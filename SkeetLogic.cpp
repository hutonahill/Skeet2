#include "SkeetLogic.h"
#include "ArrowListener.h"
#include "DrawStrategy.h"
#include "skeet.h"
#include "Storage.h"
#include "Interface.h"
#include <math.h>
#include <GL/freeglut_std.h>

#include "ElementLogic.h"

SkeetLogic::SkeetLogic() {
	SkeetInterface = nullptr;
	SkeetStorage = new Storage();
}

void SkeetLogic::Advance() {
	
	specialMoves();

	detectOutOfBounds();
	
	detectCollision();

	clearZombies();

	updateStatus();

	birdSpawn();
	
	spawn();

	
}

double RandomFloat2(const double min, const double max)
{
	assert(min < max);
	double num = min +(static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (max - min));
	assert(min <= num && num <= max);

	return num;
}

void SkeetLogic::makePellet()
{
	float speed = 15;
	SpecialMove* move = new PelletMove();
	OnDeath* death = new DisappearDeath();
	Input* in = new NoInput();
	Timing* t = new NotTimed();
	DrawStrategy* dr = new PelletDraw();
	Bullet* b = new Bullet(move,death,in,t,dr,1);
	b->setPoints(1);
	b->getVelocity()->setDx(RandomFloat2(speed - .5, speed + .5));
	b->getVelocity()->setDy(RandomFloat2(speed - .5, speed + .5));
	ElementsToSpawn.push_back(b);
}

void SkeetLogic::makeMissile()
{
	float speed = 10;
	SpecialMove* move = new MissileMove();
	OnDeath* death = new DisappearDeath();
	Input* in = new Arrows();
	in->subscribe(SkeetInterface->getArrowListener());
	Timing* t = new NotTimed();
	DrawStrategy* dr = new MissleDraw();

	Bullet* b = new Bullet(move, death, in, t,dr, 1);
	b->setPoints(3);
	b->getVelocity()->setDx(RandomFloat2(speed - .5, speed + .5));
	b->getVelocity()->setDy(RandomFloat2(speed - .5, speed + .5));
	ElementsToSpawn.push_back(b);
}

void SkeetLogic::makeBomb() {
	float speed = 15;
	SpecialMove* move = new PelletMove();
	OnDeath* death = new ShrapnelDeath(&ElementsToSpawn);
	Input* in = new NoInput();
	Timing* t = new Timed();
	DrawStrategy* dr = new BombDraw();

	Bullet* b = new Bullet(move, death, in, t, dr, 1);
	b->setPoints(1);
	b->getVelocity()->setDx(RandomFloat2(speed - .5, speed + .5));
	b->getVelocity()->setDy(RandomFloat2(speed - .5, speed + .5));
	ElementsToSpawn.push_back(b);
}
Time* SkeetLogic::getTime() const {
	return SkeetStorage->getTime();

}

void SkeetLogic::specialMoves() const {

	for (Storage::IteratorElement it = SkeetStorage->beginElement(); it != SkeetStorage->endElement(); ++it ) { // strange error
		(*it)->getSpecialMove()->execute(*it);
	}

	
}

bool isOutOfBounds(ElementStorage* element, const Position* dimensions){
	Position* elementPosition = element->getPosition();
	return (elementPosition->getX() < -element->getRadius() || elementPosition->getX() >= dimensions->getX() + element->getRadius() ||
			elementPosition->getY() < -element->getRadius() || elementPosition->getY() >= dimensions->getY() + element->getRadius());
}

void SkeetLogic::detectOutOfBounds(){

	for (Storage::IteratorElement it = SkeetStorage->beginElement(); it != SkeetStorage->endElement(); ++it) {
		if(isOutOfBounds((*it), SkeetStorage->getDimensions())) {
			ElementStorage* targetElement = (*it);
			if(targetElement->isBird) {
				BirdsMissedThisFrame++;
			}

			if (targetElement->isBird || targetElement->isBullet) {
				PointChangeThisFrame+=targetElement->value;
			}
			targetElement->kill();
		}
	}
}



void SkeetLogic::clearZombies() const {

	Storage::IteratorElement start = SkeetStorage->beginElement();
	Storage::IteratorElement end =       SkeetStorage->endElement();
	
	for (Storage::IteratorElement it = start; it != end;) {
		bool dead = (*it)->getDead();
		if ( (*it)->getDead()) {
			it = SkeetStorage->erase(it.getIt());
		}
		else {
			++it;
		}
	}
}

