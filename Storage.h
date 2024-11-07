#pragma once
#include "time.h"
#include "gun.h"
#include "ElementStorage.h"

#include <list>

class Storage {
private:

	int numBirds;
	int points;
	int numKilled;
	int numMissed;
	StorageTime time;
	StorageGun gun;
	std::list<ElementStorage*> Element;

	class IteratorElement
	{
	public:
		IteratorElement() : it(nullptr) {};
		IteratorElement(ElementStorage* it) : it(it) {};
		IteratorElement(IteratorElement* that) : it(that->it) {};

		IteratorElement operator++() {};

	private:
		ElementStorage* it;
	};

	class IteratorBird
	{
		IteratorBird() : it(nullptr) {};
		IteratorBird(ElementStorage* it) : it(it) {};
		IteratorBird(IteratorBird* that) : it(that->it) {};

		IteratorBird operator++() {};

	private:
		ElementStorage* it;
	};

	class IteratorBullet
	{
		IteratorBullet() : it(nullptr) {};
		IteratorBullet(ElementStorage* it) : it(it) {};
		IteratorBullet(IteratorBullet* that) : it(that->it) {};

		IteratorBullet operator++() {};

	private:
		ElementStorage* it;
	};


public:
	
	Storage() {};
	int getPoints() { return points; }
	int getNumKilled() {};
	int getNumMissed() {};
	IteratorElement begin() {};
	IteratorElement end() {};
	IteratorBird beginBird() {};
	IteratorBird endBird() {};
	IteratorBullet beginBullet() {};
	IteratorBullet endBullet() {};
	void add(ElementStorage element) {};
	void reset() {};
};
