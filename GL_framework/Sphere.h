#pragma once
#include "Particle.h"

#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>

class Esfera {
public:
	glm::vec3 pos, lastPos; //Stores Current and Last Position
	glm::vec3 currentV, lastV; //Stores Current and Last Velocity
	glm::vec3 forces; //Stores the resultant of the forces applied to this particle in a determined instant of time

	float density; //density of the sphere
	float radius; //radius of the sphere
	float mass; //mass of the sphere

	Esfera();
	~Esfera();
};
