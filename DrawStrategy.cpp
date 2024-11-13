#include "DrawStrategy.h"
#include "openGLIntegration.h"
#include "ElementStorage.h"
#include <sstream>

//Draw bullet
void PelletDraw::draw(ElementStorage* elm)
{
   if (!elm->isDead())
      drawDot(elm->pt, 3.0, 1.0, 1.0, 0.0);
}

void MissleDraw::draw(ElementStorage* elm)
{
   if (!elm->isDead())
   {
      // missile is a line with a dot at the end so it looks like fins.
      Position ptNext(elm->pt);
      ptNext.add(elm->v);
      drawLine(elm->pt, ptNext, 1.0, 1.0, 0.0);
      drawDot(elm->pt, 3.0, 1.0, 1.0, 1.0);
   }
}

void BombDraw::draw(ElementStorage* elm)
{
   if (!elm->isDead())
   {
      // Bomb actually has a gradient to cut out the harsh edges
      drawDot(elm->pt, elm->radius + 2.0, 0.50, 0.50, 0.00);
      drawDot(elm->pt, elm->radius + 1.0, 0.75, 0.75, 0.00);
      drawDot(elm->pt, elm->radius + 0.0, 0.87, 0.87, 0.00);
      drawDot(elm->pt, elm->radius - 1.0, 1.00, 1.00, 0.00);
   }
}

void ShrapnelDraw::draw(ElementStorage* elm)
{
   if (!elm->isDead())
      drawDot(elm->pt, elm->radius, 1.0, 1.0, 0.0);
}


//Draw Bird

void StandardBirdDraw::draw(ElementStorage* elm)
{
   if (!elm->isDead())
   {
      drawDisk(elm->pt, elm->radius - 0.0, 1.0, 1.0, 1.0); // white outline
      drawDisk(elm->pt, elm->radius - 3.0, 0.0, 0.0, 1.0); // blue center
   }
}

void SinkerBirdDraw::draw(ElementStorage* elm)
{
   if (!elm->isDead())
   {
      drawDisk(elm->pt, elm->radius - 0.0, 0.0, 0.0, 0.8);
      drawDisk(elm->pt, elm->radius - 4.0, 0.0, 0.0, 0.0);
   }
}

void FloaterBirdDraw::draw(ElementStorage* elm)
{
   if (!elm->isDead())
   {
      drawDisk(elm->pt, elm->radius - 0.0, 0.0, 0.0, 1.0); // blue outline
      drawDisk(elm->pt, elm->radius - 4.0, 1.0, 1.0, 1.0); // white center
   }
}

void CrazyBirdDraw::draw(ElementStorage* elm)
{
   if (!elm->isDead())
   {
      drawDisk(elm->pt, elm->radius * 1.0, 0.0, 0.0, 1.0); // bright blue outside
      drawDisk(elm->pt, elm->radius * 0.8, 0.2, 0.2, 1.0);
      drawDisk(elm->pt, elm->radius * 0.6, 0.4, 0.4, 1.0);
      drawDisk(elm->pt, elm->radius * 0.4, 0.6, 0.6, 1.0);
      drawDisk(elm->pt, elm->radius * 0.2, 0.8, 0.8, 1.0); // almost white inside
   }
}

//Draw Effect

void FragmentDraw::draw(ElementStorage* elm)
{
   // Do nothing if we are already dead
   if (elm->isDead())
      return;

   // Draw this sucker
   glBegin(GL_TRIANGLE_FAN);

   // the color is a function of age - fading to black
   glColor3f((GLfloat)elm->age, (GLfloat)elm->age, (GLfloat)elm->age);

   // draw the fragment
   glVertex2f((GLfloat)(elm->pt.getX() - elm->size), (GLfloat)(elm->pt.getY() - elm->size));
   glVertex2f((GLfloat)(elm->pt.getX() + elm->size), (GLfloat)(elm->pt.getY() - elm->size));
   glVertex2f((GLfloat)(elm->pt.getX() + elm->size), (GLfloat)(elm->pt.getY() + elm->size));
   glVertex2f((GLfloat)(elm->pt.getX() - elm->size), (GLfloat)(elm->pt.getY() + elm->size));
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

void StreekDraw::draw(ElementStorage* elm)
{
   // Do nothing if we are already dead
   if (elm->isDead())
      return;

   // Draw this sucker
   glBegin(GL_LINES);
   glColor3f((GLfloat)elm->age, (GLfloat)elm->age, (GLfloat)elm->age);

   // Draw the actual line
   glVertex2f((GLfloat)elm->pt.getX(), (GLfloat)elm->pt.getY());
   glVertex2f((GLfloat)elm->ptEnd.getX(), (GLfloat)elm->ptEnd.getY());

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

void exhaustDraw::draw(ElementStorage* elm)
{
   // Do nothing if we are already dead
   if (elm->isDead())
      return;

   // Draw this sucker
   glBegin(GL_LINES);
   glColor3f((GLfloat)elm->age, (GLfloat)elm->age, (GLfloat)elm->age);

   // Draw the actual line
   glVertex2f((GLfloat)elm->pt.getX(), (GLfloat)elm->pt.getY());
   glVertex2f((GLfloat)elm->ptEnd.getX(), (GLfloat)elm->ptEnd.getY());

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

void ScoreDraw::draw(ElementStorage* elm)
{
   if (elm->value == 0)
      return;

   void* pFont = GLUT_TEXT;

   // set the color
   GLfloat red = (elm->value <= 0.0 ? 1.0 : 0.0) * elm->age;
   GLfloat green = (elm->value <= 0.0 ? 0.0 : 1.0) * elm->age;
   GLfloat blue = 0.0;
   glColor3f(red, green, blue);

   // specify the position
   glRasterPos2f((GLfloat)elm->pos.getX(), (GLfloat)elm->pos.getY());

   // draw the digits
   int number = (elm->value > 0 ? elm->value : -elm->value);
   if (number / 10 != 0)
      glutBitmapCharacter(pFont, (char)(number / 10) + '0');
   glutBitmapCharacter(pFont, (char)(number % 10) + '0');
}


//Draw other
void gunDraw::draw(ElementStorage* elm)
{
   drawRectangle(elm->pos, M_PI_2 - elm->angle, 10.0, 100.0, 1.0, 1.0, 1.0);
}

void StatusDraw::draw(ElementStorage* elm)
{
   // output the text information
   ostringstream sout;
   if (elm->time.isGameOver())
   {
      // draw the end of game message
      drawText(Position(elm->dimensions.getX() / 2 - 30, elm->dimensions.getY() / 2 + 10),
         "Game Over");

      // draw end of game status
      drawText(Position(elm->dimensions.getX() / 2 - 30, elm->dimensions.getY() / 2 - 10),
         elm->score.getText());
   }
   else
   {
      // output the status timer
      drawTimer(1.0 - elm->time.percentLeft(),
         (elm->time.level() - 0.0) * .1, 0.0, 0.0,
         (elm->time.level() - 1.0) * .1, 0.0, 0.0, elm->dimensions);

      // draw the message giving a countdown
      sout << "Level " << elm->time.level()
         << " begins in " << elm->time.secondsLeft() << " seconds";
      drawText(Position(elm->dimensions.getX() / 2 - 110, elm->dimensions.getY() / 2 - 10),
         sout.str());
   }
}
