#pragma once
#include "Particle.h"

#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>

class Esfera {
public:
	glm::vec3 pos; //Stores Current Position
	float radius; //radius of the sphere

	Esfera();
	~Esfera();
};
