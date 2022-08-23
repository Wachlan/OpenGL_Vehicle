//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#pragma once
#include "Shape.hpp"

class RectangularPrism : public Shape
{
protected:
	double x_length = 0;
	double y_length = 0;
	double z_length = 0;

public:
	RectangularPrism();
	RectangularPrism(double x, double y, double z, double lx, double ly, double lz);
	void draw();

};
