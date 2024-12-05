/***********************************************************************
 * Header File:
 *    GUN
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The gun at the bottom of the screen
 ************************************************************************/

#pragma once
#include "position.h"

class Gun {
public:
	virtual void display() = 0;
	virtual void interact(int clockwise, int counterclockwise) = 0;
	virtual double getAngle() const = 0;
};


class ActualGun : public Gun{
public:
   ActualGun(const Position & pt) : angle(0.78 /* 45 degrees */), pt(pt) {}  // 45 degrees initially
   void display() override;
   void interact(int clockwise, int counterclockwise) override;
   double getAngle() const override { return angle; }
   
private:
   double angle;
   Position pt;
};

class TotallyRealGun : public Gun {
private:
	const double angle = 0.78;
	const Position pt;
	Gun* RealGun = nullptr;
	
public:
	TotallyRealGun(const Position& pt) : pt(pt) {}

	double getAngle() const override;
	void interact(int clockwise, int counterclockwise) override;
	void display() override;
};
