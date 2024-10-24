#pragma once
#include <list>
class Effect;
class Bird;
class Bullet;
class Fragment;
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