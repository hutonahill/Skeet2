#pragma once
#include <iterator>
#include <list>

using namespace std;

class ElementStorage;
class Storage;
class Interface;

class SkeetLogic {
public:

	class iterator;
	
	SkeetLogic(Interface* skeetInterface);
	
	list<ElementStorage>::iterator* ElementIterator;

	void Advance();

	void makePellet();
	void makeMissile();
	void makeBomb();

	list<ElementStorage> ElementsToSpawn;
	
private:
	void move();
	void specialMoves();
	void spawn();
	void detectCollision();
	void clearZombies();
	void updateStatus();

	list<ElementStorage>::iterator* PrivateElementIterator;
	
	Storage* SkeetStorage;

	Interface* SkeetInterface;

	
};

class SkeetLogic :: iterator {
private:
	
};
