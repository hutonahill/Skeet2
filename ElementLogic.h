﻿#pragma once

class ElementStorage;
class ArrowListener;
class SkeetLogic;

// The base Element logic class
// Abstract
class ElementLogic {
public:
	virtual void execute(ElementStorage* el) = 0;
};

// Special move of an element
// Abstract
class SpecialMove : public ElementLogic {
public:
	virtual void execute(ElementStorage* el) = 0;
};

// Special move for standard bird
// Concrete
class StandardBirdMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage* el);
};

// Special move for floater bird
// Concrete
class FloaterBirdMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage* el);
};

// Special move for sinker bird
// Concrete
class SinkerBirdMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage* el);
};

// Special move for crazy bird
// Concrete
class CrazyBirdMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage* el);
};

// Special move for pellet and bomb
// Concrete
class PelletMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage* el);
};

// Special move for the missle
// Concrete
class MissleMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage* el);
};

// Special move for things that don't move
// Concrete
class NoneMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage* el);
};

// What do we do when an element dies
// Abstract
class OnDeath : public ElementLogic
{
public:
	virtual void execute(ElementStorage* el) = 0;
};

// When an effect dies
// Concrete
class EffectDeath : public OnDeath
{
public:
	virtual void execute(ElementStorage* el);
};

// Fragments, offscreen birds, shrappnel, missle, bullets
// Concrete
class DisapearDeath : public OnDeath
{
public:
	virtual void execute(ElementStorage* el);
};

// Bombs
// Concrete
class ShrapnelDeath : public OnDeath
{
public:
	ShrapnelDeath(SkeetLogic* sl) : SkeetLogic(sl) {};
	virtual void execute(ElementStorage* el);
private:
	SkeetLogic* SkeetLogic;
};

// Handles whether an element needs input or not
// Abstract
class Input : public ElementLogic
{
public:
	Input() : up(0), down(0), left(0), right(0) {};
	virtual void execute(ElementStorage* el) = 0;
	virtual void subscribe(ArrowListener* al) = 0;
	virtual void unsubscribe(ArrowListener* al) = 0;
	int up;
	int down;
	int left;
	int right;
};

// Missles need arrow input
// Concrete
class Arrows : public Input
{
public:
	virtual void execute(ElementStorage* el);
	virtual void subscribe(ArrowListener* al);
	virtual void unsubscribe(ArrowListener* al);
private:
	ArrowListener* al;
};

// Everything else
// Concrete
class NoInput : public Input
{
public:
	virtual void execute(ElementStorage* el);
	virtual void subscribe(ArrowListener* al);
	virtual void unsubscribe(ArrowListener* al);
};

// What we do for internal clocks on elements
// Abstract
class Timing : public ElementLogic
{
public:
	virtual void execute(ElementStorage* el) = 0;
	virtual void setInitialTimer(int time) = 0;
};

// No timer for the object
// Concrete
class NotTimed : public Timing
{
public:
	virtual void execute(ElementStorage* el);
	virtual void setInitialTimer(int time) {}
};

// Has an internal timer
// Concrete
class Timed : public Timing
{
public:
	virtual void execute(ElementStorage* el);

	// This is set to a different time depending on the type of timed item
	virtual void setInitialTimer(int time) { timeToDie = time; }
	int timeToDie;
};