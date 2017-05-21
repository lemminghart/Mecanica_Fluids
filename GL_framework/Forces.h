#pragma once
#include "../Particle.h"
#include "../Collision.h"
#include "../Sphere.h"

#define Vsub 0.2f

struct Index {
	int F, C; //Fila & Columna
};

namespace Utils {
	//separation between particles
	extern float part_separation;
}

namespace ClothMesh {
	extern void setupClothMesh();
	extern void cleanupClothMesh();
	extern void updateClothMesh(float* array_data);
	extern void drawClothMesh();
	extern const int numCols; //14
	extern const int numRows; //18
	extern const int numVerts; // 14 * 18 = 252
}


static void Calculate_Buoyancy(Esfera *esfera) {
	//formula:
	//F = density * gravity * V_sub (some value that depends on the displaced height of the fluid)
	glm::vec3 norm = glm::vec3(0.f, 1.f, 0.f);

	esfera->forces += esfera->density * GRAVITY * Vsub * norm;
}

static float Calculate_Drag(Esfera *esfera) {
	//formula
	//F = -0.5f * density * Drag_coefficient * crossSectionalArea * RelativeVelocityBetweenObject&Fluid
}

static float Calculate_Lift(Esfera *esfera) {
	
}


static void Calculate_Forces(Esfera *esfera) {
	//first of all, we clean all the forces
	esfera->forces = glm::vec3{ 0.f,0.f,0.f };

	//calculate forces
	Calculate_Buoyancy(esfera);

}