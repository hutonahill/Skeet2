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


class SpecialMove;
class Timing;


/**********************
 * ENTITY STORAGE
 * The storage of all entities/elements within the system
 **********************/
class ElementStorage {
public:
   bool isBird;
   bool isBullet;
   ElementStorage() : isBird(true), {} ;
   void specialMove();
   void execute();
   SpecialMove getSpecial() const{ return sm;}
   
      // getters
   Position getPosition()  const { return objectPT;     }
  
   
   
   
protected:
   Position objectPT;
   Bird* bird;
   Bullet* bullet;
   SpecialMove*  sm;
   Score* score;
   OnDeath* od;
   Input*      arrow;
   Timing*  time;
   
};