void SkeetLogic::updateStatus() {
	SkeetStorage->addPoints(PointChangeThisFrame);
	SkeetStorage->addKilled(BirdsShotThisFrame);
	SkeetStorage->addMissed(BirdsMissedThisFrame);

	BirdsShotThisFrame = 0;
	BirdsMissedThisFrame = 0;
	PointChangeThisFrame = 0;
}

int RandomInt(int min, int max)
{
	assert(min < max);
	int num = (rand() % (max - min)) + min;
	assert(min <= num && num <= max);

	return num;
}



bool ShouldSpawnBird(const double seconds = 4){
	return RandomInt(0, static_cast<int>(seconds * 30)) == 1;
}

double getSize(int level) {
	const double maxSize = 30;

	return maxSize - (5*(level-1));
}

ElementStorage* Standard(const double radius, const double speed, const int points) {
	SpecialMove* move = new StandardBirdMove();
	OnDeath* death = new DisappearDeath();
	Timing* time = new NotTimed();
	Input* input = new NoInput();
	DrawStrategy* dr = new StandardBirdDraw();
	Bird* b = new Bird(move, death, input, time, dr, radius);
	b->setValue(points);
	double xSpeed = RandomFloat2(speed - .5, speed + .5);
	double ySpeed = RandomFloat2(speed - .5, speed + .5);
	b->getVelocity()->setDx(xSpeed);
	b->getVelocity()->setDy(ySpeed);


	return b;
}
void SkeetLogic::StandardFactory(const double size, const int level) {
	ElementStorage* newStandard;
	switch (level) {
		case 1:
			newStandard = Standard(size, 7, 10);
			break;
		case 2:
			newStandard = Standard(size, 7, 12);
			break;
		case 3:
			newStandard = Standard(size, 5.0, 15);
			break;
		case 4:
			newStandard = Standard(size, 4.0, 18);
			break;
		default:
			newStandard = nullptr;
			break;
	}

	if (newStandard != nullptr) {
		ElementsToSpawn.push_back(newStandard);
	}
}


ElementStorage* Sinker(double radius, double speed, int points) {
	SpecialMove* move = new SinkerBirdMove();
	OnDeath* death = new DisappearDeath();
	Timing* time = new NotTimed();
	Input* input = new NoInput();
	DrawStrategy* dr = new SinkerBirdDraw();
	Bird* b = new Bird(move, death, input, time,dr, radius);
	b->setValue(points);
	b->getVelocity()->setDx(RandomFloat2(speed - .5, speed + .5));
	b->getVelocity()->setDy(RandomFloat2(speed - .5, speed + .5));


	return b;
}
void SkeetLogic::SinkerFactory(double size, int level) {
	ElementStorage* newSinker;
	switch (level) {
		case 2:
			newSinker = Sinker(size, 4.5, 20);
			break;
		case 3:
			newSinker = Sinker(size, 4.0, 22);
			break;
		case 4:
			newSinker = Sinker(size, 3.5, 25);
			break;
		default:
			newSinker = nullptr;
			break;
	}

	if (newSinker != nullptr) {
		ElementsToSpawn.push_back(newSinker);
	}
}


ElementStorage* Floater(double radius, double speed, int points) {
	SpecialMove* move = new FloaterBirdMove();
	OnDeath* death = new DisappearDeath();
	Timing* time = new NotTimed();
	Input* input = new NoInput();
	DrawStrategy* dr = new FloaterBirdDraw();
	Bird* b = new Bird(move, death, input, time,dr, radius);
	b->setValue(points);
	b->getVelocity()->setDx(RandomFloat2(speed - .5, speed + .5));
	b->getVelocity()->setDy(RandomFloat2(speed - .5, speed + .5));


	return b;
}
void SkeetLogic::FloaterFactory(double size, int level) {
	ElementStorage* newFloater;
	switch (level) {
		case 3:
			newFloater = Floater(size, 5, 15);
			break;
		case 4:
			newFloater = Floater(size, 4.0, 25);
			break;
		default:
			newFloater = nullptr;
			break;
	}

	if (newFloater != nullptr) {
		ElementsToSpawn.push_back(newFloater);
	}
}


