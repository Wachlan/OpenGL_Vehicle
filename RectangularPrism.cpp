//Lachlan Chow & James Davies
//Assignment 2 MTRN 2500
//RectangularPrism.cpp

#include "RectangularPrism.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

#ifdef _APPLE_
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


//RectangularPrism default constructor
RectangularPrism::RectangularPrism()
{
	x_length = 1;
	y_length = 1;
	z_length = 1;
}


//Receiving dimensional input about shape and setting workable variables
RectangularPrism::RectangularPrism(double x, double y, double z, double lx, double ly, double lz)
{
	setX(x);
	setY(y);
	setZ(z);

	x_length = lx;
	y_length = ly;
	z_length = lz;
}

void RectangularPrism::draw()
{
	x = getX();
	y = getY();
	z = getZ();

	glPushMatrix();
	glRotated(rotation, 0.0, 1.0, 0.0);
	glColor3d(red, green, blue);

	//Variables which store half the lengths of x, y and z to centre the rectangular prism
	double hlx = x_length / 2;
	double hly = y_length / 2;
	double hlz = z_length / 2;

	//Drawing each face separately
	glBegin(GL_QUADS);
	//bottom
	glVertex3d(x + hlx, y, z + hlz);
	glVertex3d(x + hlx, y, z - hlz);
	glVertex3d(x - hlx, y, z - hlz);
	glVertex3d(x - hlx, y, z + hlz);

	//left side
	glVertex3d(x - hlx, y, z + hlz);
	glVertex3d(x + hlx, y, z + hlz);
	glVertex3d(x + hlx, y + y_length, z + hlz);
	glVertex3d(x - hlx, y + y_length, z + hlz);

	//back
	glVertex3d(x - hlx, y + y_length, z + hlz);
	glVertex3d(x - hlx, y, z + hlz);
	glVertex3d(x - hlx, y, z - hlz);
	glVertex3d(x - hlx, y + y_length, z - hlz);

	//right
	glVertex3d(x - hlx, y + y_length, z - hlz);
	glVertex3d(x - hlx, y, z - hlz);
	glVertex3d(x + hlx, y, z - hlz);
	glVertex3d(x + hlx, y + y_length, z - hlz);

	//front
	glVertex3d(x + hlx, y + y_length, z - hlz);
	glVertex3d(x + hlx, y, z - hlz);
	glVertex3d(x + hlx, y, z + hlz);
	glVertex3d(x + hlx, y + y_length, z + hlz);

	//top
	glVertex3d(x + hlx, y + y_length, z + hlz);
	glVertex3d(x + hlx, y + y_length, z - hlz);
	glVertex3d(x - hlx, y + y_length, z - hlz);
	glVertex3d(x - hlx, y + y_length, z + hlz);

	glEnd();

	glPopMatrix();
}