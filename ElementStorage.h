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


class SpecialMove;
class Timing;
class Bird;
class Bullet;
class OnDeath;
class Input;

/**********************
 * ENTITY STORAGE
 * The storage of all entities/elements within the system
 **********************/
class ElementStorage {
   friend ElementLogic;
public:
   bool isBird;
   bool isBullet;
   ElementStorage() : isBird(true) {};
   void specialMove();
      // getters
   Position getPosition()  const        { return objectPT; }
   Velocity getVelocity() const        {return objectV;}
   bool isDead() const                  {return dead;}
   void kill()                          { dead = true; }

protected:
   Position objectPT;   //what is our position?
   Velocity objectV;    //what is our velocity?
   Score score;
   SpecialMove*  sm;
   OnDeath* od;
   Input*   arrow;
   Timing*  time;
   bool dead;
   
};



