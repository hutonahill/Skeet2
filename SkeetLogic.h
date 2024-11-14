﻿#pragma once
#include <iterator>
#include <list>
#include "time.h"

#include "Storage.h"

class ElementStorage;
using namespace std;

class Storage;
class Interface;

class SkeetLogic {
public:
	
	SkeetLogic();

	void setInterface(Interface* skeetInterface) { SkeetInterface = skeetInterface; }
	
	list<ElementStorage>::iterator* ElementIterator;

	void Advance();

	void makePellet();
	void makeMissile();
	void makeBomb();
	StorageGun* getGun() const { return SkeetStorage->getGun(); };
	float getHitRatio() const { return SkeetStorage->getHitRatio(); }
	Position* getDimensions() const { return SkeetStorage->getDimensions(); }
	int getPoints() const { return SkeetStorage->getPoints(); }

	static ElementStorage* Fragment(const Position* position, const Velocity* velocity);

	Time* getTime() const;


	list<ElementStorage*> ElementsToSpawn;
	class Iterator {

	private:
		Storage::IteratorElement it;
	public:
		Iterator(Storage* SkeetStorage);
		Iterator(ElementStorage* it) : it(it) {}
		Iterator(Iterator* that) : it(that->it) {}

		void moveToEnd(Storage* SkeetStorage);
		
		Iterator operator++();
		ElementStorage* operator*();
		bool operator !=(const Iterator& rhs) { return it != rhs.it; }
	};
	
	Iterator begin() const {
		return Iterator(SkeetStorage);
	}
	
	Iterator end() const {
		Iterator it = Iterator(SkeetStorage);

		it.moveToEnd(SkeetStorage);

		return it;
	}
		
	
private:
	void specialMoves() const;
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


