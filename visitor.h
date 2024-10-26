#pragma once
#include <list>
class Bird;
class Bullet;
class Effect;
class FlyingObject;
class Fragment;
class HitRatio;
class Points;
class Score;
class UserInput;

class Visitor
{
public:
   virtual void visit(Bird& b) = 0;
   virtual void visit(Bullet& b) = 0;
   virtual void visit(Fragment& f) = 0;
};

class VisitDraw : public Visitor
{
public:
   virtual void visit(Bird& b);
   virtual void visit(Bullet& b);
   virtual void visit(Fragment& f);
};

class VisitMove : public Visitor
{
public:
   VisitMove(std::list<Effect*>* e) : effects(e) {};
   virtual void visit(Bird& b);
   virtual void visit(Bullet& b);
   virtual void visit(Fragment& f);
protected:
   std::list<Effect*>* effects;
};

class VisitInput : public Visitor
{
public:
   VisitInput(const UserInput& ui) : ui(ui) {};
   virtual void visit(Bird& b) {};
   virtual void visit(Bullet& b);
   virtual void visit(Fragment& f) {};
protected:
   const UserInput& ui;
};

class VisitBirdDetect : public Visitor
{
public:
   VisitBirdDetect(HitRatio& hitRatio, std::list<FlyingObject*>& fo) : flyingObjects(fo), hitRatio(hitRatio) {};
   virtual void visit(Bird& b);
   virtual void visit(Bullet& b) {};
   virtual void visit(Fragment& f) {};
protected:
   std::list<FlyingObject*>& flyingObjects;
   HitRatio& hitRatio;
};

class VisitBulletDetect : public Visitor
{
public:
   VisitBulletDetect(Bird& b, HitRatio& hitRatio, std::list<FlyingObject*>& fo) : bird(b), hitRatio(hitRatio), flyingObjects(fo) {};
   virtual void visit(Bird& b) {};
   virtual void visit(Bullet& b);
   virtual void visit(Fragment& f) {};
protected:
   Bird& bird;
   HitRatio& hitRatio;
   std::list<FlyingObject*>& flyingObjects;
};

class VisitDeath : public Visitor
{
public:
   VisitDeath(Score&s, std::list<Points>& p, std::list<FlyingObject*>::iterator& it, std::list<FlyingObject*>& fo) : score(s), points(p), it(it), flyingObjects(fo) {};
   virtual void visit(Bird& b);
   virtual void visit(Bullet& b);
   virtual void visit(Fragment& f);
protected:
   Score& score;
   std::list<Points>& points;
   std::list<FlyingObject*>::iterator& it;
   std::list<FlyingObject*>& flyingObjects;
};

class VisitBirdCount : public Visitor
{
public:
   VisitBirdCount() : count(0) {};
   virtual void visit(Bird& b) { count++; }
   virtual void visit(Bullet& b) {}
   virtual void visit(Fragment& f) {}
   bool const operator == (const int& rhs) { return count == rhs; }
protected:
   int count;
};