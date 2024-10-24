#include "visitor.h"
#include "bird.h"
#include "bullet.h"
#include "uiInteract.h"

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
