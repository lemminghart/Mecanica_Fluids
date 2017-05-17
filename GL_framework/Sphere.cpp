#include "../Sphere.h"
#include <glm\gtc\matrix_transform.hpp>

Esfera::Esfera() {
	//setup the initial parameters (position)
	radius = ((float)rand() / RAND_MAX) * 1.f + .5f;

	//setup the initial position
	pos.x = ((float)rand() / RAND_MAX) * 8.f - 4.f;
	pos.y = ((float)rand() / RAND_MAX) * 3.f + 5.f;
	pos.z = ((float)rand() / RAND_MAX) * 8.f - 4.f;

	//setup the last pos
	lastPos = pos;

	//setup the initial forces
	forces = { 0,0,0 };

	//setup the initial speed
	currentV.x = 0.f;
	currentV.y = 0.f;
	currentV.z = 0.f;

	//setup the last velocity
	lastV = currentV;


}

Esfera::~Esfera() {

}
