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

	for (ElementStorage element : SkeetStorage->begin()) {
		// exicuted exicute method which hasent been updated
	}

	
}

void SkeetLogic::detectOutOfBounds() {

	for (ElementStorage element : SkeetStorage->begin()) {
		// exicuted exicute method which hasent been updated
	}

	
}

void SkeetLogic::clearZombies() {
	for (ElementStorage* element : SkeetStorage->begin()) {
		if (/*element.isDead*/) {
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

void SkeetLogic::StandardFactory(double size, int level) {
	ElementStorage* newStandard;
	switch (level) {
		case 1:
			newStandard = new Standard(size, 7);
			break;
		case 2:
			newStandard = new Standard(size, 7, 12);
			break;
		case 3:
			newStandard = new Standard(size, 5.0, 15);
			break;
		case 4:
			newStandard = new Standard(size, 4.0, 18);
			break;
		default:
			newStandard = nullptr;
			break;
	}

	if (newStandard != nullptr) {
		ElementsToSpawn.push_back(newStandard);
	}
}

void SkeetLogic::SinkerFactory(double size, int level) {
	ElementStorage* newSinker;
	switch (level) {
		case 2:
			newSinker = new Sinker(size);
			break;
		case 3:
			newSinker = new Sinker(size, 4.0, 22);
			break;
		case 4:
			newSinker = new Sinker(size, 3.5, 25);
			break;
		default:
			newSinker = nullptr;
			break;
	}

	if (newSinker != nullptr) {
		ElementsToSpawn.push_back(newSinker);
	}
}

void SkeetLogic::FloaterFactory(double size, int level) {
	ElementStorage* newFloater;
	switch (level) {
		case 3:
			newFloater = new Floater(size);
			break;
		case 4:
			newFloater = new Floater(size, 4.0, 25);
			break;
		default:
			newFloater = nullptr;
			break;
	}

	if (newFloater != nullptr) {
		ElementsToSpawn.push_back(newFloater);
	}
}

void SkeetLogic::CrazyFactory(double size, int level) {
	ElementStorage* newCrazy;
	switch (level) {
		case 4:
			newCrazy = new Crazy(size);
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

	int level = SkeetStorage->getTime().getLevel();
	int size = getSize(level);
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



