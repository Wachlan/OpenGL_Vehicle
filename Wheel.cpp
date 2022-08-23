//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#include "RectangularPrism.h"
#include "TrapezoidalPrism.h"
#include "TriangularPrism.h"
#include "Cylinder.h"
#include "Wheel.h"
#include "Vehicle1.h"
#include "Vehicle.hpp"
#include "Shape.hpp"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>
#include <math.h>

#ifdef APPLE
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <unistd.h>
#include <sys/time.h>
#elif defined(WIN32)
#include <Windows.h>
#include <tchar.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <unistd.h>
#include <sys/time.h>
#endif

Wheel::Wheel()
{
	r = 1;
	w = 1;
}

Wheel::Wheel(double x, double y, double z, double radius, double width)
{
	r = radius;
	w = width;
}

void Wheel::draw()
{
	double angle = (rollwheel / r);

	x = getX();
	y = getY();
	z = getZ();
	
	glPushMatrix();
	glTranslated(x, y, z);
	
	if (angle != 0)
	{
		//translate and then rotate the wheel if the vehicle has moved
		glTranslated(-(r*sin(angle)), r - r * cos(angle), 0.0);
		glRotated(-angle * 180 / 3.1415926535, 0.0, 0.0, 1);
	}
	glEnd();


	if (getIsSteering() == TRUE)
	{
		glRotated(steerwheel, 0, 1, 0);
	}
	else
	{
		glRotated(rotation, 0.0, 1.0, 0.0);
	}
	glColor3d(1,0,0);
	//fix lighting issues
	glDisable(GL_LIGHTING);
	
	//Following the curved surface drawing function from cylinder to draw the tyre
	glBegin(GL_TRIANGLE_STRIP);

	for (double angle = 0; angle <= 6.283185307; angle = angle + 0.01)
	{
		glVertex3d(r * sin(angle), r+r * cos(angle), (w / 2));
		w = -w;
	}
	
	glEnd();
	glColor3d(0, 1, 0);
	
	//Drawing the spoke for the wheel
	glBegin(GL_QUADS);
	//bottom
	glVertex3d(0.1*r, 0,  0.1*r);
	glVertex3d(0.1*r, 0, - 0.1*r);
	glVertex3d(- 0.1*r,0, - 0.1*r);
	glVertex3d(- 0.1*r, 0, 0.1*r);

	//left side
	glVertex3d(- 0.1*r, 0, 0.1*r);
	glVertex3d(0.1*r, 0,  0.1*r);
	glVertex3d(0.1*r, 2 * r, 0.1*r);
	glVertex3d(- 0.1*r, 2 * r, 0.1*r);

	//back
	glVertex3d(- 0.1*r, 2 * r,  0.1*r);
	glVertex3d(- 0.1*r, 0,  0.1*r);
	glVertex3d(- 0.1*r, 0, - 0.1*r);
	glVertex3d(- 0.1*r, 2 * r,- 0.1*r);

	//right
	glVertex3d(- 0.1*r, 2 * r,- 0.1*r);
	glVertex3d(- 0.1*r,0, - 0.1*r);
	glVertex3d(0.1*r, 0, - 0.1*r);
	glVertex3d(0.1*r, 2 * r, - 0.1*r);

	//front
	glVertex3d(0.1*r, 2 * r, - 0.1*r);
	glVertex3d(0.1*r, 0, - 0.1*r);
	glVertex3d(0.1*r, 0,  0.1*r);
	glVertex3d(0.1*r, 0 + 2 * r, 0.1*r);

	//top
	glVertex3d(0.1*r, 2 * r, 0.1*r);
	glVertex3d(0.1*r,  2 * r,- 0.1*r);
	glVertex3d(- 0.1*r, 2 * r,- 0.1*r);
	glVertex3d(- 0.1*r,  2 * r, 0.1*r);

	glEnd();

	

	glPopMatrix();

}

