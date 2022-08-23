#pragma once
#include "Vehicle.hpp"
#include "Shape.hpp"

class Update : public Vehicle
{

public:
	virtual void update(double dt);
	virtual void update(double speed_, double steering_, double dt);

};
