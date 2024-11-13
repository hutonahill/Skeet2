#include "DrawStrategy.h"
#include "openGLIntegration.h"
#include "ElementStorage.h"
#include <sstream>
#include "time.h"
#include <string>

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
   glColor3f(static_cast<GLfloat>(elm->getAge()), static_cast<GLfloat>(elm->getAge()), static_cast<GLfloat>(elm->getAge()));

   // draw the fragment
   glVertex2f(static_cast<GLfloat>(elm->getPosition()->getX() - elm->getRadius()), static_cast<GLfloat>(elm->getPosition()->getY() - elm->getRadius()));
   glVertex2f(static_cast<GLfloat>(elm->getPosition()->getX() + elm->getRadius()), static_cast<GLfloat>(elm->getPosition()->getY() - elm->getRadius()));
   glVertex2f(static_cast<GLfloat>(elm->getPosition()->getX() + elm->getRadius()), static_cast<GLfloat>(elm->getPosition()->getY() + elm->getRadius()));
   glVertex2f(static_cast<GLfloat>(elm->getPosition()->getX() - elm->getRadius()), static_cast<GLfloat>(elm->getPosition()->getY() + elm->getRadius()));
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
   glColor3f(static_cast<GLfloat>(elm->getAge()), static_cast<GLfloat>(elm->getAge()), static_cast<GLfloat>(elm->getAge()));

   // Draw the actual line
   glVertex2f(static_cast<GLfloat>(elm->getPosition()->getX()), static_cast<GLfloat>(elm->getPosition()->getY()));
   glVertex2f(static_cast<GLfloat>(elm->getEnd()->getX()), static_cast<GLfloat>(elm->getEnd()->getY()));

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
   glColor3f(static_cast<GLfloat>(elm->getAge()), static_cast<GLfloat>(elm->getAge()), static_cast<GLfloat>(elm->getAge()));

   // Draw the actual line
   glVertex2f(static_cast<GLfloat>(elm->getPosition()->getX()), static_cast<GLfloat>(elm->getPosition()->getY()));
   glVertex2f(static_cast<GLfloat>(elm->getEnd()->getX()), static_cast<GLfloat>(elm->getEnd()->getY()));

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
   glRasterPos2f(static_cast<GLfloat>(elm->getPosition()->getX()), static_cast<GLfloat>(elm->getPosition()->getY()));

   // draw the digits
   int number = (elm->value > 0 ? elm->value : -elm->value);
   if (number / 10 != 0)
      glutBitmapCharacter(pFont, static_cast<char>(number / 10) + '0');
   glutBitmapCharacter(pFont, static_cast<char>(number % 10) + '0');
}

