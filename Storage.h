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

		IteratorElement operator++();
		ElementStorage* operator*();

	private:
		ElementStorage* it;
	};

	class IteratorBird
	{
	public:
		IteratorBird() : it(nullptr) {};
		IteratorBird(ElementStorage* it) : it(it) {};
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
	
	Storage();
	int getPoints() { return points; }
	int getNumKilled() { return numKilled; }
	int getNumMissed() { return numMissed; }
	StorageGun getGun() { return gun; }
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