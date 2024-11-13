#pragma once




class ElementStorage;
class Effect;


class DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm) = 0;

};




// Draw bullets

class PelletDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

class MissleDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

class BombDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

class ShrapnelDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

// Draw Birds

class StandardBirdDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

class SinkerBirdDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

class FloaterBirdDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

class CrazyBirdDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

// Draw effects

class FragmentDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

class StreekDraw : public DrawStrategy
{
public:
	virtual void draw(Effect* elm);

};

class exhaustDraw : public DrawStrategy
{
public:
	virtual void draw(Effect* elm);

};

class ScoreDraw : public DrawStrategy
{
public:
	virtual void draw(ElementStorage* elm);

};

