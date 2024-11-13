/***********************************************************************
 * Header File:
 *    ElementStorage
 * Author:
 *    Br. Helfrich
 * Summary:
 *    The storage of all entities/elements within the system
 ************************************************************************/

#pragma once
#include <string>
#include "position.h"
#include "score.h"


class SpecialMove;
class DrawStrategy;
class Timing;
class Bird;
class Bullet;
class OnDeath;
class Input;
class Effect;
class ElementLogic;

/**********************
 * ENTITY STORAGE
 * The storage of all entities/elements within the system
 **********************/
class ElementStorage {
   friend ElementLogic;
public:
   //Defining Quirks
   bool isBird;
   bool isBullet;
   bool isDead;
   double radius;
   double age; //1.0 = new, 0.0 = dead
   int points;
   int value;
   //Constructor
   ElementStorage(const bool isDead, const bool isBird, const bool isBullet, SpecialMove* sm, OnDeath* od, Input* arrow,
   	Timing* time, DrawStrategy* draw, double radius = 0) :
	   isBird(isBird), isBullet(isBullet), isDead(isDead), radius(radius), sm(sm), od(od), arrow(arrow), time(time),
	   draw(draw)
	{
	   
    }
   

   
   // getters
   SpecialMove* getSpecialMove()
                                    {return sm;           }
   Position* getPosition() const           {return objectPT;     }
   Velocity* getVelocity()           {return objectV;      }
   Input* getInput()                {return arrow;        }
   Timing* getTime()                {return time;         }
   DrawStrategy* getDraw()          {return draw;         }
   
   //Other valid functions
   bool getDead()         const         {return isDead;        }
   double getRadius()     const         {return radius;        }
   double getAge()                      {return age++;         }
   int getPoints()        const         {return points;        }
   int getValue()         const         {return value;         }
   //Setters
   void kill()                          {isDead = true;        }
   void setAge(double age)  {age = this->age;      }
   void setPoints(int points)  {points = this->points;}
   void setValue(int value)  {value = this->value;  }
   
   
   

protected:
   
   Position* objectPT;   //what is our position?
   Position* ptEnd;      //what is the end of an effect's position?
   Velocity* objectV;    //what is our velocity?
   Score* score;         //what is our value? How much will our score be affected?
   HitRatio* hr;         //what is our hit ratio?
   Effect* effect;      //what visual effects exist?
   
   
   SpecialMove*  sm;    //what special move do we execute?
   OnDeath* od;         //what do we do once we die? AKA how dramatic are we?
   Input*   arrow;      //what keys are pressed?
   Timing*  time;       //how much time do we have?
   DrawStrategy* draw;  //how we display the object
   
   
   
};

//age? Size? radius?
/**********************
 * BIRD
 **********************/
class Bird : public ElementStorage
{
public:
   Bird(SpecialMove* sm, OnDeath* od, Input* arrow, Timing* time, DrawStrategy* draw, double radius) :
	ElementStorage(false, true, false, sm, od, arrow, time, draw, radius) {
	   
   }
   
};

/**********************
 * BULLET
 **********************/
class Bullet : public ElementStorage
{
public:
   Bullet(SpecialMove* sm, OnDeath* od, Input* arrow, Timing* time,DrawStrategy* draw, double radius) :
	ElementStorage(false, false, true, sm, od, arrow, time, draw, radius) {}
   
};

/**********************
 * EFFECTS
 **********************/
class Effect : public ElementStorage
{
public:
   Effect(SpecialMove* sm, OnDeath* od, Input* arrow, Timing* time, DrawStrategy* draw, double radius, Position& ptEnd) :
	ElementStorage(false, false, false, sm, od, arrow, time, draw, radius) {}
   Position* getEnd() {return ptEnd;}
   void setEnd(Position* ptEnd) {ptEnd= this->ptEnd;}
   
};
