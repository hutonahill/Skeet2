#include "visitor.h"
#include "bird.h"
#include "bullet.h"
#include "uiInteract.h"
#include "score.h"
#include "points.h"

void VisitDraw::visit(Bird& b)
{
   b.draw();
}

void VisitDraw::visit(Bullet& b)
{
   b.output();
}

void VisitDraw::visit(Fragment& f)
{
   f.render();
}

void VisitMove::visit(Bird& b)
{
   b.advance();
}

void VisitMove::visit(Bullet& b)
{
   b.move(*effects);
}

void VisitMove::visit(Fragment& f)
{
   f.fly();
}

void VisitInput::visit(Bullet& b)
{
   b.input(ui.isUp() + ui.isRight(), ui.isDown() + ui.isLeft(), ui.isB());
}

void VisitBulletDetect::visit(Bullet& b)
{
   if (!b.isDead() &&
      bird.getRadius() + b.getRadius() >
      minimumDistance(bird.getPosition(), bird.getVelocity(),
         b.getPosition(), b.getVelocity()))
   {
      for (int i = 0; i < 25; i++)
         flyingObjects.push_back(new Fragment(b.getPosition(), b.getVelocity()));
      bird.kill();
      b.kill();
      hitRatio.adjust(1);
      b.setValue(-(bird.getPoints()));
      bird.setPoints(0);
   }
}

void VisitBirdDetect::visit(Bird& b)
{

   VisitBulletDetect vb = VisitBulletDetect(b, hitRatio, flyingObjects);
   if (!b.isDead())
   {
      for (auto element : flyingObjects)
      {
         element->accept(vb);
      }
   }
}

void VisitDeath::visit(Bird& b)
{
   if (b.isDead())
   {
      if (b.getPoints())
         points.push_back(Points(b.getPosition(), b.getPoints()));
      score.adjust(b.getPoints());
      it = flyingObjects.erase(it);
   }
   else
   {
      it++;
   }
}

void VisitDeath::visit(Bullet& b)
{
   if (b.isDead())
   {
      b.death(flyingObjects);
      int value = -b.getValue();
      points.push_back(Points(b.getPosition(), value));
      score.adjust(value);
      it = flyingObjects.erase(it);
   }
   else
      ++it;
}

void VisitDeath::visit(Fragment& f)
{
   if (f.isDead())
      it = flyingObjects.erase(it);
   else
      ++it;
}
