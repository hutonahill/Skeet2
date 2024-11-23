#pragma once

class Velocity;
class Position;

enum elementType {
	PELLET,
	BOMB,
	MISSILE,
	SHRAPNEL,
	STANDARD,
	CRAZY,
	SINKER,
	FLOATER
};

class Element {
public:
	virtual Position& getPosition() = 0;

	virtual Velocity& getVelocity() = 0;

	virtual bool isDead() const = 0;

	virtual double getRadius() const = 0;

	virtual elementType getType() const = 0;
};


