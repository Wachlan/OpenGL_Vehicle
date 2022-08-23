//Lachlan Chow & James Davies
//z164192 and z5162711
//Group 23
//Assignment 2 MTRN 2500

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <map>

#ifdef _APPLE_
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


//Include derived classes here
#include "RectangularPrism.h"
#include "TriangularPrism.h"
#include "Cylinder.h"
#include "TrapezoidalPrism.h"
#include "Vehicle1.h"
#include "Wheel.h"
#include "VehicleDrawer.h"

#include "XBoxController.h"
#include "XInputWrapper.h"


void display();
void reshape(int width, int height);
void idle();

void keydown(unsigned char key, int x, int y);
void keyup(unsigned char key, int x, int y);
void special_keydown(int keycode, int x, int y);
void special_keyup(int keycode, int x, int y);

void mouse(int button, int state, int x, int y);
void dragged(int x, int y);
void motion(int x, int y);

using namespace std;
using namespace scos;

// Used to store the previous mouse location so we
//   can calculate relative mouse movement.
int prev_mouse_x = -1;
int prev_mouse_y = -1;

// vehicle control related variables
Vehicle * vehicle = NULL;
double speed = 0;
double steering = 0;

// default goal location
std::deque<GoalState> goals;

std::map<int, Vehicle *> otherVehicles;

int frameCounter = 0;

//int _tmain(int argc, _TCHAR* argv[]) {
int main(int argc, char ** argv) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	glutInit(&argc, (char**)(argv));
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("MTRN3500 - GL");

	Camera::get()->setWindowDimensions(WINDOW_WIDTH, WINDOW_HEIGHT);

	glEnable(GL_DEPTH_TEST);

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);

	glutKeyboardFunc(keydown);
	glutKeyboardUpFunc(keyup);
	glutSpecialFunc(special_keydown);
	glutSpecialUpFunc(special_keyup);

	glutMouseFunc(mouse);
	glutMotionFunc(dragged);
	glutPassiveMotionFunc(motion);

	// -------------------------------------------------------------------------
	// Please uncomment the following line of code and replace 'MyVehicle'
	//   with the name of the class you want to show as the current 
	//   custom vehicle.
	// -------------------------------------------------------------------------

	vehicle = new Vehicle1();


	// add test obstacles
	ObstacleManager::get()->addObstacle(Obstacle(10, 10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(10, -10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10, 10, 1));
	ObstacleManager::get()->addObstacle(Obstacle(-10, -10, 1));

	// add test goal
	GoalState g;
	g.x = 25;
	g.z = 0;
	goals.push_back(g);


	glutMainLoop();

	if (vehicle != NULL) {
		delete vehicle;
	}

	return 0;
}

void drawGoals()
{
	for (int i = 0; i < goals.size(); ++i) {
		GoalState goal = goals[i];

		glPushMatrix();
		glTranslatef(goal.x, 0, goal.z);
		glRotated(90, -1, 0, 0);
		static GLUquadric * quad = gluNewQuadric();

		// make first goal purple
		if (i == 0)
			glColor3f(1, .3, 1);
		else
			glColor3f(1, 1, 1);

		gluCylinder(quad, .5, .5, 10, 5, 1);
		glPopMatrix();
	}
}

void display() {
	frameCounter++;
	// -------------------------------------------------------------------------
	//  This method is the main draw routine. 
	// -------------------------------------------------------------------------

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (Camera::get()->isPursuitMode() && vehicle != NULL) {
		double x = vehicle->getX(), y = vehicle->getY(), z = vehicle->getZ();
		double dx = cos(vehicle->getRotation() * 3.141592765 / 180.0);
		double dy = sin(vehicle->getRotation() * 3.141592765 / 180.0);
		Camera::get()->setDestPos(x + (-20 * dx), y + 15, z + (-20 * dy));
		Camera::get()->setDestDir(dx, -0.25, dy);
	}
	Camera::get()->updateLocation();
	Camera::get()->setLookAt();

	Ground::draw();

	// draw other vehicles
	for (std::map<int, Vehicle *>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter)
		iter->second->draw();

	// draw my vehicle
	if (vehicle != NULL) {
		vehicle->draw();

	}

	// draw obstacles
	ObstacleManager::get()->drawAll();

	// draw goals
	drawGoals();

	// draw HUD
	HUD::Draw();


	//Draw stuff here

	glutSwapBuffers();
};

void reshape(int width, int height) {

	Camera::get()->setWindowDimensions(width, height);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
};

