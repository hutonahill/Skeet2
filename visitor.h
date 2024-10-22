#pragma once
#include <list>

class Visitor
{
public:
   Visitor(std::list<Effect*>* e) : effects(e) {};
   virtual void visit(Bird& b) = 0;
   virtual void visit(Bullet& b) = 0;
   virtual void visit(Fragment& f) = 0;
protected:
   std::list<Effect*>* effects;
};

class VisitDraw : public Visitor
{
   virtual void visit(Bird& b)
   {
      b.draw();
   }
   virtual void visit(Bullet& b)
   {
      b.output();
   }
   virtual void visit(Fragment& f)
   {
      f.render();
   }
};

class VisitMove : public Visitor
{
   virtual void visit(Bird& b)
   {
      b.advance();
   }
   virtual void visit(Bullet& b)
   {
      b.move(*effects);
   }
   virtual void visit(Fragment& f)
   {
      f.fly();
   }
};