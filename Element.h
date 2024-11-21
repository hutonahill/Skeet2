#pragma once

class Position;

class Element {
public:
	virtual Position& getPosition() const = 0;

	virtual double getValue() const = 0;
};
