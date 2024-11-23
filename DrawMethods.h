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

#include "Element.h"
#include <cassert>

#include "position.h"

void drawDisk(const Position& center, double radius, double red, double green, double blue) {
	assert(radius > 1.0);
	const double increment = M_PI / radius;  // bigger the circle, the more increments

	// begin drawing
	glBegin(GL_TRIANGLES);
	glColor3f(static_cast<GLfloat>(red /* red % */) /* red % */, static_cast<GLfloat>(green /* green % */) /* green % */, static_cast<GLfloat>(blue /* blue % */) /* blue % */);

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

		glVertex2f(static_cast<GLfloat>(center.getX()), static_cast<GLfloat>(center.getY()));
		glVertex2f(static_cast<GLfloat>(pt1.getX()), static_cast<GLfloat>(pt1.getY()));
		glVertex2f(static_cast<GLfloat>(pt2.getX()), static_cast<GLfloat>(pt2.getY()));

		pt1 = pt2;
	}

	// complete drawing
	glEnd();
}

void drawDot(const Position& point, double radius, double red, double green, double blue) {
	// Get ready, get set...
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(static_cast<GLfloat>(red), static_cast<GLfloat>(green), static_cast<GLfloat>(blue));
	double r = radius / 2.0;

	// Go...
	glVertex2f(static_cast<GLfloat>(point.getX() - r), static_cast<GLfloat>(point.getY() - r));
	glVertex2f(static_cast<GLfloat>(point.getX() + r), static_cast<GLfloat>(point.getY() - r));
	glVertex2f(static_cast<GLfloat>(point.getX() + r), static_cast<GLfloat>(point.getY() + r));
	glVertex2f(static_cast<GLfloat>(point.getX() - r), static_cast<GLfloat>(point.getY() + r));

	// Done!  OK, that was a bit too dramatic
	glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
	glEnd();
}

inline void glVertexPoint(const Position& point)
{
	glVertex2f(static_cast<GLfloat>(point.getX()), static_cast<GLfloat>(point.getY()));
}

void drawLine(const Position& begin, const Position& end, double red, double green, double blue) {
	// Get ready...
	glBegin(GL_LINES);
	glColor3f(static_cast<GLfloat>(red), static_cast<GLfloat>(green), static_cast<GLfloat>(blue));

	// Draw the actual line
	glVertexPoint(begin);
	glVertexPoint(end);

	// Complete drawing
	glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
	glEnd();
}


void drawBomb(Element* element) {
	if (!element->isDead()){
		Position pt = element->getPosition();
		double radius = element->getRadius();
		
		// Bomb actually has a gradient to cut out the harsh edges
		drawDot(pt, radius + 2.0, 0.50, 0.50, 0.00);
		drawDot(pt, radius + 1.0, 0.75, 0.75, 0.00);
		drawDot(pt, radius + 0.0, 0.87, 0.87, 0.00);
		drawDot(pt, radius - 1.0, 1.00, 1.00, 0.00);
	}
}

void drawPellet(Element* element) {
	if (!element->isDead()) {
		drawDot(element->getPosition(), 3.0, 1.0, 1.0, 0.0);
	}
}

void drawMissile(Element* element) {
	if (!element->isDead())
	{
		Position pt = element->getPosition();
		Velocity v = element->getVelocity();
		// missile is a line with a dot at the end, so it looks like fins.
		Position ptNext(pt);
		ptNext.add(v);
		drawLine(pt, ptNext, 1.0, 1.0, 0.0);
		drawDot(pt, 3.0, 1.0, 1.0, 1.0);
	}
}

void drawShrapnel(Element* element) {
	if (!element->isDead())
		drawDot(element->getPosition(), element->getRadius(), 1.0, 1.0, 0.0);
}

void drawStandard(Element* element) {
	if (!element->isDead())
	{
		Position pt = element->getPosition();
		double radius = element->getRadius();
		drawDisk(pt, radius - 0.0, 1.0, 1.0, 1.0); // white outline
		drawDisk(pt, radius - 3.0, 0.0, 0.0, 1.0); // blue center
	}
}

void drawSinker(Element* element) {
	if (!element->isDead())
	{
		Position pt = element->getPosition();
		double radius = element->getRadius();
		drawDisk(pt, radius - 0.0, 0.0, 0.0, 0.8);
		drawDisk(pt, radius - 4.0, 0.0, 0.0, 0.0);
	}
}

void drawFloater(Element* element) {
	if (!element->isDead())
	{
		Position pt = element->getPosition();
		double radius = element->getRadius();
		drawDisk(pt, radius - 0.0, 0.0, 0.0, 1.0); // blue outline
		drawDisk(pt, radius - 4.0, 1.0, 1.0, 1.0); // white center
	}
}

void drawCrazy(Element* element) {
	if (!element->isDead())
	{
		Position pt = element->getPosition();
		double radius = element->getRadius();
		drawDisk(pt, radius * 1.0, 0.0, 0.0, 1.0); // bright blue outside
		drawDisk(pt, radius * 0.8, 0.2, 0.2, 1.0);
		drawDisk(pt, radius * 0.6, 0.4, 0.4, 1.0);
		drawDisk(pt, radius * 0.4, 0.6, 0.6, 1.0);
		drawDisk(pt, radius * 0.2, 0.8, 0.8, 1.0); // almost white inside
	}
}