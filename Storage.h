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
	Position dimensions;
	Time time;
	StorageGun gun;
	std::list<ElementStorage*> Element;

	class IteratorElement
	{
	public:
		IteratorElement() : it(nullptr) {};
		IteratorElement(ElementStorage* it) : it(it) {};
		IteratorElement(IteratorElement* that) : it(that->it) {};

		IteratorElement operator++();
		ElementStorage* operator*();

	private:
		ElementStorage* it;
	};

	class IteratorBird
	{
	public:
		IteratorBird() : it(nullptr) {};
		IteratorBird(ElementStorage* it);
		IteratorBird(IteratorBird* that) : it(that->it) {};

		IteratorBird operator++();
		ElementStorage* operator*();

	private:
		ElementStorage* it;
	};

	class IteratorBullet
	{
	public:
		IteratorBullet() : it(nullptr) {};
		IteratorBullet(ElementStorage* it) : it(it) {};
		IteratorBullet(IteratorBullet* that) : it(that->it) {};

		IteratorBullet operator++();
		ElementStorage* operator*();

	private:
		ElementStorage* it;
	};


public:
	
	Storage() : numBirds(0), points(0), numKilled(0), numMissed(0), gun(Position(800.0, 0.0)), dimensions(Position(800.0, 800.0)) {}
	int getPoints() { return points; }
	int getNumKilled() { return numKilled; }
	int getNumMissed() { return numMissed; }
	StorageGun getGun() { return gun; }
	Time getTime() { return time;  }
	int getNumBirds() { return numBirds; }
	Position getDimensions() { return dimensions; }
	IteratorElement begin();
	IteratorElement end();
	IteratorBird beginBird();
	IteratorBird endBird();
	IteratorBullet beginBullet();
	IteratorBullet endBullet();
	void add(ElementStorage* element);
	void remove(ElementStorage* it);
	void reset();
};