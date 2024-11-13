#pragma once
#include <iterator>
#include <list>

#include "Storage.h"

class ElementStorage;
using namespace std;

class Storage;
class Interface;

class SkeetLogic {
public:
	
	SkeetLogic(Interface* skeetInterface);
	
	list<ElementStorage>::iterator* ElementIterator;

	void Advance();

	void makePellet();
	void makeMissile();
	void makeBomb();

	list<ElementStorage*> ElementsToSpawn;
	class Iterator {

	private:
		Storage::IteratorElement it;
	public:
		Iterator(Storage* SkeetStorage);
	};
		Iterator begin() {
			return Iterator(SkeetStorage);
		};
	
private:
	void specialMoves();
	void spawn() const;
	void detectCollision();
	void detectOutOfBounds();
	void clearZombies() const;
	void updateStatus();
	void birdSpawn();

	int BirdsShotThisFrame;
	int BirdsMissedThisFrame;
	int PointChangeThisFrame;

	void StandardFactory(double size, int level);
	void SinkerFactory(double size, int level);
	void FloaterFactory(double size, int level);
	void CrazyFactory(double size, int level);
	
	Storage* SkeetStorage;

	Interface* SkeetInterface;

	
};


