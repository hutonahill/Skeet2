#include "SkeetLogic.h"

#include "skeet.h"
#include "Storage.h"

#include <math.h>

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
		(*it)->getSpecialMove();
	}

	
}

bool isOutOfBounds(ElementStorage element, Position dimensions){
	Position elementPosition = element.getPosition();
	return (elementPosition.getX() < -element.getRadius() || elementPosition.getX() >= dimensions.getX() + element.getRadius() ||
			elementPosition.getY() < -element.getRadius() || elementPosition.getY() >= dimensions.getY() + element.getRadius());
}

void SkeetLogic::detectOutOfBounds() {

	for (Storage::IteratorElement it = SkeetStorage->beginElement(); it != SkeetStorage->endElement(); ++it) {
		if(isOutOfBounds(*(*it), SkeetStorage->getDimensions())) {
			(*it)->kill();
		}
	}
}



void SkeetLogic::clearZombies() const {
	for (Storage::IteratorElement it = SkeetStorage->beginElement(); it != SkeetStorage->endElement(); ++it) {
		bool dead = (*it)->getDead();
		if ( (*it)->isDead() ) {
			SkeetStorage->remove(element);
		}
	}
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

ElementStorage* Standard(double radius, double speed, int points) {
	SpecialMove* move = new StandardBirdMove();
	OnDeath* death = new DisapearDeath();
	Timing* time = new NotTimed();

	return new ;
}
void SkeetLogic::StandardFactory(double size, int level) {
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
	OnDeath* death = new DisapearDeath();
	Timing* time = new NotTimed();

	return new ;
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
	OnDeath* death = new DisapearDeath();
	Timing* time = new NotTimed();

	return new ;
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
	SpecialMove* move = new CrazyBirdMove();
	OnDeath* death = new DisapearDeath();
	Timing* time = new NotTimed();

	return new ;
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

	int level = SkeetStorage->getTime().level();
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

void SkeetLogic::spawn() {
	for (ElementStorage* element : ElementsToSpawn) {
		SkeetStorage->add(element);
	}
}



