#include "ElementLogic.h"
#include "ElementStorage.h"
#include "Interface.h"
#include "ArrowListener.h"
#include "position.h"
#include <cassert>

#include "SkeetLogic.h"

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
double RandomFloat(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
   assert(min <= num && num <= max);
   return num;
}


void StandardBirdMove::execute(ElementStorage* el)
{
      // small amount of drag
   (*(el->getVelocity())) *= 0.995;
   
      // inertia
   el->getPosition()->add(el->getVelocity());
}

void FloaterBirdMove::execute(ElementStorage* el)
{
      // large amount of drag
   (*(el->getVelocity())) *= 0.990;
   
      // inertia
   el->getPosition()->add(el->getVelocity());
   
      // anti-gravity
   el->getVelocity()->addDy(0.05);
}

void SinkerBirdMove::execute(ElementStorage* el)
{
      // gravity
   el->getVelocity()->addDy(-0.07);
   
      // inertia
   el->getPosition()->add(el->getVelocity());
}

void CrazyBirdMove::execute(ElementStorage* el)
{
      // erratic turns eery half a second or so
   if (randomInt(0, 15) == 0)
   {
      el->getVelocity()->addDy(RandomFloat(-1.5, 1.5));
      el->getVelocity()->addDx(RandomFloat(-1.5, 1.5));
   }
   
      // inertia
   el->getPosition()->add(el->getVelocity());
}

void PelletMove::execute(ElementStorage* el)
{
      // inertia
   
   el->getPosition()->add(el->getVelocity());
}

void MissleMove::execute(ElementStorage* el)
{
   if (el->getInput()->up)
      el->getVelocity()->turn(0.04);
   if (el->getInput()->down)
      el->getVelocity()->turn(-0.04);
      // inertia
   el->getPosition()->add(el->getVelocity());
}

void NoneMove::execute(ElementStorage* el)
{
}

void EffectDeath::execute(ElementStorage* el)
{
   // This would add bird fragments if it were implimented
}

void DisapearDeath::execute(ElementStorage* el)
{
   el->isDead = true;
}

void ShrapnelDeath::execute(ElementStorage* el)
{
   // for bombs, should spawn some shrapnel
   int numFragments = 25;
   for (int i = 0; i < numFragments; i++) {
      ElementsToSpawn->push_back(SkeetLogic::Fragment(el->getPosition(), el->getVelocity()));
   }
}

void Arrows::execute(ElementStorage* el)
{
}

void Arrows::subscribe(ArrowListener* al)
{
   al->subscribe(this);
}

void Arrows::unsubscribe(ArrowListener* al)
{
   al->unsubscribe(this);
}

void NoInput::execute(ElementStorage* el)
{
}

void NoInput::subscribe(ArrowListener* al)
{
}

void NoInput::unsubscribe(ArrowListener* al)
{
}

void NotTimed::execute(ElementStorage* el)
{
}

void Timed::execute(ElementStorage* el)
{
   timeToDie--;
   if (!timeToDie)
      el->kill();
}
