//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#include "Vehicle1.h"
#include "Wheel.h"
#include "RectangularPrism.h"
#include "TrapezoidalPrism.h"
#include "TriangularPrism.h"
#include "Cylinder.h"
#include "Messages.hpp"
#include <time.h>
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

//Vehicle1 default constructor for local vehicle
Vehicle1::Vehicle1()
{
	//Draw each shape of the vehicle and add each shape onto the Shapes vector
	//body
	Shape *body1 = new RectangularPrism(0, 0.5, 0, 4, 1, 2);
	//Cast the shape object into a rectangularprism type so it can be added onto the shapes vector
	RectangularPrism *rect = dynamic_cast<RectangularPrism*>(body1);
	body1->setPosition(0, 0.5, 0);
	body1->setColor(1, 1, 1);
	body1->setRotation(rotation);
	addShape(body1);

	//roof
	Shape *body2 = new TrapezoidalPrism(0, 1.5, 0, 3, 2, 0.75, 0.5, 2);
	TrapezoidalPrism *trap = dynamic_cast<TrapezoidalPrism*>(body2);
	body2->setPosition(0, 1.5, 0);
	body2->setColor(0, 1, 1);
	body2->setRotation(rotation);
	addShape(body2);

	//wheel 1
	Shape *body3 = new Wheel(1.25, 0, -1.1, 0.45, 0.25);
	Wheel *cyl1 = dynamic_cast<Wheel*>(body3);
	body3->setPosition(1.25, 0, -1);
	body3->setColor(1, 0, 0);
	body3->setRotation(rotation);
	//Set boolean isrolling to true or false depending if the vehicle is moving
	if (getSpeed() != 0)
	{
		body3->setIsRolling(TRUE);
	}
	else
	{
		body3->setIsRolling(FALSE);
	}
	addShape(body3);

	//Wheel 2
	Shape *body4 = new Wheel(1.25, 0, 1.1, 0.45, 0.25);
	Wheel *cyl2 = dynamic_cast<Wheel*>(body4);
	body4->setPosition(1.25, 0, 1);
	body4->setColor(1, 0, 0);
	if (getSpeed() != 0)
	{
		body4->setIsRolling(TRUE);
	}
	else
	{
		body4->setIsRolling(FALSE);
	}
	body4->setRotation(rotation);
	addShape(body4);

	//Wheel 3
	Shape *body5 = new Wheel(-1.25, 0, -1.1, 0.55, 0.25);
	Wheel *cyl3 = dynamic_cast<Wheel*>(body5);
	body5->setPosition(-1.25, 0, -1);
	body5->setColor(1, 0, 0);
	//Set boolean issteering to true or false depending if the vehicle is steering or not
	if (getSteering() != 0) {
		body5->setIsSteering(true);
	}
	else {
		body5->setIsSteering(false);
	}
	//Set boolean isrolling to true or false depending if the vehicle is moving
	if (getSpeed() != 0)
	{
		body5->setIsRolling(true);
	}
	else
	{
		body5->setIsRolling(false);
	}
	body5->setRotation(rotation);
	addShape(body5);

	//Wheel 4
	Shape *body6 = new Wheel(-1.25, 0, 1.1, 0.55, 0.25);
	Wheel *cyl4 = dynamic_cast<Wheel*>(body6);
	body6->setPosition(-1.25, 0, 1.0);
	body6->setColor(1, 0, 0);
	if (getSteering() != 0) {
		body6->setIsSteering(TRUE);
	}
	else {
		body6->setIsSteering(FALSE);
	}
	if (getSpeed() != 0)
	{
		body6->setIsRolling(true);
	}
	else
	{
		body6->setIsRolling(false);
	}
	body6->setRotation(rotation);
	addShape(body6);

	//spoiler
	Shape *body7 = new RectangularPrism(-1.875, 1.5, 0, 0.25, 0.25, 3);
	RectangularPrism *rect2 = dynamic_cast<RectangularPrism*>(body7);
	body7->setPosition(-1.875, 1.5, 0);
	body7->setColor(1, 1, 0);
	body7->setRotation(rotation);
	addShape(body7);

	//front bumper
	Shape *body8 = new TriangularPrism(2.25, 0.5, 0, 0.5, 0.35, 2, 90);
	TriangularPrism *bump = dynamic_cast<TriangularPrism*>(body8);
	body8->setPosition(2.25, 0.5, 0);
	body8->setColor(1, 0, 0);
	body8->setRotation(rotation);
	addShape(body8);
}

