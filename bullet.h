/***********************************************************************
 * Header File:
 *    Bullet
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Stuff that kills other things
 ************************************************************************/

#pragma once
#include "position.h"
#include "effect.h"
#include <list>
#include <cassert>
#include "Element.h"

/*********************************************
 * BULLET
 * Something to shoot something else
 *********************************************/
class Bullet : public Element
{
protected:
   static Position dimensions;   // size of the screen
   Position pt;                 // position of the bullet
   Velocity v;                   // velocity of the bullet
   double radius;                // the size (radius) of the bullet
   bool dead;                    // is this bullet dead?
   int value;                    // how many points does this cost?
    
public:
   Bullet(double angle = 0.0, double speed = 30.0, double radius = 5.0, int value = 1);
   
   // setters
   void kill()                   { dead = true; }
   void setValue(int newValue)   { value = newValue; }
   
   // getters
   bool isDead()            const override { return dead;   }
   Position& getPosition()  override { return pt;     }
   Velocity& getVelocity()  override { return v;      }
   double getRadius()       const override { return radius; }
   int getPointValue()      const { return value;  }

   // special functions
   virtual void death(std::list<Bullet *> & bullets) {}
   virtual void input(bool isUp, bool isDown, bool isB) {}
   virtual void move(std::list<Effect*> &effects);

protected:
   bool isOutOfBounds() const
   {
      return (pt.getX() < -radius || pt.getX() >= dimensions.getX() + radius ||
         pt.getY() < -radius || pt.getY() >= dimensions.getY() + radius);
   }
   int    random(int    min, int    max);
   double random(double min, double max);
};

/*********************
 * PELLET
 * Small little bullet
 **********************/
class Pellet : public Bullet
{
public:
   Pellet(double angle, double speed = 15.0) : Bullet(angle, speed, 1.0, 1) {}
   
   elementType getType() const override {return PELLET;}
};

/*********************
 * BOMB
 * Things that go "boom"
 **********************/
class Bomb : public Bullet
{
private:
   int timeToDie;
public:
   Bomb(double angle, double speed = 10.0) : Bullet(angle, speed, 4.0, 4), timeToDie(60) {}
   
   void move(std::list<Effect*> & effects) override;
   void death(std::list<Bullet *> & bullets) override;

   elementType getType() const override {return BOMB;}
};

/*********************
 * Shrapnel
 * A piece that broke off of a bomb
 **********************/
class Shrapnel : public Bullet
{
private:
   int timeToDie;
public:
   Shrapnel(Bomb & bomb)
   {
      // how long will this one live?
      timeToDie = random(5, 15);
      
      // The speed and direction is random
      v.set(random(0.0, 6.2), random(10.0, 15.0));
      pt = bomb.getPosition();

      value = 0;
      
      radius = 3.0;
   }
   
   void move(std::list<Effect*> & effects) override;

   elementType getType() const override {return SHRAPNEL;}
};


/*********************
 * MISSILE
 * Guided missiles
 **********************/
class Missile : public Bullet
{
public:
   Missile(double angle, double speed = 10.0) : Bullet(angle, speed, 1.0, 3) {}
   
   void input(bool isUp, bool isDown, bool isB) override {
      if (isUp)
         v.turn(0.04);
      if (isDown)
         v.turn(-0.04);
   }
   void move(std::list<Effect*> & effects) override;

   elementType getType() const override {return MISSILE;}
};
