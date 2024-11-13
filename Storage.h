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
	Position* dimensions;
	Time* time;
	StorageGun* gun;
	std::list<ElementStorage*>* Element;

public:

	class IteratorElement
	{
	public:
		IteratorElement() : it(nullptr) {};
		IteratorElement(ElementStorage* it) : it(it) {};
		IteratorElement(IteratorElement* that) : it(that->it) {};

		IteratorElement operator++();
		ElementStorage* operator*();
		bool operator !=(const IteratorElement& rhs) { return it != rhs.it; }

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
		bool operator !=(const IteratorBird& rhs) { return it != rhs.it; }
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
		bool operator !=(const IteratorBullet& rhs) { return it != rhs.it; }

	private:
		ElementStorage* it;
	};
	
	Storage() : numBirds(0), points(0), numKilled(0), numMissed(0),
		dimensions(new Position(800.0, 800.0)),
		gun(new StorageGun(new Position(800.0, 0.0))) {}
	int getPoints() const { return points; }
	int getNumKilled() const { return numKilled; }
	int getNumMissed() const { return numMissed; }
	float getHitRatio() { return (FLOAT)numKilled / (FLOAT)(numMissed + numKilled); }
	Position* getDimensions() { return dimensions; }
	StorageGun* getGun() { return gun; }
	Time* getTime() const { return time;  }
	int getNumBirds() const { return numBirds; }
	Position* getDimensions() const { return dimensions; }
	IteratorElement beginElement();
	IteratorElement endElement();
	IteratorBird beginBird();
	IteratorBird endBird();
	IteratorBullet beginBullet();
	IteratorBullet endBullet();
	void addPoints(int points) { this->points += points; }
	void addMissed(int missed) { numMissed += missed; }
	void addKilled(int killed) { numKilled += killed; }
	void addElement(ElementStorage* element);
	void remove(ElementStorage* it);
	void reset();
};