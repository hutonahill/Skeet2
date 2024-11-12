#pragma once
#include <iterator>
#include <list>

class ElementStorage;
using namespace std;


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

	list<ElementStorage*> ElementsToSpawn;
	
private:
	void specialMoves();
	void spawn();
	void detectCollision();
	void detectOutOfBounds();
	void clearZombies() const;
	void updateStatus();
	void birdSpawn();

	void StandardFactory(double size, int level);
	void SinkerFactory(double size, int level);
	void FloaterFactory(double size, int level);
	void CrazyFactory(double size, int level);
	
	Storage* SkeetStorage;

	Interface* SkeetInterface;

	
};

class SkeetLogic :: iterator {
private:
	
};
