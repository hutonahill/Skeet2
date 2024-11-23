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
   virtual void draw() = 0; //execute

   //getters

//   Position getPosition() const {return pt;}
//   Velocity getVelocity() const {return v;}
   
protected:
   Bird* bird;
   Bullet* bullet;

};

class birdDraw : public abstractDraw
{
public:
   birdDraw(Bird* bird) : abstractDraw(bird) {}
   virtual void draw() = 0;
   bool getDead() const {return bird->isDead();}
   double getRadius() const {return bird->getRadius();}
   Position getPt() const {return bird->getPosition();}
   Velocity getV() const {return bird->getVelocity();}
   
private:
   Bird* bird;

};

class bulletDraw : public abstractDraw
{
   
public:
   bulletDraw(Bullet* bullet) : abstractDraw(bullet) {}
   virtual void draw() = 0;
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
class standardDraw : public birdDraw
{
public:
   standardDraw(Bird* bird) : birdDraw(bird) {}
   virtual void draw() = 0;
};

class sinkerDraw : public birdDraw
{
public:
   sinkerDraw(Bird* bird) : birdDraw(bird) {}
   virtual void draw() = 0;
};

class floaterDraw : public birdDraw
{
public:
   floaterDraw(Bird* bird) : birdDraw(bird) {}
   virtual void draw() = 0;
}; 

class crazyDraw : public birdDraw
{
public:
   crazyDraw(Bird* bird) : birdDraw(bird) {}
   virtual void draw() = 0;
}; 

/***********
BULLET DRAW
***********/
class pelletDraw : public bulletDraw
{
public:
   pelletDraw(Bullet* bullet) : bulletDraw(bullet) {}
   virtual void draw() = 0;
};

class missileDraw : public bulletDraw
{
public:
   missileDraw(Bullet* bullet) : bulletDraw(bullet) {}
   virtual void draw() = 0;
}; 

class bombDraw : public bulletDraw
{
public:
   bombDraw(Bullet* bullet) : bulletDraw(bullet) {}
   virtual void draw() = 0;
}; 

class shrapnelDraw : public bulletDraw
{
public:
   shrapnelDraw(Bullet* bullet) : bulletDraw(bullet) {}
   virtual void draw() = 0;
};