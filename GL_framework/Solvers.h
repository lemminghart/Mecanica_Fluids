#pragma once

#include <cmath>

#include "../Particle.h"
#include "../Sphere.h"

#define GRAVITY -9.81f

enum SOLVER { EULER = 0, VERLET = 1 };

static void Solver_Waves(Particle *part, glm::vec3 K, float A, float W, float T) {
	//k = dirección de las olas
	//A = altura de las olas
	//w = frecuencia de las olas
	//t = tiempo acumulado

	// WAVES SECTION
	part->currentPos = part->OriginalPos - (glm::normalize(K))*A*sin(glm::dot(K, part->OriginalPos) - W*T);
	part->currentPos.y = (A*cos(glm::dot(K, part->OriginalPos) - W*T))+3; //le sumo la altura minima que quiero que tenga
}

static void Solver_Sphere(Esfera *Sphere, float dt) {
	//SPHERE SECTION

	//set the current position & speed as the last
	Sphere->lastPos = Sphere->pos;
	Sphere->lastV = Sphere->currentV;

	//Calculate the new position
	// P = P. + dt * V.
	Sphere->pos.x = Sphere->pos.x + (dt * Sphere->currentV.x);
	Sphere->pos.y = Sphere->pos.y + (dt * Sphere->currentV.y);
	Sphere->pos.z = Sphere->pos.z + (dt * Sphere->currentV.z);

	//Calculate the new velocity
	// V = V. + dt * (F/m)[acceleration]
	//We only need to recalculate the V on Y, it's the only one affected by external force
	Sphere->currentV.x = Sphere->currentV.x + (dt * Sphere->forces.x);
	Sphere->currentV.y = Sphere->currentV.y + (dt * (GRAVITY + Sphere->forces.y));
	Sphere->currentV.z = Sphere->currentV.z + (dt * Sphere->forces.z);
}

//static void Verlet_Solver(Particle *part, float dt) {
//	//set the current position & speed as the last
//	glm::vec3 tmp = part->currentPos;
//	part->lastV = part->currentV;
//
//	//Calculate the new position
//	// P = P + (P - P.) + F/m * dt^2
//	//Notice only the Y has external force, the other ones F/m = 0
//	part->currentPos.x = part->currentPos.x + (part->currentPos.x - part->lastPos.x);
//	part->currentPos.y = part->currentPos.y + (part->currentPos.y - part->lastPos.y) + (GRAVITY * pow(dt, 2));
//	part->currentPos.z = part->currentPos.z + (part->currentPos.z - part->lastPos.z);
//
//	part->lastPos = tmp;
//
//	//Calculate velocity
//	//  V = (X_t+1 - X_t) / dt
//	part->currentV.x = (part->currentPos.x - part->lastPos.x) / dt;
//	part->currentV.y = (part->currentPos.y - part->lastPos.y) / dt;
//	part->currentV.z = (part->currentPos.z - part->lastPos.z) / dt;
//}