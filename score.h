/***********************************************************************
 * Header File:
 *    Score
 * Author:
 *    Br. Helfrich
 * Summary:
 *    How well the player is doing
 ************************************************************************/

#pragma once
#include <string>
#include <list>

struct Message {
   //type
   //value
};

/**********************
 * STATUS
 * How well the player is doing
 **********************/
class Status
{
public:
    Status() {}
    virtual std::string getText() const = 0;
    virtual void adjust(int value) = 0;
    virtual void reset() = 0;
};

/**********************
 * SCORE
 * Points earned vs lost
 **********************/
class Score : public Status
{
public:
    Score() { reset(); }
    std::string getText() const;
    void adjust(int value) { points += value; }
    void reset() { points = 0; }
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
class Meditator : public Status
{
public:
   
   virtual void notify(Message);
   //enrolls the Concrete colleagues that will be communicating
   void enroll(Meditator);
   //unenrolls the Concrete colleagues that will be communicating
   void unenroll(Meditator);
   
protected:
   std::list<Meditator*> colleagues;   //list of Colleagues enrolled in mediator
   
};

/**********************
 * ABSTRACT COLLEAGUE
 * A reference to several mediators, notify method, and utlity methods
 **********************/

class AbstractColleague : public Meditator
{
public:
   virtual void notify(Message) = 0;
      //enrolls the Concrete colleagues that will be communicating
   void enroll(Meditator);
      //unenrolls the Concrete colleagues that will be communicating
   void unenroll(Meditator);
protected:
   
};

/**********************
 * HITRATIO COLLEAGUE
 **********************/
class HRColleague : public Status
{
public:
   virtual void notify(Message);
   
};
/**********************
 * SCORE COLLEAGUE
 **********************/
class ScoreColleague : public Status
{
public:
   virtual void notify(Message);
};
/**********************
 * BULLET COLLEAGUE
 **********************/
class BulletColleague : public Status
{
public:
   virtual void notify(Message);
   void wentOutOfBounds();
};

/**********************
 * BIRD COLLEAGUE
 **********************/
class BirdColleague : public Status
{
public:
   void notify(Message);
   void wentOutOfBounds();
   void wasShot();
};
