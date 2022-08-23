//Lachlan Chow & James Davies
//Assignment 2 MTRN 2500
//TriangularPrism.cpp

#include "TriangularPrism.h"
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

//Default constructor for triangular prism
TriangularPrism::TriangularPrism()
{
	alen = 1;
	blen = 1;
	depth = 1;
	angle = 60;
}

//Receiving dimensional input about shape and setting workable variables
TriangularPrism::TriangularPrism(double x, double y, double z, double al, double bl, double d, double theta)
{
	//Set all the co-ordinates
	setX(x);
	setY(y);
	setZ(z);

	//Set dimensions
	alen = al;
	blen = bl;
	depth = d;

	//Converting angle from degrees to radians
	angle = theta * (3.14159265358979 / 180);
}

void TriangularPrism::draw()
{
	//Receiving stored dimensions
	x = getX();
	y = getY();
	z = getZ();

	double sinTheta = sin(angle);
	double cosTheta = cos(angle);

	//Grouping shapes, setting rotation and colour
	glPushMatrix();
	glRotated(rotation, 0.0, 1.0, 0.0);
	glColor3d(red, green, blue);

	//Drawing each face separately
	//Front Triangle
	glBegin(GL_TRIANGLES);
	glVertex3d(x - alen / 2, y, z - depth / 2);
	glVertex3d(x + alen / 2, y, z - depth / 2);
	glVertex3d(x - alen / 2 + blen * cosTheta, y + blen * sinTheta, z - depth / 2);
	glVertex3d(x - alen / 2, y, z - depth / 2);
	glEnd();

	//Back Triangle
	glBegin(GL_TRIANGLES);
	glVertex3d(x - alen / 2, y, z + depth / 2);
	glVertex3d(x + alen / 2, y, z + depth / 2);
	glVertex3d(x - alen / 2 + blen * cosTheta, y + blen * sinTheta, z + depth / 2);
	glVertex3d(x - alen / 2, y, z + depth / 2);
	glEnd();

	//Bottom Face
	glBegin(GL_QUADS);
	glVertex3d(x - alen / 2, y, z - depth / 2);
	glVertex3d(x - alen / 2, y, z + depth / 2);
	glVertex3d(x + alen / 2, y, z + depth / 2);
	glVertex3d(x + alen / 2, y, z - depth / 2);


	//Left Face
	glVertex3d(x - alen / 2, y, z - depth / 2);
	glVertex3d(x - alen / 2 + blen * cosTheta, y + blen * sinTheta, z - depth / 2);
	glVertex3d(x - alen / 2 + blen * cosTheta, y + blen * sinTheta, z + depth / 2);
	glVertex3d(x - alen / 2, y, z + depth / 2);
	glEnd();

	//Right Face
	glBegin(GL_QUADS);
	glVertex3d(x + alen / 2, y, z - depth / 2);
	glVertex3d(x + alen / 2, y, z + depth / 2);
	glVertex3d(x - alen / 2 + blen * cosTheta, y + blen * sinTheta, z + depth / 2);
	glVertex3d(x - alen / 2 + blen * cosTheta, y + blen * sinTheta, z - depth / 2);
	glVertex3d(x + alen / 2, y, z - depth / 2);
	glEnd();

	glPopMatrix();
}