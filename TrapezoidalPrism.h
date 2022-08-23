//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#pragma once
#include "Shape.hpp"

class TrapezoidalPrism : public Shape
{
protected:
	double a = 0;
	double b = 0;
	double h = 0;
	double o = 0;
	double d = 0;

public:
	TrapezoidalPrism();
	TrapezoidalPrism(double x, double y, double z, double lenA, double lenB, double lenH, double lenO, double lenD);
	void draw();
};