/***********************************************************************
 * Header File:
 *    Bird : Everything that can be shot
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that moves across the screen to be shot
 ************************************************************************/

#pragma once
#include "position.h"
#include "birdDecorator.h"
#include <list>
#include <cassert>

using namespace std;

class BirdDecorator;

/**********************
 * BIRD
 * Everything that can be shot
 **********************/
class Bird
{
   friend class BirdDecorator;
   friend class ApplyGravity;
   friend class SmallDrag;
   friend class LargeDrag;
   friend class Inertia;
   friend class KillOnLeave;
   friend class CrazyTurning;
   friend class AntiGravity;
   
protected:
   static Position dimensions; // size of the screen
   Position pt;                  // position of the flyer
   Velocity v;                // velocity of the flyer
   double radius;             // the size (radius) of the flyer
   bool dead;                 // is this flyer dead?
   int points;                // how many points is this worth?
   list<BirdDecorator*> decorators; //What quirks does each bird have?
   
public:
   Bird() : dead(false), points(0), radius(1.0) { }
   
   // setters
   void operator=(const Position    & rhs) { pt = rhs;    }
   void operator=(const Velocity & rhs) { v = rhs;     }
   void kill()                          { dead = true; }
   void setPoints(int pts)              { points = pts;}

   // getters
   bool isDead()           const { return dead;   }
   Position getPosition()     const { return pt;     }
   Velocity getVelocity()  const { return v;      }
   double getRadius()      const { return radius; }
   int getPoints() const { return points; }
   bool isOutOfBounds() const
   {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
              pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }

   // special functions
   virtual void draw() = 0;
   void advance();
   
};

/*********************************************
 * STANDARD
 * A standard bird: slows down, flies in a straight line
 *********************************************/
class Standard : public Bird
{
public:
    Standard(double radius = 25.0, double speed = 5.0, int points = 10);
    void draw();
//    void advance();
};

/*********************************************
 * FLOATER
 * A bird that floats like a balloon: flies up and really slows down
 *********************************************/
class Floater : public Bird
{
public:
    Floater(double radius = 30.0, double speed = 5.0, int points = 15);
    void draw();
//    void advance();
};

/*********************************************
 * CRAZY
 * A crazy flying object: randomly changes direction
 *********************************************/
class Crazy : public Bird
{
public:
    Crazy(double radius = 30.0, double speed = 4.5, int points = 30);
    void draw();
//    void advance();
};

/*********************************************
 * SINKER
 * A sinker bird: honors gravity
 *********************************************/
class Sinker : public Bird
{
public:
    Sinker(double radius = 30.0, double speed = 4.5, int points = 20);
    void draw();
//    void advance();
};



/*********************************************
 * APPLYGRAVITY
 *********************************************/
class ApplyGravity : public BirdDecorator
{
   void apply(Bird* self) override
   {
      self->v.addDy(-0.07);
   }
};

/******************************************************************
 * SMALLDRAG
 ****************************************************************/
class SmallDrag : public BirdDecorator
{
   void apply(Bird* self) override
   {
      self->v *= 0.995;
   }
};

/******************************************************************
 * LARGEDRAG
 ****************************************************************/
class LargeDrag : public BirdDecorator
{
   void apply(Bird* self) override
   {
      self->v *=  0.990; 
   }
};

/******************************************************************
 * INERTIA
 ****************************************************************/
class Inertia : public BirdDecorator
{
   void apply(Bird* self) override
   {
      self->pt.add(self->v);
  }
};

/******************************************************************
 * KILLONLEAVE
 ****************************************************************/
class KillOnLeave : public BirdDecorator
{
    void apply(Bird* self) override
   {
       if (self->isOutOfBounds()){
          self->kill();
          self->points *= -1; // points go negative when it is missed!
       }
   }
};

/******************************************************************
 * ANTIGRAVITY
 ****************************************************************/
class AntiGravity : public BirdDecorator
{
  void apply(Bird* self) override
   {
      self->v.addDy(0.05);
   }
};

/******************************************************************
 * CRAZYTURNING
 ****************************************************************/
class CrazyTurning : public BirdDecorator
{
   /******************************************************************
    * RANDOM
    * These functions generate a random number.
    ****************************************************************/
   int randomInt(int min, int max)
   {
      assert(min < max);
      int num = (rand() % (max - min)) + min;
      assert(min <= num && num <= max);
      return num;
   }
   double randomFloat(double min, double max)
   {
      assert(min <= max);
      double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
      assert(min <= num && num <= max);
      return num;
   }
   
  void apply(Bird* self) override
   {
      if (randomInt(0, 15) == 0)
      {
         self->v.addDy(randomFloat(-1.5, 1.5));
         self->v.addDx(randomFloat(-1.5, 1.5));
      }
   }
};
