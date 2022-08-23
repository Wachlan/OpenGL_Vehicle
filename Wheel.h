//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#pragma once
#include "Vehicle.hpp"
#include "Vehicle1.h"
#include "Shape.hpp"
#include "Cylinder.h"

class Wheel : public Cylinder
{
protected:
	double r;
	double w;

	double rotation1;

public:
	Wheel();
	Wheel(double x, double y, double z, double radius, double width);
	void draw();

};