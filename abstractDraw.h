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


class abstractDraw
{
public:
   abstractDraw(Bird* bird, Bullet* bullet) : bird(bird), bullet(bullet) {}
   abstractDraw(Bird* bird) : bird(bird) {}
   abstractDraw(Bullet* bullet) : bullet(bullet) {}
   virtual void draw() = 0;
   bool isDead;
   double radius;
   //getters
   
   bool getDead() const {return isDead;}
   double getRadius() const {return radius;}
   Position getPosition() const {return pt;}
   Velocity getVelocity() const {return v;}
   
protected:
   Bird* bird;
   Bullet* bullet;
   Position pt;
   Velocity v;
};

class birdDraw : public abstractDraw
{
public:
   birdDraw(Bird* bird) : abstractDraw(bird) {}
   virtual void draw() = 0;

private:
   Bird* bird;
};

class bulletDraw : public abstractDraw
{
   
public:
   bulletDraw(Bullet* bullet) : abstractDraw(bullet) {}
   virtual void draw() = 0;

   
private:
   Bullet* bullet;
};


/***********
BIRD DRAW
***********/
class standardDraw : public birdDraw
{
public:
   virtual void draw() = 0;
};

class sinkerDraw : public birdDraw
{
public:
   virtual void draw() = 0;
};

class floaterDraw : public birdDraw
{
public:
   virtual void draw() = 0;
}; 

class crazyDraw : public birdDraw
{
public:
   virtual void draw() = 0;
}; 

/***********
BULLET DRAW
***********/
class pelletDraw : public bulletDraw
{
public:
   virtual void draw() = 0;
};

class missileDraw : public bulletDraw
{
public:
   virtual void draw() = 0;
}; 

class bombDraw : public bulletDraw
{
public:
   virtual void draw() = 0;
}; 

class shrapnelDraw : public bulletDraw
{
public:
   virtual void draw() = 0;
};
