#include "MyVehicle.h"
#include "VehicleDrawer.h"
#include "Wheel.h"
#include "RectangularPrism.h"
#include "TrapezoidalPrism.h"
#include "TriangularPrism.h"
#include "Cylinder.h"
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

#include "Camera.hpp"
#include "Ground.hpp"
#include "KeyManager.hpp"

#include "Shape.hpp"
#include "Vehicle.hpp"

#include "RemoteDataManager.hpp"
#include "Messages.hpp"
#include "HUD.hpp"
#include "ObstacleManager.hpp"

/*
void VehicleDrawer::Drawer(VehicleModel vm)
{
	GetVehicleModelStr(vm);
	//GetShapeInitStr(si);
	//GetVehicleStateStr(vs);

	for (int i = 0; i < vm.shapes.size(); i++) {
		//ShapeInit Shape* si = shapes.pop_back;
		//si = shapes.pop_back;
		ShapeType shapeType = vm.shapes(i).type;



		double x = si.xyz[0];
		double y = si.xyz[1];
		double z = si.xyz[2];

		int r = si.rgb[0];
		int g = si.rgb[1];
		int b = si.rgb[2];


		double rot = si.rotation;

		if (shapeType = RECTANGULAR_PRISM) {
			double xlen = si.params.rect.xlen;
			double ylen = si.params.rect.ylen;
			double zlen = si.params.rect.zlen;

			RectangularPrism A(x, y, z, xlen, ylen, zlen);
			A.setColor(r, g, b);
			A.draw();

		}
	}

}*/
