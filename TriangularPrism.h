//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#pragma once
#include "Shape.hpp"

//TriangularPrism class derived from shape
class TriangularPrism : public Shape
{
protected:
	double alen = 0;
	double blen = 0;
	double depth = 0;
	double angle = 0;

public:
	TriangularPrism();
	TriangularPrism(double x, double y, double z, double al, double bl, double d, double theta);
	void draw();
};