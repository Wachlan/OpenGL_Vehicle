//Lachlan Chow & James Davies
//Assignment 2 MTRN 2500
//TrapezoidalPrism.cpp

#include "TrapezoidalPrism.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

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

//Default constructor
TrapezoidalPrism::TrapezoidalPrism()
{
	setX(0);
	setY(0);
	setZ(0);
	
	a = 1;
	b = 1;
	h = 1.5;
	o = 0.5;
	d = 2;
}

//Receiving input data for dimensions and co-ordinates
TrapezoidalPrism::TrapezoidalPrism(double x, double y, double z, double lenA, double lenB, double lenH, double lenO, double lenD)
{
	//Storing co-ordinates 
	setX(x);
	setY(y);
	setZ(z);
	
	//Storing dimensions
	a = lenA;
	b = lenB;
	h = lenH;
	o = lenO;
	d = lenD;
}

void TrapezoidalPrism::draw()
{
	//Retrieving given co-ordinates
	x = getX();
	y = getY();
	z = getZ();

	glPushMatrix();
	glColor3d(red, green, blue);
	glRotated(rotation, 0, 1, 0);

	//Drawing all the faces
	//Front face left triangle
	glBegin(GL_TRIANGLES);
	glVertex3d(x - a / 2, y, z - d / 2);
	glVertex3d(x - a / 2 + o, y, z - d / 2);
	glVertex3d(x - a / 2 + o, y + h, z - d / 2);
	glEnd();

	//Front face right triangle
	glBegin(GL_TRIANGLES);
	glVertex3d(x + a / 2, y, z - d / 2);
	glVertex3d(x - a / 2 + b + o, y, z - d / 2);
	glVertex3d(x - a / 2 + b + o, y + h, z - d / 2);
	glEnd();

	//Back face left triangle
	glBegin(GL_TRIANGLES);
	glVertex3d(x - a / 2, y, z + d / 2);
	glVertex3d(x - a / 2 + o, y, z + d / 2);
	glVertex3d(x - a / 2 + o, y + h, z + d / 2);
	glEnd();

	//Back face right triangle
	glBegin(GL_TRIANGLES);
	glVertex3d(x + a / 2, y, z + d / 2);
	glVertex3d(x - a / 2 + b + o, y, z + d / 2);
	glVertex3d(x - a / 2 + b + o, y + h, z + d / 2);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3d(x - a / 2, y, z - d / 2);
	glVertex3d(x + a / 2, y, z - d / 2);
	glVertex3d(x + a / 2, y, z + d / 2);
	glVertex3d(x - a / 2, y, z + d / 2);

	glVertex3d(x - a / 2, y, z + d / 2);
	glVertex3d(x - a / 2, y, z - d / 2);
	glVertex3d(x - a / 2 + o, y + h, z + d / 2);
	glVertex3d(x - a / 2 + o, y + h, z - d / 2);

	glVertex3d(x - a / 2 + o, y + h, z - d / 2);
	glVertex3d(x - a / 2 + o, y + h, z + d / 2);
	glVertex3d(x - a / 2 + b + o, y + h, z - d / 2);
	glVertex3d(x - a / 2 + b + o, y + h, z + d / 2);

	glVertex3d(x - a / 2 + b + o, y + h, z + d / 2);
	glVertex3d(x - a / 2 + b + o, y + h, z - d / 2);
	glVertex3d(x + a / 2, y, z - d / 2);
	glVertex3d(x + a / 2, y, z + d / 2);
	glEnd();

	//Front face
	glBegin(GL_QUADS);
	glVertex3d(x - a / 2 + o, y, z - d / 2);
	glVertex3d(x - a / 2 + b + o, y, z - d / 2);
	glVertex3d(x - a / 2 + b + o, y + h, z - d / 2);
	glVertex3d(x - a / 2 + o, y + h, z - d / 2);
	glEnd();

	//Back face
	glBegin(GL_QUADS);
	glVertex3d(x - a / 2 + o, y, z + d / 2);
	glVertex3d(x - a / 2 + b + o, y, z + d / 2);
	glVertex3d(x - a / 2 + b + o, y + h, z + d / 2);
	glVertex3d(x - a / 2 + o, y + h, z + d / 2);
	glEnd();
	glPopMatrix();
}