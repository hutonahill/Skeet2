/***********************************************************************
 * Header File:
 *    Abstract Draw : Entities that can be drawn
 * Author:
 *    Taemour and Jessica
 * Summary:
 *    Stuff that moves across the screen to be drawn
 ************************************************************************/


#pragma once
#include "bullet.h"
#include "bird.h"


class AbstractDraw
{
public:
   AbstractDraw()                           : bird(nullptr), bullet(nullptr) {}
   AbstractDraw(Bird* bird, Bullet* bullet) : bird(bird),    bullet(bullet)  {}
   AbstractDraw(Bird* bird)                 : bird(bird),    bullet(nullptr) {}
   AbstractDraw(Bullet* bullet)             : bird(nullptr), bullet(bullet)  {}
   virtual void draw() const = 0; //execute

   //getters

//   Position getPosition() const {return pt;}
//   Velocity getVelocity() const {return v;}
   
protected:
   Bird* bird;
   Bullet* bullet;

};

class BirdDraw : public AbstractDraw
{
public:
   BirdDraw(Bird* bird) : AbstractDraw(bird), bird(bird) {}
   virtual void draw() const = 0;
   bool getDead() const {return bird->isDead();}
   double getRadius() const {return bird->getRadius();}
   Position getPt() const {return bird->getPosition();}
   Velocity getV() const {return bird->getVelocity();}
   
private:
   Bird* bird;

};

class BulletDraw : public AbstractDraw
{
   
public:
   BulletDraw(Bullet* bullet) : AbstractDraw(bullet), bullet(bullet) {}
   virtual void draw() const = 0;
   bool getDead() const {return bullet->isDead();}
   double getRadius() const {return bullet->getRadius();}
   Position getPt() const {return bullet->getPosition();}
   Velocity getV() const {return bullet->getVelocity();}

   
private:
   Bullet* bullet;
};


/***********
BIRD DRAW
***********/
class StandardDraw : public BirdDraw
{
public:
   StandardDraw(Bird* bird) : BirdDraw(bird) {}
   virtual void draw() const;
};

class SinkerDraw : public BirdDraw
{
public:
   SinkerDraw(Bird* bird) : BirdDraw(bird) {}
   virtual void draw() const;
};

class FloaterDraw : public BirdDraw
{
public:
   FloaterDraw(Bird* bird) : BirdDraw(bird) {}
   virtual void draw() const;
}; 

class CrazyDraw : public BirdDraw
{
public:
   CrazyDraw(Bird* bird) : BirdDraw(bird) {}
   virtual void draw() const;
}; 

/***********
BULLET DRAW
***********/
class PelletDraw : public BulletDraw
{
public:
   PelletDraw(Bullet* bullet) : BulletDraw(bullet) {}
   virtual void draw() const;
};

class MissileDraw : public BulletDraw
{
public:
   MissileDraw(Bullet* bullet) : BulletDraw(bullet) {}
   virtual void draw() const;
}; 

class BombDraw : public BulletDraw
{
public:
   BombDraw(Bullet* bullet) : BulletDraw(bullet) {}
   virtual void draw() const;
}; 

class ShrapnelDraw : public BulletDraw
{
public:
   ShrapnelDraw(Bullet* bullet) : BulletDraw(bullet) {}
   virtual void draw() const;
};
