#pragma once
#include <vector>
#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>

#define AvgParts 4

class Particle {
public:
	glm::vec3 currentPos, lastPos, OriginalPos; //Stores Current and Last Position
	glm::vec3 currentV, lastV; //Stores Current and Last Velocity
	glm::vec3 forces; //Stores the resultant of the forces applied to this particle in a determined instant of time
	//float lifeTime; //Life time of the particle
	bool fixed; //states if particle is animated or not
	int index;

	Particle();
	Particle(bool fix, glm::vec3 pos);
	Particle(Particle *part, float separationX, float separationZ);
	~Particle();
};

static std::vector <Particle> partArray; //vector de particulas

static Particle partForces_parts[AvgParts];