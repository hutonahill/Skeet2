/***********************************************************************
 * Header File:
 *    Score
 * Author:
 *    Br. Helfrich
 * Summary:
 *    How well the player is doing - Not great
 ************************************************************************/

#pragma once
#include <string>
#include <list>
#include "bird.h"
#include "bullet.h"

class AbstractColleague;
class Bird;

struct Message {
   enum Type {BIRD_DIED, BULLET_FIRED, OUTOFBOUNDS} type;
   std::string value;
};

/**********************
 * STATUS
 * How well the player is doing
 **********************/
class Status
{
   friend class ScoreColleague;
public:
    Status() {}
    virtual std::string getText() const = 0;
    virtual void adjust(int value) = 0;
    virtual void reset() = 0;
    virtual ~Status() = default;
};

/**********************
 * SCORE
 * Points earned vs lost
 **********************/
class Score : public Status
{
public:
    Score() { reset(); }
    std::string getText() const override;
    void adjust(int value) override { points += value; }
    void reset() override{ points = 0; }
private:
    int points;
};




/**********************
 * HIT RATIO
 * Bird hit ratio
 **********************/
class HitRatio : public Status
{
public:
    HitRatio()  { reset(); }
    std::string getText() const;
    void adjust(int value);
    void reset() { numKilled = numMissed = 0; }
private:
    int numKilled;
    int numMissed;
};


/**********************
 * MEDIATOR
 * A container for a set of colleagues, notify method, and utility methods
 **********************/
class Mediator : public Status
{
public:
   
   virtual void notify(Message message) = 0;
   //enrolls the Concrete colleagues that will be communicating
   void enroll(AbstractColleague* colleague) {colleagues.push_back(colleague);}
   //unenrolls the Concrete colleagues that will be communicating
   void unenroll(AbstractColleague* colleague){colleagues.remove(colleague);}
   
protected:
   std::list<AbstractColleague*> colleagues;   //list of Colleagues enrolled in mediator
   
};

/**********************
 * ABSTRACT COLLEAGUE
 * A reference to several mediators, notify method, and utlity methods
 **********************/

class AbstractColleague : public Mediator
{
public:
   virtual void notify(Message message) = 0;
      //enrolls the Concrete colleagues that will be communicating
   void enroll(Mediator* mediator);
      //unenrolls the Concrete colleagues that will be communicating
   void unenroll(Mediator* mediator);
   void wentOutOfBounds() {};
protected:
   Mediator* mediator;
};


/**********************
 * HITRATIO COLLEAGUE
 **********************/
class HRColleague : public AbstractColleague
{
public:
   virtual void notify(Message message) override
   {
      if (message.type == Message::BIRD_DIED)
      {
         pStatus->adjust(std::stoi(message.value));
      }
   }
private:
   Status* pStatus;
};

/**********************
 * SCORE COLLEAGUE
 **********************/
class ScoreColleague : public AbstractColleague
{
public:

   virtual void notify(Message message) override
   {
      pStatus->adjust(std::stoi(message.value));
   }
   
private:
   Status* pStatus;
   
};

/**********************
 * BULLET COLLEAGUE
 **********************/
class BulletColleague : public AbstractColleague
{
public:
   virtual void notify(Message message) override;
   void wentOutOfBounds();
   void wasFired();
private:
   Bullet* pBullet;
};

/**********************
 * BIRD COLLEAGUE
 **********************/
class BirdColleague : public AbstractColleague
{
public:
   void notify(Message message) override;
   void wentOutOfBounds();
   void wasShot();
private:
   Bird* pBird;
};


