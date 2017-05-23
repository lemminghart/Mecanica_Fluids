#define _USE_MATH_DEFINES

#include <glm\gtc\matrix_transform.hpp>
#include <math.h>

#include "../Sphere.h"

Esfera::Esfera() {
	//setup the initial parameters
	radius = ((float)rand() / RAND_MAX) * 1.f + .5f;

	mass = 1.f;

	density = (4.f * M_PI * pow(radius, 3.f)) / 3.f;

	area = 4.f * M_PI * pow(radius, 2.f);

	//setup the initial position
	pos.x = ((float)rand() / RAND_MAX) * 8.f - 4.f;
	pos.y = ((float)rand() / RAND_MAX) * 3.f + 5.f;
	pos.z = ((float)rand() / RAND_MAX) * 8.f - 4.f;

	//setup the last pos
	lastPos = pos;

	//setup the initial forces
	forces = { 0.f,0.f,0.f };

	//setup the initial speed
	currentV.x = 0.f;
	currentV.y = 0.f;
	currentV.z = 0.f;

	//setup the last velocity
	lastV = currentV;

	collision = false;
}

Esfera::~Esfera() {

}
