#pragma once

#include "StorageGun.h"



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
	void draw(ElementStorage* elm) override;

};

class MissleDraw : public DrawStrategy
{
public:
	void draw(ElementStorage* elm) override;

};

class BombDraw : public DrawStrategy
{
public:
	void draw(ElementStorage* elm) override;

};

class ShrapnelDraw : public DrawStrategy
{
public:
	void draw(ElementStorage* elm) override;

};

// Draw Birds

class StandardBirdDraw : public DrawStrategy
{
public:
	void draw(ElementStorage* elm) override;

};

class SinkerBirdDraw : public DrawStrategy
{
public:
	void draw(ElementStorage* elm) override;

};

class FloaterBirdDraw : public DrawStrategy
{
public:
	void draw(ElementStorage* elm) override;

};

class CrazyBirdDraw : public DrawStrategy
{
public:
	void draw(ElementStorage* elm) override;

};

// Draw effects

class FragmentDraw : public DrawStrategy
{
public:
	void draw(ElementStorage* elm) override;

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
	void draw(ElementStorage* elm) override;

};

