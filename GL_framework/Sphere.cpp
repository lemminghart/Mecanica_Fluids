#include "../Sphere.h"
#include <glm\gtc\matrix_transform.hpp>

Esfera::Esfera() {
	//setup the initial parameters (position)
	radius = ((float)rand() / RAND_MAX) * 1.f + 1.5f;;

	//setup the initial position
	pos.x = ((float)rand() / RAND_MAX) * 8.f - 4.f;;
	pos.y = ((float)rand() / RAND_MAX) * 5.f + 5.f;;
	pos.z = ((float)rand() / RAND_MAX) * 8.f - 4.f;;

}

Esfera::~Esfera() {

}
