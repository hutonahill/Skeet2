#include "ElementLogic.h"
#include "ElementStorage.h"
#include "Interface.h"
#include "position.h"
#include <cassert>

/***************************************************************/
/***************************************************************/
/*                             MISC.                           */
/***************************************************************/
/***************************************************************/


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


void StandardBirdMove::execute(ElementStorage* el)
{
   // small amount of drag
   el->v *= 0.995;

   // inertia
   el->pt.add(el->v);

   // out of bounds checker
   if (el->isOutOfBounds())
   {
      el->isDead = true;
      el->points *= -1; // points go negative when it is missed!
   }
}

void FloaterBirdMove::execute(ElementStorage* el)
{
   // large amount of drag
   el->v *= 0.990;

   // inertia
   el->pt.add(el->v);

   // anti-gravity
   el->v.addDy(0.05);

   // out of bounds checker
   if (el->isOutOfBounds())
   {
      el->isDead = true;
      el->points *= -1; // points go negative when it is missed!
   }
}

void SinkerBirdMove::execute(ElementStorage* el)
{
   // gravity
   el->v.addDy(-0.07);

   // inertia
   el->pt.add(el->v);

   // out of bounds checker
   if (el->isOutOfBounds())
   {
      el->isDead = true;
      el->points *= -1; // points go negative when it is missed!
   }
}

void CrazyBirdMove::execute(ElementStorage* el)
{
   // erratic turns eery half a second or so
   if (randomInt(0, 15) == 0)
   {
      el->v.addDy(randomFloat(-1.5, 1.5));
      el->v.addDx(randomFloat(-1.5, 1.5));
   }

   // inertia
   pt.add(v);

   // out of bounds checker
   if (isOutOfBounds())
   {
      el->isDead = true;
      points *= -1; // points go negative when it is missed!
   }
}

void PelletMove::execute(ElementStorage* el)
{
   // inertia
   el->pt.add(el->v);
   // out of bounds checker
   if (el->isOutOfBounds())
      el->isDead = true;
}

void MissleMove::execute(ElementStorage* el)
{
   if (el->input->up) 
      el->v.turn(0.04);
   if (el->input->down)
      el->v.turn(-0.04);
   // inertia
   el->pt.add(el->v);
   // out of bounds checker
   if (el->isOutOfBounds())
      el->isDead = true;
}

void NoneMove::execute(ElementStorage* el)
{
   // inertia
   el->pt.add(el->v);
}

void EffectDeath::execute(ElementStorage* el)
{
}

void DisapearDeath::execute(ElementStorage* el)
{
}

void ShrapnelDeath::execute(ElementStorage* el)
{
}

void Arrows::execute(ElementStorage* el)
{
}

void Arrows::subscribe(ArrowListener* al)
{
   al = al->subscribe(this);
}

void Arrows::unsubscribe(ArrowListener* al)
{
   al->unsubscribe(this);
}

void None::execute(ElementStorage* el)
{
}

void None::subscribe(ArrowListener* al)
{
}

void None::unsubscribe(ArrowListener* al)
{
}

void NotTimed::execute(ElementStorage* el)
{
}

void Timed::execute(ElementStorage* el)
{
   timeToDie--;
   if (!timeToDie)
      el->isDead = true;
}
