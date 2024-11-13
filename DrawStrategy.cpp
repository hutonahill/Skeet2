﻿#include "DrawStrategy.h"
#include "openGLIntegration.h"
#include "ElementStorage.h"
#include "gun.h"
#include <sstream>
#include "time.h"
#include <string>
#include "Storage.h"

//Draw bullet
void PelletDraw::draw(ElementStorage* elm)
{
   if (!elm->getDead())
      drawDot(elm->getPosition(), 3.0, 1.0, 1.0, 0.0);
}

void MissleDraw::draw(ElementStorage* elm)
{
   if (!elm->getDead())
   {
      // missile is a line with a dot at the end so it looks like fins.
      Position* ptNext(elm->getPosition());
      ptNext->add(elm->getVelocity());
      drawLine(elm->getPosition(), ptNext, 1.0, 1.0, 0.0);
      drawDot(elm->getPosition(), 3.0, 1.0, 1.0, 1.0);
   }
}

void BombDraw::draw(ElementStorage* elm)
{
   if (!elm->getDead())
   {
      // Bomb actually has a gradient to cut out the harsh edges
      drawDot(elm->getPosition(), elm->radius + 2.0, 0.50, 0.50, 0.00);
      drawDot(elm->getPosition(), elm->radius + 1.0, 0.75, 0.75, 0.00);
      drawDot(elm->getPosition(), elm->radius + 0.0, 0.87, 0.87, 0.00);
      drawDot(elm->getPosition(), elm->radius - 1.0, 1.00, 1.00, 0.00);
   }
}

void ShrapnelDraw::draw(ElementStorage* elm)
{
   if (!elm->getDead())
      drawDot(elm->getPosition(), elm->radius, 1.0, 1.0, 0.0);
}


//Draw Bird

void StandardBirdDraw::draw(ElementStorage* elm)
{
   if (!elm->getDead())
   {
      drawDisk(elm->getPosition(), elm->radius - 0.0, 1.0, 1.0, 1.0); // white outline
      drawDisk(elm->getPosition(), elm->radius - 3.0, 0.0, 0.0, 1.0); // blue center
   }
}

void SinkerBirdDraw::draw(ElementStorage* elm)
{
   if (!elm->getDead())
   {
      drawDisk(elm->getPosition(), elm->radius - 0.0, 0.0, 0.0, 0.8);
      drawDisk(elm->getPosition(), elm->radius - 4.0, 0.0, 0.0, 0.0);
   }
}

void FloaterBirdDraw::draw(ElementStorage* elm)
{
   if (!elm->getDead())
   {
      drawDisk(elm->getPosition(), elm->radius - 0.0, 0.0, 0.0, 1.0); // blue outline
      drawDisk(elm->getPosition(), elm->radius - 4.0, 1.0, 1.0, 1.0); // white center
   }
}

void CrazyBirdDraw::draw(ElementStorage* elm)
{
   if (!elm->getDead())
   {
      drawDisk(elm->getPosition(), elm->radius * 1.0, 0.0, 0.0, 1.0); // bright blue outside
      drawDisk(elm->getPosition(), elm->radius * 0.8, 0.2, 0.2, 1.0);
      drawDisk(elm->getPosition(), elm->radius * 0.6, 0.4, 0.4, 1.0);
      drawDisk(elm->getPosition(), elm->radius * 0.4, 0.6, 0.6, 1.0);
      drawDisk(elm->getPosition(), elm->radius * 0.2, 0.8, 0.8, 1.0); // almost white inside
   }
}

//Draw Effect