void remoteDriver(Vehicle * vehicle, double x, double z, double r, double speed_, double steering_)
{
	// filter 
	const double kSmoothingFactor = 0.5;
	vehicle->setX(vehicle->getX() * kSmoothingFactor + x * (1 - kSmoothingFactor));
	vehicle->setZ(vehicle->getZ() * kSmoothingFactor + z * (1 - kSmoothingFactor));

	vehicle->setRotation(r);
	vehicle->steering = steering_;
	vehicle->speed = speed_;
}

double getTime()
{
#if defined(WIN32)
	LARGE_INTEGER freqli;
	LARGE_INTEGER li;
	if (QueryPerformanceCounter(&li) && QueryPerformanceFrequency(&freqli)) {
		return double(li.QuadPart) / double(freqli.QuadPart);
	}
	else {
		static ULONGLONG start = GetTickCount64();
		return (GetTickCount64() - start) / 1000.0;
	}
#else
	struct timeval t;
	gettimeofday(&t, NULL);
	return t.tv_sec + (t.tv_usec / 1000000.0);
#endif
}

void idle() {



	if (KeyManager::get()->isAsciiKeyPressed('a')) {
		Camera::get()->strafeLeft();
	}

	if (KeyManager::get()->isAsciiKeyPressed('c')) {
		Camera::get()->strafeDown();
	}

	if (KeyManager::get()->isAsciiKeyPressed('d')) {
		Camera::get()->strafeRight();
	}

	if (KeyManager::get()->isAsciiKeyPressed('s')) {
		Camera::get()->moveBackward();
	}

	if (KeyManager::get()->isAsciiKeyPressed('w')) {
		Camera::get()->moveForward();
	}

	if (KeyManager::get()->isAsciiKeyPressed(' ')) {
		Camera::get()->strafeUp();
	}

	speed = 0;
	steering = 0;

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_LEFT)) {
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_RIGHT)) {
		steering = Vehicle::MAX_RIGHT_STEERING_DEGS * -1;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_UP)) {
		speed = Vehicle::MAX_FORWARD_SPEED_MPS;
	}

	if (KeyManager::get()->isSpecialKeyPressed(GLUT_KEY_DOWN)) {
		speed = Vehicle::MAX_BACKWARD_SPEED_MPS;
	}

	//Create an instantiation of the wrapper
	XInputWrapper xinput;
	//XINPUT_STATE state;
	XINPUT_VIBRATION Vibration;
	GamePad::Coordinate LT(0, 0);
	GamePad::Coordinate RT(0, 0);

	//Create a new xbox controller object
	GamePad::XBoxController controller1(&xinput, 0);
	controller1.IsConnected();
	


	LT = controller1.LeftThumbLocation();
	RT = controller1.RightThumbLocation();

	controller1.SetDeadzone(10000);

	if (controller1.RightTriggerLocation() != 0)
	{
		double rtrig = controller1.RightTriggerLocation();
		speed = (Vehicle::MAX_FORWARD_SPEED_MPS)*(rtrig/ 255);
		//std::cout << x << std::endl;
	}

	if (controller1.LeftTriggerLocation() != 0)
	{
		double ltrig = controller1.LeftTriggerLocation();
		speed = (Vehicle::MAX_BACKWARD_SPEED_MPS)*(ltrig / 255);
		//std::cout << x << std::endl;
	}

	if (LT.GetX() > 5000)
	{
		double lt = LT.GetX();
			steering = (Vehicle::MAX_RIGHT_STEERING_DEGS * -1) * (lt/32767);
		
	}

	if (LT.GetX() < -5000)
	{
		double lt = LT.GetX();
		steering = Vehicle::MAX_LEFT_STEERING_DEGS * (lt/32767);

	}

	
	

	// attempt to do data communications every 4 frames if we've created a local vehicle
	if (frameCounter % 4 == 0 && vehicle != NULL) {

		// if not connected, attempt to connect every 2 seconds
		if (!RemoteDataManager::IsConnected()) {
			if (frameCounter % 120 == 0) {

				// erase other vehicles
				for (std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) {
					delete iter->second;
				}
				otherVehicles.clear();

				// uncomment this line to connect to the robotics server.
				RemoteDataManager::Connect("www.robotics.unsw.edu.au", "18081");

				// on connect, let's tell the server what we look like
				if (RemoteDataManager::IsConnected()) {
					ObstacleManager::get()->removeAll();

					VehicleModel vm;
					vm.remoteID = 0;

					//Feeding our vehicle co-ordinates and attributes onto the vehicle models vector
					glPushMatrix();
					//Body
					ShapeInit A;
					A.type = RECTANGULAR_PRISM;
					A.params.rect.xlen = 4.0;
					A.params.rect.ylen = 1.0;
					A.params.rect.zlen = 2.0;
					A.xyz[0] = 0.0;
					A.xyz[1] = 0.5;
					A.xyz[2] = 0.0;
					A.rgb[0] = 1.0;
					A.rgb[1] = 1.0;
					A.rgb[2] = 1.0;
					A.rotation = 0.0;

					vm.shapes.push_back(A);

					//Roof
					ShapeInit B;
					B.type = TRAPEZOIDAL_PRISM;
					B.params.trap.alen = 3.0;
					B.params.trap.blen = 2.0;
					B.params.trap.height = 0.75;
					B.params.trap.aoff = 0.5;
					B.params.trap.depth = 2;
					B.xyz[0] = 0.0;
					B.xyz[1] = 1.5;
					B.xyz[2] = 0.0;
					B.rgb[0] = 0.0;
					B.rgb[1] = 1.0;
					B.rgb[2] = 1.0;
					B.rotation = 0.0;

					vm.shapes.push_back(B);

					glPopMatrix();

					glPushMatrix();

					//Wheels
					ShapeInit C;
					C.type = CYLINDER;
					C.params.cyl.radius = 0.45;
					C.params.cyl.depth = 0.25;
					C.xyz[0] = 1.25;
					C.xyz[1] = 0.0;
					C.xyz[2] = -1.0;
					C.rgb[0] = 1.0;
					C.rgb[1] = 0.0;
					C.rgb[2] = 0.0;
					C.rotation = 0.0;
					C.params.cyl.isRolling;
					C.params.cyl.isSteering;

					vm.shapes.push_back(C);

					glPopMatrix();

					glPushMatrix();

					ShapeInit D;
					D.type = CYLINDER;
					D.params.cyl.radius = 0.45;
					D.params.cyl.depth = 0.25;
					D.xyz[0] = 1.25;
					D.xyz[1] = 0.0;
					D.xyz[2] = 1.0;
					D.rgb[0] = 1.0;
					D.rgb[1] = 0.0;
					D.rgb[2] = 0.0;
					D.rotation = 0.0;
					C.params.cyl.isRolling;
					C.params.cyl.isSteering;

					vm.shapes.push_back(D);

					glPopMatrix();

					glPushMatrix();

					ShapeInit E;
					E.type = CYLINDER;
					E.params.cyl.radius = 0.55;
					E.params.cyl.depth = 0.25;
					E.xyz[0] = -1.25;
					E.xyz[1] = 0.0;
					E.xyz[2] = -1.0;
					E.rgb[0] = 1.0;
					E.rgb[1] = 0.0;
					E.rgb[2] = 0.0;
					E.rotation = 0.0;
					C.params.cyl.isRolling;
					C.params.cyl.isSteering;

					glPopMatrix();

					vm.shapes.push_back(E);

					glPushMatrix();

					ShapeInit F;
					F.type = CYLINDER;
					F.params.cyl.radius = 0.55;
					F.params.cyl.depth = 0.25;
					F.xyz[0] = -1.25;
					F.xyz[1] = 0.0;
					F.xyz[2] = 1.0;
					F.rgb[0] = 1.0;
					F.rgb[1] = 0.0;
					F.rgb[2] = 0.0;
					F.rotation = 0.0;
					C.params.cyl.isRolling;
					C.params.cyl.isSteering;

					vm.shapes.push_back(F);

					glPopMatrix();

					glPushMatrix();

					//Spoiler
					ShapeInit G;
					G.type = RECTANGULAR_PRISM;
					G.params.rect.xlen = 0.25;
					G.params.rect.ylen = 0.25;
					G.params.rect.zlen = 3.0;
					G.xyz[0] = -1.875;
					G.xyz[1] = 1.5;
					G.xyz[2] = 0.0;
					G.rgb[0] = 1.0;
					G.rgb[1] = 1.0;
					G.rgb[2] = 0.0;
					G.rotation = 0.0;

					vm.shapes.push_back(G);

					glPopMatrix();

					glPushMatrix();

					//Bumper
					ShapeInit H;
					H.type = TRIANGULAR_PRISM;
					H.params.tri.alen = 0.5;
					H.params.tri.blen = 0.35;
					H.params.tri.depth = 2.0;
					H.params.tri.angle = 90;
					H.xyz[0] = 2.25;
					H.xyz[1] = 0.5;
					H.xyz[2] = 0.0;
					H.rgb[0] = 1.0;
					H.rgb[1] = 0.0;
					H.rgb[2] = 0.0;
					H.rotation = 0.0;

					vm.shapes.push_back(H);

					glPopMatrix();

					RemoteDataManager::Write(GetVehicleModelStr(vm));
				}
			}
		}

		// if we're connected, send our vehicle state to the server
		if (RemoteDataManager::IsConnected()) {
			VehicleState vs;
			vs.remoteID = 0;
			vs.x = vehicle->getX();
			vs.z = vehicle->getZ();
			vs.rotation = vehicle->getRotation();
			vs.speed = vehicle->getSpeed();
			vs.steering = vehicle->getSteering();
			RemoteDataManager::Write(GetVehicleStateStr(vs));
		}

		// if we're still connected, receive and handle response messages from the server
		if (RemoteDataManager::IsConnected()) {
			std::vector<RemoteMessage> msgs = RemoteDataManager::Read();
			for (unsigned int i = 0; i < msgs.size(); i++) {

				RemoteMessage msg = msgs[i];
				//cout << msg.payload << endl;

				switch (msg.type) {
					// new models
				case 'M':
				{
					std::vector<VehicleModel> models = GetVehicleModels(msg.payload);
					for (unsigned int i = 0; i < models.size(); i++) {
						VehicleModel vm = models[i];

						//Passing the vehicle models structure through to our vehicle1.cpp so that it
						//  can be unpacked and formatted into a more palatable form for drawing
						otherVehicles[vm.remoteID] = new Vehicle1(vm);

					}
					break;

				}

				// vehicle states
				case 'S':
				{
					std::vector<VehicleState> states = GetVehicleStates(msg.payload);
					for (unsigned int i = 0; i < states.size(); i++) {
						VehicleState vs = states[i];

						std::map<int, Vehicle*>::iterator iter = otherVehicles.find(vs.remoteID);
						if (iter != otherVehicles.end()) {
							Vehicle * veh = iter->second;
							remoteDriver(veh, vs.x, vs.z, vs.rotation, vs.speed, vs.steering);
						}
					}
					break;
				}

				// goal state
				case 'G':
				{
					goals = GetGoals(msg.payload);
					break;
				}

				// obstacle state
				case 'O':
				{
					std::vector<ObstacleState> obs = GetObstacles(msg.payload);
					for (unsigned int i = 0; i < obs.size(); i++) {
						Obstacle o(obs[i].x, obs[i].z, obs[i].radius);
						ObstacleManager::get()->addObstacle(o);
					}
					break;
				}

				// disconnect list
				case 'D':
				{
					std::vector<int> disconnectedIDs = GetVehicleDisconnects(msg.payload);
					for (unsigned int i = 0; i < disconnectedIDs.size(); i++) {
						int id = disconnectedIDs[i];
						std::map<int, Vehicle*>::iterator iter = otherVehicles.find(id);
						if (iter != otherVehicles.end()) {
							delete iter->second;
							otherVehicles.erase(iter);
						}
					}
					break;
				}

				// error message
				case 'E':
				{
					cerr << "Server error: " << msg.payload << endl;
					break;
				}

				}
			}
		}
	}


	const float sleep_time_between_frames_in_seconds = 0.025;

	static double previousTime = getTime();
	const double currTime = getTime();
	const double elapsedTime = currTime - previousTime;
	previousTime = currTime;

	// do a simulation step
	if (vehicle != NULL) {
		vehicle->update(speed, steering, elapsedTime);
	}
	for (std::map<int, Vehicle*>::iterator iter = otherVehicles.begin(); iter != otherVehicles.end(); ++iter) {
		iter->second->update(elapsedTime);
	}

	display();

