#include "Interface.h"
#include "openGLIntegration.h"
#include "DrawStrategy.h"
#include <sstream>

void Interface::drawLevel() const
{
   // output the background
   drawBackground(getTime().level() * .1, 0.0, 0.0);

   // output the gun
   drawGun();

   for (SkeetLogic::Iterator it = SkeetLogic->beginElement(); it != SkeetLogic->endElement(); ++it) {
      (*it)->draw();
   }

   // status
   drawText(Position(10, sl->getDimensions()->getY() - 30), to_string(sl->getPoints()));
   drawText(Position(sl->getDimensions()->getX() / 2 - 30, sl->getDimensions()->getY() - 30), getTime().getText());
   drawText(Position(sl->getDimensions()->getX() - 110, sl->getDimensions()->getY() - 30), to_string(sl->getHitRatio()));
}

void Interface::interact(const UserInput& ui)
{
   // gather input from the interface
   al->send(ui.isUp(), ui.isDown(), ui.isLeft(), ui.isRight());

   // a pellet can be shot at any time
   if (ui.isSpace())
      sl->makePellet();
   // missiles can be shot at level 2 and higher
   else if (ui.isM() && getLevel() > 1)
      sl->makeMissile();
   // bombs can be shot at level 3 and higher
   else if (ui.isB() && getLevel() > 2)
      sl->makeBomb();
}

void Interface::drawGun() const
{
   drawRectangle(sl->getGun()->getPosition(), M_PI_2 - sl->getGun()->getAngle(), 10.0, 100.0, 1.0, 1.0, 1.0);
}

void Interface::drawStatus() const
{
   // output the text information
   ostringstream sout;
   if (getTime().isGameOver())
   {
      // draw the end of game message
      drawText(Position(sl->getDimensions()->getX() / 2 - 30, sl->getDimensions()->getY() / 2 + 10),
         "Game Over");

      // draw end of game status
      drawText(Position(sl->getDimensions()->getX() / 2 - 30, sl->getDimensions()->getY() / 2 - 10),
         to_string(sl->getPoints()));
   }
   else
   {
      // output the status getTime()r
      drawTimer(1.0 - getTime().percentLeft(),
         (getTime().level() - 0.0) * .1, 0.0, 0.0,
         (getTime().level() - 1.0) * .1, 0.0, 0.0);

      // draw the message giving a countdown
      sout << "Level " << getTime().level()
         << " begins in " << getTime().secondsLeft() << " seconds";
      drawText(Position(sl->getDimensions()->getX() / 2 - 110, sl->getDimensions()->getY() / 2 - 10),
         sout.str());
   }
}

bool Interface::isPlaying() const
{
   return getTime().isPlaying();
}

/************************************************************************
 * DRAW Background
 * Fill in the background
 *  INPUT color   Background color
 *************************************************************************/
void Interface::drawBackground(double redBack, double greenBack, double blueBack) const
{
   glBegin(GL_TRIANGLE_FAN);

   // two rectangles is the fastest way to fill the screen.
   glColor3f((GLfloat)redBack /* red % */, (GLfloat)greenBack /* green % */, (GLfloat)blueBack /* blue % */);
   glVertex2f((GLfloat)0.0, (GLfloat)0.0);
   glVertex2f((GLfloat)sl->getDimensions()->getX(), (GLfloat)0.0);
   glVertex2f((GLfloat)sl->getDimensions()->getX(), (GLfloat)sl->getDimensions()->getY());
   glVertex2f((GLfloat)0.0, (GLfloat)sl->getDimensions()->getY());

   glEnd();
}

/************************************************************************
 * DRAW Timer
 * Draw a large timer on the screen
 *  INPUT percent     Amount of time left
 *        Foreground  Foreground color
 *        Background  Background color
 *************************************************************************/
void Interface::drawTimer(double percent,
   double redFore, double greenFore, double blueFore,
   double redBack, double greenBack, double blueBack) const
{
   double radians;

   GLfloat length = (GLfloat)sl->getDimensions()->getX();
   GLfloat half = length / (GLfloat)2.0;

   // do the background stuff
   drawBackground(redBack, greenBack, blueBack);

   // foreground stuff
   radians = percent * M_PI * 2.0;
   GLfloat x_extent = half + length * (GLfloat)sin(radians);
   GLfloat y_extent = half + length * (GLfloat)cos(radians);

   // get read to draw the triangles
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)redFore /* red % */, (GLfloat)greenFore /* green % */, (GLfloat)blueFore /* blue % */);
   glVertex2f(half, half);

   // fill in the triangles, one eight at a time
   switch ((int)(percent * 8.0))
   {
   case 7: // 315 - 360
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, length);
      break;
   case 6: // 270 - 315
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      glVertex2f(0.0, half);
      break;
   case 5: // 225 - 270
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(0.0, 0.0);
      break;
   case 4: // 180 - 225
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, 0.0);
      glVertex2f(half, 0.0);
      break;
   case 3: // 135 - 180
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      glVertex2f(length, 0.0);
      break;
   case 2: // 90 - 135 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      glVertex2f(length, half);
      break;
   case 1: // 45 - 90 degrees
      glVertex2f(half, length);
      glVertex2f(length, length);
      break;
   case 0: // 0 - 45 degrees
      glVertex2f(half, length);
      break;
   }
   glVertex2f(x_extent, y_extent);

   // complete drawing
   glEnd();

   // draw the red line now
   glBegin(GL_LINES);
   glColor3f((GLfloat)0.6, (GLfloat)0.0, (GLfloat)0.0);
   glVertex2f(half, half);
   glVertex2f(x_extent, y_extent);
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}


