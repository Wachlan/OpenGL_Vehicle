//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#pragma once
#include "Shape.hpp"

class Cylinder : public Shape
{
protected:
	double radius;
	double length;

public:
	Cylinder();
	Cylinder(double x, double y, double z, double r, double l);

	void draw();
	void endCircle();
	void curvedSurface();

	double steerwheel;
	void setSteerWheel(double steering);

	double rollwheel;
	void setRoll(double dist);

};