ElementStorage* Crazy(double size, double speed, int points) {
	SpecialMove* move = new FloaterBirdMove();
	OnDeath* death = new DisappearDeath();
	Timing* time = new NotTimed();
	Input* input = new NoInput();
	DrawStrategy* dr = new CrazyBirdDraw();
	Bird* b = new Bird(move, death, input, time,dr, size);
	b->setValue(points);
	b->getVelocity()->setDx(RandomFloat2(speed - .5, speed + .5));
	b->getVelocity()->setDy(RandomFloat2(speed - .5, speed + .5));


	return b;
}
void SkeetLogic::CrazyFactory(double size, int level) {
	ElementStorage* newCrazy;
	switch (level) {
		case 4:
			newCrazy = Crazy(size, 4.5, 30);
			break;
		default:
			newCrazy = nullptr;
			break;
	}

	if (newCrazy != nullptr) {
		ElementsToSpawn.push_back(newCrazy);
	}
}



void SkeetLogic::birdSpawn() {

	int level = SkeetStorage->getTime()->level();
	double size = getSize(level);
	// spawns when there is nothing on the screen
	if (SkeetStorage->getNumBirds() == 0 && RandomInt(0, 15) == 1) {
		StandardFactory(size, level);
	}

	// spawn every 4 seconds
	if (ShouldSpawnBird()) {
		StandardFactory(size, level);
	}
	// spawn every 4 seconds
	if (ShouldSpawnBird()) {
		SinkerFactory(size, level);
	}
	// spawn every 4 seconds
	if (ShouldSpawnBird()) {
		FloaterFactory(size, level);
	}
	// spawn every 4 seconds
	if (ShouldSpawnBird()) {
		CrazyFactory(size, level);
	}
         
         
	
}

/**
 * Spawns all the elements that were qued up
 */
void SkeetLogic::spawn() const {
	for (ElementStorage* element : ElementsToSpawn) {
		SkeetStorage->addElement(element);
	}
}


/**
 * Builder for a fragment
 * @param position The initial position of the fragment
 * @param velocity The velocity that the fragment orginates from
 * @return 
 */
ElementStorage* SkeetLogic::Fragment(const Position* position, const Velocity* velocity) {
	SpecialMove* move = new PelletMove();
	OnDeath* death = new DisappearDeath();
	Timing* time = new Timed();
	int timeToLive = static_cast<int>(30.0 * RandomFloat2(0.4, 1.0));
	time->setInitialTimer(timeToLive);
	DrawStrategy* draw = new FragmentDraw();


	
	ElementStorage* newBullet = new Bullet(move, death, new NoInput(), time, draw, RandomFloat2(1.0, 2.5));

	newBullet->getVelocity()->setDx(velocity->getDx() * 0.5 + RandomFloat2(-6.0, 6.0));
	newBullet->getVelocity()->setDy(velocity->getDy() * 0.5 + RandomFloat2(-6.0, 6.0));

	newBullet->getPosition()->setX(position->getX());
	newBullet->getPosition()->setY(position->getY());

	/*
	// the velocity is a random kick plus the velocity of the thing that died
   this->v.setDx(v.getDx() * 0.5 + random(-6.0, 6.0));
   this->v.setDy(v.getDy() * 0.5 + random(-6.0, 6.0));
   
	// age
	age = random(0.4, 1.0);
	 */

	return newBullet;
}


void SkeetLogic::detectCollision() {

	for (Storage::IteratorBird it = SkeetStorage->beginBird(); it != SkeetStorage->endBird(); ++it) {
		ElementStorage* bird = (*it);
		for (Storage::IteratorBullet it2 = SkeetStorage->beginBullet(); it2 != SkeetStorage->endBullet(); ++it2) {
			ElementStorage* bullet = (*it2);

			double minDistance =  minimumDistance(bird->getPosition(), bird->getVelocity(),
							 bullet->getPosition(),  bullet->getVelocity());
			
			if (!bird->getDead() && !bullet->getDead() && bird->getRadius() + bullet->getRadius() > minDistance)
			{
				// this implies fragments are created on the death of every bird...
				for (int i = 0; i < 25; i++) {
					ElementsToSpawn.push_back(Fragment(bullet->getPosition(), bullet->getVelocity()));
				}
				bird->kill();
				bullet->kill();
				BirdsShotThisFrame++;
				/*bullet->setValue(-(bird->getPoints()));
				bird->setPoints(0);
				i think this is unnecessary now, but i saved it just in case.*/
			}
		}
	}
}



SkeetLogic::Iterator::Iterator(Storage* skeetStorage) : storage_(skeetStorage){
	it = storage_->beginElement();
}

void SkeetLogic::Iterator::moveToEnd(const Storage* skeetStorage) {
	it = skeetStorage->endElement();
}

SkeetLogic::Iterator SkeetLogic::Iterator::operator++()
{
	++it;
	return *this;
}

ElementStorage* SkeetLogic::Iterator::operator*() const {
	return *it;
}
