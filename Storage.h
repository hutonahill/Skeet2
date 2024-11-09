#pragma once
#include "time.h"
#include "gun.h"
#include "ElementStorage.h"

#include <list>

class Storage {
public:

	Storage() : numBirds(0),points(0),numKilled(0),numMissed(0) {};
	int getPoints() { return points; }
	int getNumKilled() { return numKilled; }
	int getNumMissed() { return numMissed; }
	int getNumBirds() { return numBirds; }
	StorageGun getGun() { return gun; }
	StorageTime getTime() { return time;  }
	void add(ElementStorage* element);
	void remove(ElementStorage* it);
	void reset();

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
		IteratorBullet(ElementStorage* it);
		IteratorBullet(IteratorBullet* that) : it(that->it) {};

		IteratorBullet operator++();
		ElementStorage* operator*();

	private:
		ElementStorage* it;
	};

public:

	IteratorElement begin();
	IteratorElement end();
	IteratorBird beginBird();
	IteratorBird endBird();
	IteratorBullet beginBullet();
	IteratorBullet endBullet();
};