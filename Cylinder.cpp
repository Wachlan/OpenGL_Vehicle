//Lachlan Chow & James Davies
//Assignment 2 MTRN 2500
//Cylinder.cpp

#include "Cylinder.h"
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

#define Pi 3.14159265359

//Default constructor
Cylinder::Cylinder()
{
	setX(0);
	setY(0);
	setZ(0);

	radius = 5;
	length = 10;
}

//Receiving input data for dimensions and co-ordinates
Cylinder::Cylinder(double x, double y, double z, double r, double l)
{
	//Storing co-ordinates 
	setX(x);
	setY(y);
	setZ(z);

	//Storing dimensions
	radius = r;
	length = l;

}

void Cylinder::draw()
{
	//Set the centre of the cylinder to the given co-ordinates
	x = getX();
	y = getY();
	z = getZ();
	glPushMatrix();
	glRotated(rotation, 0.0, 1.0, 0.0);
	glColor3d(red, green, blue);
	glDisable(GL_LIGHTING); //Fix lighting issues

	//Draw the 2 end circles, followed by the curved surface joining them
	endCircle();
	length = -length;
	endCircle();
	curvedSurface();
	glPopMatrix();

}

void Cylinder::endCircle()
{
	//Draw the end circle as a fan of triangles from the centre
	glBegin(GL_TRIANGLE_FAN);
	//Drawing the cylinder when the center is defined at the bottom (from server specs)
	//Which is why 'y + radius" is used
	glVertex3d(x, y + radius, z - (length / 2));
	for (double angle = 0; angle <= 2 * Pi; angle = angle + 0.01)
	{
		//Specify vertices along the circle circumference
		glVertex3d(x + radius * sin(angle), y + radius + radius * cos(angle), z - (length / 2));
	}

	glEnd();
}

void Cylinder::curvedSurface()
{
	//Draw the surface as a series of connected triangles
	glBegin(GL_TRIANGLE_STRIP);

	for (double angle = 0; angle <= 6.283185307; angle = angle + 0.012566)
	{
		glVertex3d(x + radius * sin(angle), y + radius + radius * cos(angle), z - (length / 2));
		length = -length;
	}

	glEnd();
}

void Cylinder::setSteerWheel(double steering)
{
	steerwheel = steering;
	//std::cout << steerwheel;
}

void Cylinder::setRoll(double dist)
{
	rollwheel = dist;
	//std::cout << rollwheel;
}