//Deconstructing the vehiclemodel vector attributes and storing them into a shapes vector such that drawing is possible
Vehicle1::Vehicle1(VehicleModel vm)
{
	//looping through the vehiclemodel shapes vector to extract information
	for (std::vector<ShapeInit>::iterator it = vm.shapes.begin(); it != vm.shapes.end(); ++it) {

		//Dealing with different shape cases
		switch (it->type) {
		case RECTANGULAR_PRISM:
		{
			//Storing attributes of the shape 
			xrect = it->xyz[0];
			yrect = it->xyz[1];
			zrect = it->xyz[2];

			rrect = it->rgb[0];
			grect = it->rgb[1];
			brect = it->rgb[2];

			rotrect = it->rotation;
			xlenrect = it->params.rect.xlen;
			ylenrect = it->params.rect.ylen;
			zlenrect = it->params.rect.zlen;

			//Creating shape object using stored variables from vehiclemodel vector
			Shape *shape = new RectangularPrism(xrect, yrect, zrect, xlenrect, ylenrect, zlenrect);
			//Casting the type of shape such that it can be stored in the shapes vector
			RectangularPrism *rect = dynamic_cast<RectangularPrism*>(shape);
			shape->setPosition(xrect, yrect, zrect);
			shape->setRotation(rotrect);
			shape->setColor(rrect, grect, brect);
			addShape(shape);

			break;
		}

		case TRIANGULAR_PRISM:
		{
			//Storing attributes of the shape 
			xtri = -(it->xyz[0]);
			ytri = it->xyz[1];
			ztri = it->xyz[2];

			rtri = it->rgb[0];
			gtri = it->rgb[1];
			btri = it->rgb[2];

			rottri = it->rotation;
			alentri = it->params.tri.alen;
			blentri = it->params.tri.blen;
			depthtri = it->params.tri.depth;
			angletri = it->params.tri.angle;

			Shape *shape = new TriangularPrism(xtri, ytri, ztri, alentri, blentri, depthtri, angletri);
			TriangularPrism *rect = dynamic_cast<TriangularPrism*>(shape);
			shape->setPosition(xtri, ytri, ztri);
			shape->setRotation(rottri);
			shape->setColor(rtri, gtri, btri);
			addShape(shape);

			break;
		}

		case TRAPEZOIDAL_PRISM:
		{
			//Storing attributes of the shape 
			xtrap = it->xyz[0];
			ytrap = it->xyz[1];
			ztrap = it->xyz[2];

			rtrap = it->rgb[0];
			gtrap = it->rgb[1];
			btrap = it->rgb[2];

			rottrap = it->rotation;
			alentrap = it->params.trap.alen;
			blentrap = it->params.trap.blen;
			heighttrap = it->params.trap.height;
			aofftrap = it->params.trap.aoff;
			depthtrap = it->params.trap.depth;

			Shape *shape = new TrapezoidalPrism(xtrap, ytrap, ztrap, alentrap, blentrap, heighttrap, aofftrap, depthtrap);
			TrapezoidalPrism *rect = dynamic_cast<TrapezoidalPrism*>(shape);
			shape->setPosition(xtrap, ytrap, ztrap);
			shape->setRotation(rottrap);
			shape->setColor(rtrap, gtrap, btrap);
			addShape(shape);

			break;
		}

		case CYLINDER:
		{
			//Storing attributes of the shape 
			xcyl = it->xyz[0];
			ycyl = it->xyz[1];
			zcyl = it->xyz[2];

			rcyl = it->rgb[0];
			gcyl = it->rgb[1];
			bcyl = it->rgb[2];

			rotcyl = it->rotation;
			radiuscyl = it->params.cyl.radius;
			depthcyl = it->params.cyl.depth;

			//Storing a boolean that represents the wheel as turning/steering or not
			cylRolling = it->params.cyl.isRolling;
			cylSteering = it->params.cyl.isSteering;

			Shape *shape = new Cylinder(xcyl, ycyl, zcyl, radiuscyl, depthcyl);
			Cylinder *rect = dynamic_cast<Cylinder*>(shape);
			shape->setPosition(xcyl, ycyl, zcyl);
			shape->setRotation(rotcyl);
			shape->setIsRolling(cylRolling);
			shape->setIsSteering(cylSteering);
			shape->setColor(rcyl, gcyl, bcyl);
			addShape(shape);

			break;
		}
		}
	}
}

void Vehicle1::draw()
{
	//Iterating through the shapes vector and drawing each shape
	for (std::vector<Shape*>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
		Wheel *cyl = dynamic_cast<Wheel*>(*it);
		Cylinder *cylind = dynamic_cast<Cylinder*>(*it);
		glPushMatrix();
		positionInGL();

		//Checking if remote vehicles steering is working, and rotate their wheels according to their steering
		if (cylind != NULL && cylind->getIsSteering() == true)
		{
			cylind->setRotation(-getSteering());
		}
		//Checking if remote vehicles are moving and if so, roll their wheels
		if (cylind != NULL)
		{
			cylind->setRoll(distance);
		}

		//Checking our vehicle steering is working, and rotate their wheels according to our steering
		if (cyl != NULL && cyl->getIsSteering() == TRUE)
		{
			cyl->setSteerWheel(-getSteering());
		}
		//Checking if our vehicle are moving and if so, roll our wheels
		if (cyl != NULL)
		{
			cyl->setRoll(distance);
		}
		
		(*it)->draw();
		glPopMatrix();
	}
}

//Using the function given in Vehicle.cpp to use distance
void Vehicle1::update(double dt)
{
	speed = clamp(MAX_BACKWARD_SPEED_MPS, speed, MAX_FORWARD_SPEED_MPS);
	steering = clamp(MAX_LEFT_STEERING_DEGS, steering, MAX_RIGHT_STEERING_DEGS);

	// update position by integrating the speed
	x += speed * dt * cos(rotation * 3.1415926535 / 180.0);
	z += speed * dt * sin(rotation * 3.1415926535 / 180.0);

	// update heading
	rotation += dt * steering * speed;

	while (rotation > 360) rotation -= 360;
	while (rotation < 0) rotation += 360;


	if (fabs(speed) < .1)
		speed = 0;
	if (fabs(steering) < .1)
		steering = 0;

	//Setting distance traveled by vehicle
	distance = distance + speed * dt;
}

void Vehicle1::setDistance(double d)
{
	distance = d;
}

double Vehicle1::getDistance()
{
	return distance;
}
