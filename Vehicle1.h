//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#pragma once
#include "Vehicle.hpp"
#include "Shape.hpp"
#include "Messages.hpp"

//Our custom vehicle class derived from vehicle
class Vehicle1 : public Vehicle
{
protected:

	//Variables for storing rectangular prism attributes
	double xrect;
	double yrect;
	double zrect;
	double xlenrect;
	double ylenrect;
	double zlenrect;
	double rrect;
	double grect;
	double brect;
	double rotrect;

	//Variables for storing triangular prism attributes
	double xtri;
	double ytri;
	double ztri;
	double alentri;
	double blentri;
	double depthtri;
	double angletri;
	double rtri;
	double gtri;
	double btri;
	double rottri;

	//Variables for storing trapezoidal prism attributes
	double xtrap;
	double ytrap;
	double ztrap;
	double alentrap;
	double blentrap;
	double heighttrap;
	double aofftrap;
	double depthtrap;
	double rtrap;
	double gtrap;
	double btrap;
	double rottrap;

	//Variables for storing cylinder attributes
	double xcyl;
	double ycyl;
	double zcyl;
	double radiuscyl;
	double depthcyl;
	double rcyl;
	double gcyl;
	double bcyl;
	double rotcyl;
	bool cylRolling;
	bool cylSteering;

	//variable for calculating distance travelled by vehicle
	double distance;

public:
	Vehicle1();
	Vehicle1(VehicleModel vm);
	void draw();

	//Update function for speed, steering and distance travelled by vehicle
	void update(double dt);

	//Functions to set and get the distance
	void setDistance(double d);
	double getDistance();
	
};