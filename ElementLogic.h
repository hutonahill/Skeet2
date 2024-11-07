#pragma once

class ElementStorage;
class ArrowListener;

class ElementLogic {
public:
	virtual void execute(ElementStorage& el) = 0;
};

class SpecialMove : public ElementLogic {
public:
	virtual void execute(ElementStorage& el) = 0;
};

class StandardBirdMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage& el);
};

class FloaterBirdMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage& el);
};

class SinkerBirdMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage& el);
};

class CrazyBirdMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage& el);
};

class PelletMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage& el);
};

class MissleMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage& el);
};

class NoneMove : public SpecialMove
{
public:
	virtual void execute(ElementStorage& el);
};

class OnDeath : public ElementLogic
{
public:
	virtual void execute(ElementStorage& el) = 0;
};

class EffectDeath : public OnDeath
{
public:
	virtual void execute(ElementStorage& el);
};

class DisapearDeath : public OnDeath
{
public:
	virtual void execute(ElementStorage& el);
};

class ShrapnelDeath : public OnDeath
{
public:
	virtual void execute(ElementStorage& el);
};

class Input : public ElementLogic
{
public:
	Input() : up(0), down(0), left(0), right(0) {};
	virtual void execute(ElementStorage& el) = 0;
	virtual void subscribe(ArrowListener& al) = 0;
	virtual void unsubscribe(ArrowListener& al) = 0;
	int up;
	int down;
	int left;
	int right;
};

class Arrows : public Input
{
public:
	virtual void execute(ElementStorage& el);
	virtual void subscribe(ArrowListener& al);
	virtual void unsubscribe(ArrowListener& al);
};

class None : public Input
{
public:
	virtual void execute(ElementStorage& el);
	virtual void subscribe(ArrowListener& al);
	virtual void unsubscribe(ArrowListener& al);
};

class Timing : public ElementLogic
{
public:
	virtual void execute(ElementStorage& el);
};

class NotTimed : public Timing
{
public:
	virtual void execute(ElementStorage& el);
};

class Timed : public Timing
{
public:
	virtual void execute(ElementStorage& el);
};