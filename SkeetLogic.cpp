#include "SkeetLogic.h"

#include "skeet.h"
#include "Storage.h"

#include <math.h>
#include <GL/freeglut_std.h>

SkeetLogic::SkeetLogic(Interface* skeetInterface) {
	SkeetInterface = skeetInterface;
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

void SkeetLogic::specialMoves() {

	for (Storage::IteratorElement it = SkeetStorage->beginElement(); it != SkeetStorage->endElement(); ++it ) {
		(*it)->getSpecialMove()->execute(*it);
	}

	
}

bool isOutOfBounds(const ElementStorage* element, const Position* dimensions){
	Position elementPosition = element->getPosition();
	return (elementPosition.getX() < -element->getRadius() || elementPosition.getX() >= dimensions->getX() + element->getRadius() ||
			elementPosition.getY() < -element->getRadius() || elementPosition.getY() >= dimensions->getY() + element->getRadius());
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
	for (Storage::IteratorElement it = SkeetStorage->beginElement(); it != SkeetStorage->endElement(); ++it) {
		bool dead = (*it)->getDead();
		if ( (*it)->isDead() ) {
			SkeetStorage->remove(*it);
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

int random(int min, int max)
{
	assert(min < max);
	int num = (rand() % (max - min)) + min;
	assert(min <= num && num <= max);

	return num;
}

bool ShouldSpawnBird(const double seconds = 4){
	return random(0, static_cast<int>(seconds * 30)) == 1;
}

double getSize(int level) {
	const double maxSize = 30;

	return maxSize - (5*(level-1));
}

ElementStorage* Standard(const double radius, const double speed, const int points) {
	SpecialMove* move = new StandardBirdMove();
	OnDeath* death = new DisapearDeath();
	Timing* time = new NotTimed();
	DrawStrategy* draw = new StandardBirdDraw();

	ElementStorage* newBird = new Bird(move, death, new NoInput(), time, draw, radius);
	newBird->value = points;
	newBird->getVelocity().set(0, speed);
	return 	newBird;
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


ElementStorage* Sinker(const double radius, const double speed, const int points) {
	SpecialMove* move = new SinkerBirdMove();
	OnDeath* death = new DisapearDeath();
	Timing* time = new NotTimed();
	DrawStrategy* draw = new SinkerBirdDraw();

	ElementStorage* newBird = new Bird(move, death, new NoInput(), time, draw, radius);
	newBird->value = points;
	newBird->getVelocity().set(0, speed);

	return newBird;
}
auto SkeetLogic::SinkerFactory(const double size, int level) -> void {
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


ElementStorage* Floater(const double radius, const double speed, const int points) {
	SpecialMove* move = new FloaterBirdMove();
	OnDeath* death = new DisapearDeath();
	Timing* time = new NotTimed();
	DrawStrategy* draw = new FloaterBirdDraw();

	ElementStorage* newBird = new Bird(move, death, new NoInput(), time, draw, radius);
	newBird->value = points;
	newBird->getVelocity().set(0, speed);

	return newBird;
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


ElementStorage* Crazy(const double radius, const double speed, const int points) {
	SpecialMove* move = new CrazyBirdMove();
	OnDeath* death = new DisapearDeath();
	Timing* time = new NotTimed();
	DrawStrategy* draw = new CrazyBirdDraw();

	ElementStorage* newBird = new Bird(move, death, new NoInput(), time, draw, radius);
	newBird->value = points;
	newBird->getVelocity()->set(0, speed);

	return newBird;
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
	if (SkeetStorage->getNumBirds() == 0 && random(0, 15) == 1) {
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

void SkeetLogic::spawn() const {
	for (ElementStorage* element : ElementsToSpawn) {
		SkeetStorage->addElement(element);
	}
}

ElementStorage* Fragment(Position* position, Velocity* velocity) {
	SpecialMove* move = new PelletMove();
	OnDeath* death = new DisapearDeath();
	Timing* time = new Timed();
	time->setInitialTimer()
}

void SkeetLogic::detectCollision() {

	for (Storage::IteratorBird it = SkeetStorage->beginBird(); it != SkeetStorage->endBird(); ++it) {
		ElementStorage* bird = (*it);
		for (Storage::IteratorBullet it2 = SkeetStorage->beginBullet(); it2 != SkeetStorage->endBullet(); ++it2) {
			ElementStorage* bullet = (*it2);
			if (!bird->isDead() && !bullet->isDead() &&
			 bird->getRadius() + bullet->getRadius() >
			 minimumDistance(bird->getPosition(), bird->getVelocity(),
							 bullet->getPosition(),  bullet->getVelocity()))
			{
				for (int i = 0; i < 25; i++)
					
					ElementsToSpawn.push_back(Fragment(bullet->getPosition(), bullet->getVelocity()));
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





