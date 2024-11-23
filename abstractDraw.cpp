/***********************************************************************
 * Source File:
 *    Abstract Draw : Entities that can be drawn
 * Author:
 *    Taemour and Jessica
 * Summary:
 *    Stuff that moves across the screen to be drawn
 ************************************************************************/

#pragma once
#include <cassert>
#include "abstractDraw.h"

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


/************************************************************************
 * DRAW Disk
 * Draw a filled circule at [center] with size [radius]
 *************************************************************************/
void drawDisk(const Position& center, double radius,
              double red, double green, double blue)
{
   assert(radius > 1.0);
   const double increment = M_PI / radius;  // bigger the circle, the more increments
   
      // begin drawing
   glBegin(GL_TRIANGLES);
   glColor3f((GLfloat)red /* red % */, (GLfloat)green /* green % */, (GLfloat)blue /* blue % */);
   
      // three points: center, pt1, pt2
   Position pt1;
   pt1.setX(center.getX() + (radius * cos(0.0)));
   pt1.setY(center.getY() + (radius * sin(0.0)));
   Position pt2(pt1);
   
      // go around the circle
   for (double radians = increment;
        radians <= M_PI * 2.0 + .5;
        radians += increment)
   {
      pt2.setX(center.getX() + (radius * cos(radians)));
      pt2.setY(center.getY() + (radius * sin(radians)));
      
      glVertex2f((GLfloat)center.getX(), (GLfloat)center.getY());
      glVertex2f((GLfloat)pt1.getX(), (GLfloat)pt1.getY());
      glVertex2f((GLfloat)pt2.getX(), (GLfloat)pt2.getY());
      
      pt1 = pt2;
   }
   
      // complete drawing
   glEnd();
}

/*********************************************
 * STANDARD DRAW
 * Draw a standard bird: blue center and white outline
 *********************************************/
void standardDraw::draw()
{
   if (!getDead())
   {
      drawDisk(pt, radius - 0.0, 1.0, 1.0, 1.0); // white outline
      drawDisk(pt, radius - 3.0, 0.0, 0.0, 1.0); // blue center
   }
}

/*********************************************
 * FLOATER DRAW
 * Draw a floating bird: white center and blue outline
 *********************************************/
void floaterDraw::draw()
{
   if (!getDead())
   {
      drawDisk(pt, radius - 0.0, 0.0, 0.0, 1.0); // blue outline
      drawDisk(pt, radius - 4.0, 1.0, 1.0, 1.0); // white center
   }
}

/*********************************************
 * CRAZY DRAW
 * Draw a crazy bird: concentric circles in a course gradient
 *********************************************/
void crazyDraw::draw()
{
   if (!getDead())
   {
      drawDisk(pt, radius * 1.0, 0.0, 0.0, 1.0); // bright blue outside
      drawDisk(pt, radius * 0.8, 0.2, 0.2, 1.0);
      drawDisk(pt, radius * 0.6, 0.4, 0.4, 1.0);
      drawDisk(pt, radius * 0.4, 0.6, 0.6, 1.0);
      drawDisk(pt, radius * 0.2, 0.8, 0.8, 1.0); // almost white inside
   }
}

/*********************************************
 * SINKER DRAW
 * Draw a sinker bird: black center and dark blue outline
 *********************************************/
void sinkerDraw::draw()
{
   if (!getDead())
   {
      drawDisk(pt, radius - 0.0, 0.0, 0.0, 0.8);
      drawDisk(pt, radius - 4.0, 0.0, 0.0, 0.0);
   }
}







/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position& point)
{
   glVertex2f((GLfloat)point.getX(), (GLfloat)point.getY());
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *************************************************************************/
void drawLine(const Position& begin, const Position& end,
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
void drawDot(const Position& point, double radius,
                     double red, double green, double blue)
{
      // Get ready, get set...
   glBegin(GL_TRIANGLE_FAN);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);
   double r = radius / 2.0;
   
      // Go...
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() - r));
   glVertex2f((GLfloat)(point.getX() + r), (GLfloat)(point.getY() + r));
   glVertex2f((GLfloat)(point.getX() - r), (GLfloat)(point.getY() + r));
   
      // Done!  OK, that was a bit too dramatic
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/*********************************************
 * PELLET OUTPUT
 * Draw a pellet - just a 3-pixel dot
 *********************************************/
void pelletDraw::draw()
{
   if (!getDead())
      drawDot(pt, 3.0, 1.0, 1.0, 0.0);
}

/*********************************************
 * BOMB OUTPUT
 * Draw a bomb - many dots to make it have a soft edge
 *********************************************/
void bombDraw::draw()
{
   if (!getDead())
   {
         // Bomb actually has a gradient to cut out the harsh edges
      drawDot(pt, radius + 2.0, 0.50, 0.50, 0.00);
      drawDot(pt, radius + 1.0, 0.75, 0.75, 0.00);
      drawDot(pt, radius + 0.0, 0.87, 0.87, 0.00);
      drawDot(pt, radius - 1.0, 1.00, 1.00, 0.00);
   }
}

/*********************************************
 * SHRAPNEL OUTPUT
 * Draw a fragment - a bright yellow dot
 *********************************************/
void shrapnelDraw::draw()
{
   if (!getDead())
      drawDot(pt, radius, 1.0, 1.0, 0.0);
}

/*********************************************
 * MISSILE OUTPUT
 * Draw a missile - a line and a dot for the fins
 *********************************************/
void missileDraw::draw()
{
   if (!getDead())
   {
         // missile is a line with a dot at the end so it looks like fins.
      Position ptNext(pt);
      ptNext.add(v);
      drawLine(pt, ptNext, 1.0, 1.0, 0.0);
      drawDot(pt, 3.0, 1.0, 1.0, 1.0);
   }
}
