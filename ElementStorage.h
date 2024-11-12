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
#include "bullet.h"
#include "bird.h"
#include "score.h"
#include "ElementLogic.h"
#include "Effect.h"


class SpecialMove;
class Timing;
class Bird;
class Bullet;
class OnDeath;
class Input;
class Effect;

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
   //Constructor
   ElementStorage(bool isDead, bool isBird, bool isBullet) : isDead(isDead), isBird(isBird), isBullet(isBullet){};
   
   // getters
   SpecialMove* getSpecialMove()
                          const         {return sm;      }
   Position getPosition() const         {return objectPT;}
   Velocity getVelocity() const         {return objectV; }
   Input* getInput()      const         {return arrow;   }
   Score getPoints()      const         {return score;   }
   Timing* getTime()      const         {return time;    }
   double getSize()     const           { return radius; }
   //Other valid functions
   bool getDead()          const        {return dead;    }
   void kill()                          {dead = true;    }
   
   
   

protected:
   
   ElementStorage(SpecialMove* sm, OnDeath* od, Input* arrow, Timing* time) : sm(sm), od(od), arrow(arrow), time(time) {};
   
   Position objectPT;   //what is our position?
   Velocity objectV;    //what is our velocity?
   Score score;         //what is our value? How much will our score be affected?
   HitRatio hr;         //what is our hit ratio?
   Effect* effect;      //what visual effects exist?
   
   
   SpecialMove*  sm;    //what special move do we execute?
   OnDeath* od;         //what do we do once we die? AKA how dramatic are we?
   Input*   arrow;      //what keys are pressed?
   Timing*  time;       //how much time do we have?
   
   bool dead;           //Are we dead?
   
};

/**********************
 * BIRD
 **********************/
class Bird : public ElementStorage
{
public:
   Bird() : ElementStorage(false, true, false) {};
   
};

/**********************
 * BULLET
 **********************/
class Bullet : public ElementStorage
{
public:
   Bullet() : ElementStorage(false, false, true) {};
   
};

/**********************
 * EFFECTS
 **********************/
class Effect : public ElementStorage
{
public:
   Effect() : ElementStorage(false, false, false) {};
   
};
