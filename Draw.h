#pragma once
#include "position.h"

#include <functional>
#include <list>]

using namespace std;

class Draw;

using drawMethod = void (Draw::*)(Position&, double);

class Position;

class Draw {
public:
	
private:
	list<tuple<drawMethod, Position&, double>> elementsToDraw = list<tuple<drawMethod, Position&, double>>();
	
	void drawBomb(const Position& point, double angle) const;
	void drawPellet(const Position& point, double angle) const;
	void drawMissile(const Position& point, double angle) const;

	void drawStandard(const Position& center, double size) const;
	void drawSinker(const Position& center, double size) const;
	void drawFloater(const Position& center, double size) const;
	void drawCrazy(const Position& center, double size) const;
	
	void drawDisk(const Position& center, double radius, double red, double green, double blue) const;
	void drawDot(const Position& point, double radius, double red, double green, double blue) const;
	void drawLine(const Position& begin, const Position& end, double red, double green, double blue) const;
	
};
