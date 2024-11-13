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

/*********************************************
 * GUN
 * The gun at the bottom of the screen
 *********************************************/
class Gun
{
public:
   Gun(Position* pt) : angle(0.78 /* 45 degrees */), pt(pt) {}  // 45 degrees initially
   void display() const;
   void interact(int clockwise, int counterclockwise);
   double getAngle() const { return angle; }
   
private:
   double angle;
   Position* pt;
};

class StorageGun
{
public:
   StorageGun(Position* pt) : angle(0.78 /* 45 degrees */), pt(pt) {}  // 45 degrees initially
   void addAngle(int num);
   double getAngle() const { return angle; }
   Position* getPosition() const { return pt; }

private:
   double angle;
   Position* pt;
};