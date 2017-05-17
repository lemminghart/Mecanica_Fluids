#pragma once
#include "../Particle.h"
#include <cmath>

#define GRAVITY -9.81

enum SOLVER { EULER = 0, VERLET = 1 };

static void Solver(Particle *part, glm::vec3 K, float A, float W, float T) {
	//k = dirección de las olas
	//A = altura de las olas
	//w = frecuencia de las olas
	//t = tiempo acumulado

	part->currentPos = part->OriginalPos - (glm::normalize(K))*A*sin(glm::dot(K, part->OriginalPos) - W*T);

	part->currentPos.y = (A*cos(glm::dot(K, part->OriginalPos) - W*T))+3; //sle sumo la altura minima que quiero que tenga


	////set the current position & speed as the last
	//part->lastPos = part->currentPos;
	//part->lastV = part->currentV;

	////Calculate the new position
	//// P = P. + dt * V.
	//part->currentPos.x = part->currentPos.x + (dt * part->currentV.x);
	//part->currentPos.y = part->currentPos.y + (dt * part->currentV.y);
	//part->currentPos.z = part->currentPos.z + (dt * part->currentV.z);

	////Calculate the new velocity
	//// V = V. + dt * (F/m)[acceleration]
	////We only need to recalculate the V on Y, it's the only one affected by external force
	//part->currentV.x = part->currentV.x + (dt * part->forces.x);
	//part->currentV.y = part->currentV.y + (dt * (GRAVITY + part->forces.y));
	//part->currentV.z = part->currentV.z + (dt * part->forces.z);
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