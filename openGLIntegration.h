#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_18
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#define GLUT_TEXT GLUT_BITMAP_HELVETICA_12
#endif // _WIN32

#include "Position.h"
#include <cassert>
using namespace std;



/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  origin   The center point we will rotate around
 *           x,y      Offset from center that we will be rotating
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
inline Position* rotate1(const Position* origin,
                         double x, double y, double rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(rotation);
   double sinA = sin(rotation);

   // start with our original point
   Position* ptReturn = new Position(*origin);

   // find the new values
   ptReturn->addX(x * cosA - y * sinA);
   ptReturn->addY(y * cosA + x * sinA /*center of rotation*/);

   return ptReturn;
}

/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position* point)
{
   glVertex2f((GLfloat)point->getX(), (GLfloat)point->getY());
}

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen from the beginning to the end.
 *************************************************************************/
inline void drawRectangle1(const Position* pt,
                           double angle = 0.0,
                           double width = 10.0,
                           double height = 100.0,
                           double red = 1.0,
                           double green = 1.0,
                           double blue = 1.0)
{
   // Get ready...
   glBegin(GL_QUADS);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(rotate1(pt, width / 2.0, height / 2.0, angle));
   glVertexPoint(rotate1(pt, width / 2.0, -height / 2.0, angle));
   glVertexPoint(rotate1(pt, -width / 2.0, -height / 2.0, angle));
   glVertexPoint(rotate1(pt, -width / 2.0, height / 2.0, angle));
   glVertexPoint(rotate1(pt, width / 2.0, height / 2.0, angle));

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
inline void drawLine1(const Position* begin, const Position* end,
                      double red, double green, double blue)
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(begin);
   glVertexPoint(end);

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW DOT
 * Draw a single point (square actually on the screen, r pixels by r pixels
 *************************************************************************/
inline void drawDot1(const Position* point, double radius,
                     double red, double green, double blue)
{
   // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(static_cast<GLfloat>(red), static_cast<GLfloat>(green), static_cast<GLfloat>(blue));
   double r = radius / 2.0;

   // Go...
   glVertex2f(static_cast<GLfloat>(point->getX() - r), static_cast<GLfloat>(point->getY() - r));
   glVertex2f(static_cast<GLfloat>(point->getX() + r), static_cast<GLfloat>(point->getY() - r));
   glVertex2f(static_cast<GLfloat>(point->getX() + r), static_cast<GLfloat>(point->getY() + r));
   glVertex2f(static_cast<GLfloat>(point->getX() - r), static_cast<GLfloat>(point->getY() + r));

   // Done!  OK, that was a bit too dramatic
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
inline void drawDisk1(const Position* center, double radius,
                      double red, double green, double blue)
{
   assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments

   // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f(static_cast<GLfloat>(red /* red % */) /* red % */,
      static_cast<GLfloat>(green /* green % */) /* green % */,
      static_cast<GLfloat>(blue /* blue % */) /* blue % */);

   // three points: center, pt1, pt2
   Position* pt1 = new Position();
   pt1->setX(center->getX() + (radius * cos(0.0)));
   pt1->setY(center->getY() + (radius * sin(0.0)));
   Position* pt2 = new Position(*pt1);

   // go around the circle
   for (double radians = increment;
      radians <= M_PI * 2.0 + .5;
      radians += increment)
   {
      pt2->setX(center->getX() + (radius * cos(radians)));
      pt2->setY(center->getY() + (radius * sin(radians)));

      glVertex2f(static_cast<GLfloat>(center->getX()), static_cast<GLfloat>(center->getY()));
      glVertex2f(static_cast<GLfloat>(pt1->getX()), static_cast<GLfloat>(pt1->getY()));
      glVertex2f(static_cast<GLfloat>(pt2->getX()), static_cast<GLfloat>(pt2->getY()));

      pt1 = pt2;
   }

   // complete drawing
   glEnd();
}


/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
inline void drawText1(const Position& topLeft, const char* text)
{
   void* pFont = GLUT_TEXT;
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);

   // prepare to output the text from the top-left corner
   glRasterPos2f(static_cast<GLfloat>(topLeft.getX()), static_cast<GLfloat>(topLeft.getY()));

   // loop through the text
   for (const char* p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}

inline void drawText1(const Position& topLeft, const string& text)
{
   drawText1(topLeft, text.c_str());
}

/************************************************************************
 * DRAW Background
 * Fill in the background
 *  INPUT color   Background color
 *************************************************************************/
inline void drawBackground1(double redBack, double greenBack, double blueBack, const Position* dimensions)
{
   glBegin(GL_TRIANGLE_FAN);

   // two rectangles is the fastest way to fill the screen.
   glColor3f(static_cast<GLfloat>(redBack /* red % */) /* red % */,
      static_cast<GLfloat>(greenBack /* green % */) /* green % */,
      static_cast<GLfloat>(blueBack /* blue % */) /* blue % */);
   glVertex2f((GLfloat)0.0, (GLfloat)0.0);
   glVertex2f(static_cast<GLfloat>(dimensions->getX()), (GLfloat)0.0);
   glVertex2f(static_cast<GLfloat>(dimensions->getX()), static_cast<GLfloat>(dimensions->getY()));
   glVertex2f((GLfloat)0.0, static_cast<GLfloat>(dimensions->getY()));

   glEnd();
}

/************************************************************************
 * DRAW Timer
 * Draw a large timer on the screen
 *  INPUT percent     Amount of time left
 *        Foreground  Foreground color
 *        Background  Background color
 *************************************************************************/
inline void drawTimer1(double percent,
                       double redFore, double greenFore, double blueFore,
                       double redBack, double greenBack, double blueBack, const Position* dimensions)
{
   GLfloat length = static_cast<GLfloat>(dimensions->getX());
   GLfloat half = length / static_cast<GLfloat>(2.0);

   // do the background stuff
   drawBackground1(redBack, greenBack, blueBack, dimensions);

   // foreground stuff
   double radians = percent * M_PI * 2.0;
   auto x_extent = half + length * static_cast<GLfloat>(sin(radians));
   GLfloat y_extent = half + length * static_cast<GLfloat>(cos(radians));

   // get read to draw the triangles
   glBegin(GL_TRIANGLE_FAN);
   glColor3f(static_cast<GLfloat>(redFore /* red % */) /* red % */, static_cast<GLfloat>(greenFore /* green % */) /* green % */, static_cast<GLfloat>(blueFore /* blue % */) /* blue % */);
   glVertex2f(half, half);

   // fill in the triangles, one eight at a time
   switch (static_cast<int>(percent * 8.0))
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

