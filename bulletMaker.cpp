#include "bulletMaker.h"

bool PelletMaker::makeBullet(Bullet*& bullet, const UserInput& ui, int time, double angle)
{
   if (ui.isSpace())
   {
      bullet = new Pellet(angle);

      return true;
   }

   return false;
}

bool MissleMaker::makeBullet(Bullet*& bullet, const UserInput& ui, int time, double angle)
{
   if (ui.isM() && time > 1)
   {
      bullet = new Missile(angle);

      return true;
   }

   return false;
}

bool BombMaker::makeBullet(Bullet*& bullet, const UserInput& ui, int time, double angle)
{
   if (ui.isB() && time > 2)
   {
      bullet = new Bomb(angle);

      return true;
   }

   return false;
}