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

void StandardFactory(double size, int level) {
	ElementStorage* newStandard;
	switch (level) {
		case 1:
			newStandard = new Standard(size, 7);
		case 2:
			newStandard = new Standard(size, 7, 12);
		case 3:
			newStandard = new Standard(size, 5.0, 15);
		case 4:
			newStandard = new Standard(size, 4.0, 18);
		default:
			return
	}
}

ElementStorage* SinkerFacotry(double size, int level) {
	
	switch (level) {
		case 1:
			return new Standard(size, 7);
		case 2:
			return new Standard(size, 7, 12);
		case 3:
			return new Standard(size, 5.0, 15);
		case 4:
			return new Standard(size, 4.0, 18);
	}
}

void SkeetLogic::birdSpawn() {
	double size;
   switch (SkeetStorage->getTime().level)
   {
      // in level 1 spawn big birds occasionally
      case 1:
         size = 30.0;
         // spawns when there is nothing on the screen
         if (SkeetStorage->getNumBirds() == 0 && random(0, 15) == 1)
            ElementsToSpawn.push_back(new Standard(size, 7.0));
         
         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Standard(size, 7.0));
         break;
         
      // two kinds of birds in level 2
      case 2:
         size = 25.0;
         // spawns when there is nothing on the screen
         if (SkeetStorage->getNumBirds() == 0 && random(0, 15) == 1)
            ElementsToSpawn.push_back(new Standard(size, 7.0, 12));

         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Standard(size, 5.0, 12));
         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Sinker(size));
         break;
      
      // three kinds of birds in level 3
      case 3:
         size = 20.0;
         // spawns when there is nothing on the screen
         if (SkeetStorage->getNumBirds() == 0 && random(0, 15) == 1)
            ElementsToSpawn.push_back(new Standard(size, 5.0, 15));

         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Standard(size, 5.0, 15));
         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Sinker(size, 4.0, 22));
         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Floater(size));
         break;
         
      // three kinds of birds in level 4
      case 4:
         size = 15.0;
         // spawns when there is nothing on the screen
         if (SkeetStorage->getNumBirds() == 0 && random(0, 15) == 1)
            ElementsToSpawn.push_back(new Standard(size, 4.0, 18));

         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Standard(size, 4.0, 18));
         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Sinker(size, 3.5, 25));
         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Floater(size, 4.0, 25));
         // spawn every 4 seconds
         if (ShouldSpawnBird())
            ElementsToSpawn.push_back(new Crazy(size));
         break;
         
      default:
         break;
   }
}

void SkeetLogic::spawn() {
	for (ElementStorage* element : ElementsToSpawn) {
		SkeetStorage->add(element);
	}
}