#ifdef _WIN32 
	Sleep(sleep_time_between_frames_in_seconds * 1000);
#else
	usleep(sleep_time_between_frames_in_seconds * 1e6);
#endif
};

void keydown(unsigned char key, int x, int y) {

	// keys that will be held down for extended periods of time will be handled
	//   in the idle function
	KeyManager::get()->asciiKeyPressed(key);

	// keys that react ocne when pressed rather than need to be held down
	//   can be handles normally, like this...
	switch (key) {
	case 27: // ESC key
		exit(0);
		break;
	case '0':
		Camera::get()->jumpToOrigin();
		break;
	case 'p':
		Camera::get()->togglePursuitMode();
		break;
	}

};

void keyup(unsigned char key, int x, int y) {
	KeyManager::get()->asciiKeyReleased(key);
};

void special_keydown(int keycode, int x, int y) {

	KeyManager::get()->specialKeyPressed(keycode);

};

void special_keyup(int keycode, int x, int y) {
	KeyManager::get()->specialKeyReleased(keycode);
};

void mouse(int button, int state, int x, int y) {

};

void dragged(int x, int y) {

	if (prev_mouse_x >= 0) {

		int dx = x - prev_mouse_x;
		int dy = y - prev_mouse_y;

		Camera::get()->mouseRotateCamera(dx, dy);
	}

	prev_mouse_x = x;
	prev_mouse_y = y;
};

void motion(int x, int y) {

	prev_mouse_x = x;
	prev_mouse_y = y;
};