void FragmentDraw::draw(ElementStorage* elm)
{
   // Do nothing if we are already dead
   if (elm->getDead())
      return;

   // Draw this sucker
   glBegin(GL_TRIANGLE_FAN);

   // the color is a function of age - fading to black
   glColor3f((GLfloat)elm->getAge(), (GLfloat)elm->getAge(), (GLfloat)elm->getAge());

   // draw the fragment
   glVertex2f((GLfloat)(elm->getPosition()->getX() - elm->getRadius()), (GLfloat)(elm->getPosition()->getY() - elm->getRadius()));
   glVertex2f((GLfloat)(elm->getPosition()->getX() + elm->getRadius()), (GLfloat)(elm->getPosition()->getY() - elm->getRadius()));
   glVertex2f((GLfloat)(elm->getPosition()->getX() + elm->getRadius()), (GLfloat)(elm->getPosition()->getY() + elm->getRadius()));
   glVertex2f((GLfloat)(elm->getPosition()->getX() - elm->getRadius()), (GLfloat)(elm->getPosition()->getY() + elm->getRadius()));
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

void StreekDraw::draw(Effect* elm)
{
   // Do nothing if we are already dead
   if (elm->getDead())
      return;

   // Draw this sucker
   glBegin(GL_LINES);
   glColor3f((GLfloat)elm->getAge(), (GLfloat)elm->getAge(), (GLfloat)elm->getAge());

   // Draw the actual line
   glVertex2f((GLfloat)elm->getPosition().getX(), (GLfloat)elm->getPosition().getY());
   glVertex2f((GLfloat)elm->getEnd().getX(), (GLfloat)elm->getEnd().getY());

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

void exhaustDraw::draw(Effect* elm)
{
   // Do nothing if we are already dead
   if (elm->getDead())
      return;

   // Draw this sucker
   glBegin(GL_LINES);
   glColor3f((GLfloat)elm->getAge(), (GLfloat)elm->getAge(), (GLfloat)elm->getAge());

   // Draw the actual line
   glVertex2f((GLfloat)elm->getPosition()->getX(), (GLfloat)elm->getPosition()->getY());
   glVertex2f((GLfloat)elm->getEnd()->getX(), (GLfloat)elm->getEnd()->getY());

   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

void ScoreDraw::draw(ElementStorage* elm)
{
   if (elm->value == 0)
      return;

   void* pFont = GLUT_TEXT;

   // set the color
   GLfloat red = (elm->value <= 0.0 ? 1.0 : 0.0) * elm->getAge();
   GLfloat green = (elm->value <= 0.0 ? 0.0 : 1.0) * elm->getAge();
   GLfloat blue = 0.0;
   glColor3f(red, green, blue);

   // specify the position
   glRasterPos2f((GLfloat)elm->getPosition()->getX(), (GLfloat)elm->getPosition()->getY());

   // draw the digits
   int number = (elm->value > 0 ? elm->value : -elm->value);
   if (number / 10 != 0)
      glutBitmapCharacter(pFont, (char)(number / 10) + '0');
   glutBitmapCharacter(pFont, (char)(number % 10) + '0');
}


//Draw other
void gunDraw::draw(StorageGun* elm)
{
   drawRectangle(elm->getPosition(), M_PI_2 - elm->getAngle(), 10.0, 100.0, 1.0, 1.0, 1.0);
}

void StatusDraw::draw(Storage* elm)
{
   // output the text information
   ostringstream sout;
   if (elm->getTime()->isGameOver())
   {
      // draw the end of game message
      drawText(Position(elm->getDimensions()->getX() / 2 - 30, elm->getDimensions()->getY() / 2 + 10),
         "Game Over");

      // draw end of game status
      drawText(Position(elm->getDimensions()->getX() / 2 - 30, elm->getDimensions()->getY() / 2 - 10),
         to_string(elm->getPoints()));
   }
   else
   {
      // output the status elm->getTime()r
      drawTimer(1.0 - elm->getTime()->percentLeft(),
         (elm->getTime()->level() - 0.0) * .1, 0.0, 0.0,
         (elm->getTime()->level() - 1.0) * .1, 0.0, 0.0, elm->getDimensions());

      // draw the message giving a countdown
      sout << "Level " << elm->getTime()->level()
         << " begins in " << elm->getTime()->secondsLeft() << " seconds";
      drawText(Position(elm->getDimensions()->getX() / 2 - 110, elm->getDimensions()->getY() / 2 - 10),
         sout.str());
   }
}
