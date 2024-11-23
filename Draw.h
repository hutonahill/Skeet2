#pragma once



#include <functional>
#include <list>



class Element;
using namespace std;

class Draw;

using drawMethod = void (*)(Element*);

class Position;

class Draw {
public:

	Draw() : elementsToDraw(list<tuple<drawMethod, Element*>>()){}
	
	void drawAll();

	void add(drawMethod method, Element* element);
	
private:
	list<tuple<drawMethod, Element*>> elementsToDraw;

	
	
};

