#pragma once
#include "time.h"
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

protected:
	std::list<ElementStorage*>* Element;

public:

	class IteratorElement
	{
	public:
		IteratorElement() : it() {}
		IteratorElement(std::list<ElementStorage*>::iterator it) : it(std::move(it)) {}
		IteratorElement(const IteratorElement* that) : it(that->it) {}

		std::list<ElementStorage*>::iterator getIt() {return it;}

		IteratorElement& operator++();
		ElementStorage* operator*() const;
		bool operator !=(const IteratorElement& rhs) const { return it != rhs.it; }
		bool operator !=(const std::list<ElementStorage*>::iterator& rhs) const { return it != rhs; }

		static IteratorElement emptyObject;
		

	private:
		std::list<ElementStorage*>::iterator it;
		
	};

	class IteratorBird
	{
	public:
		IteratorBird() : element(nullptr), it() {}
		IteratorBird(std::list<ElementStorage*>* element);
		IteratorBird(const IteratorBird* that) : element(that->element), it(that->it) {}

		IteratorBird end() {
			it = element->end();
			return this;
		}

		IteratorBird& operator++();
		ElementStorage* operator*() const;
		bool operator !=(const IteratorBird& rhs) const { return it != rhs.it; }
		bool operator !=(const std::list<ElementStorage*>::iterator& rhs) const { return it != rhs; }
	private:
		std::list<ElementStorage*>* element;
		std::list<ElementStorage*>::iterator it;
	};

	class IteratorBullet
	{
	public:
		IteratorBullet() : element(nullptr), it() {}
		IteratorBullet(std::list<ElementStorage*>* elementInput);
		IteratorBullet(const IteratorBullet* that) : element(that->element), it(that->it) {}

		IteratorBullet end() {
			it = element->end();
			return this;
		}

		IteratorBullet& operator++();
		ElementStorage* operator*() const;
		bool operator !=(const IteratorBullet& rhs) const { return it != rhs.it; }
		bool operator !=(const std::list<ElementStorage*>::iterator& rhs) const { return it != rhs; }

	private:
		std::list<ElementStorage*>* element;
		std::list<ElementStorage*>::iterator it;

		
	};
	
	Storage() : numBirds(0), points(0), numKilled(0), numMissed(0),
		dimensions(new Position(800.0, 800.0)),
		time(new Time()), gun(new StorageGun(new Position(800.0, 0.0))),
		Element(new std::list<ElementStorage*>) {}
	int getPoints() const { return points; }
	int getNumKilled() const { return numKilled; }
	int getNumMissed() const { return numMissed; }
	float getHitRatio() const { return static_cast<float> (numKilled) / static_cast<float>(numMissed + numKilled); }
	Position* getDimensions() { return dimensions; }
	StorageGun* getGun() const { return gun; }
	Time* getTime() const { return time;  }
	int getNumBirds() const { return numBirds; }
	Position* getDimensions() const { return dimensions; }
	IteratorElement beginElement() const;
	IteratorElement endElement() const;
	IteratorBird beginBird() const;
	IteratorBird endBird() const;
	IteratorBullet beginBullet() const;
	IteratorBullet endBullet() const;
	void addPoints(int points) { this->points += points; }
	void addMissed(const int missed) { numMissed += missed; }
	void addKilled(const int killed) { numKilled += killed; }
	void addElement(ElementStorage* element);
	void remove(ElementStorage* element);
	std::list<ElementStorage*>::iterator erase(const std::list<ElementStorage*>::iterator& it);
	void reset();
};