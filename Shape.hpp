//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#ifndef MTRN3500_SHAPE_H
#define MTRN3500_SHAPE_H

// Abstract class
class Shape {

public:
	Shape();
	Shape(double x_, double y_, double z_);
	Shape(double x_, double y_, double z_, double rotation_);
	virtual ~Shape();

	virtual void draw() = 0;

	double getX();
	double getY();
	double getZ();
	double getRotation();
	bool getIsSteering();
	bool getIsRolling();

	void setX(double x_);
	void setY(double y_);
	void setZ(double z_);
	void setRotation(double rotation_);
	void setIsSteering(bool steering_);
	void setIsRolling(bool rolling_);
	
	//double getSteerWheel();

	void setPosition(double x_, double y_, double z_);

	void positionInGL();
	void setColorInGL();

	double getRed();
	double getGreen();
	double getBlue();
	void setColor(float red_, float green_, float blue_);

protected:
	double x, y, z;               // position
	double rotation;              // heading of the object in the horizontal plane (degrees)
	float red, green, blue;       // colour of object
	bool steering;                // is wheel steering?
	bool rolling;                 // is wheel rolling?
	
	
};

#endif // for MTRN3500_SHAPE_H