#pragma once
#include "../Particle.h"
#include "../Collision.h"
#include "../Sphere.h"

#define _USE_MATH_DEFINES

#include <glm\gtc\matrix_transform.hpp>
#include <math.h>

#define C_Drag 0.47f
//#define Cross_Sectional_Area (esfera->radius * 2.f * M_PI) / 2.f //el area de un circulo de diametro entre 0 i (esfera->radio *2) 
#define C_Lift 0.15f

static void Calculate_Buoyancy(Esfera *esfera) {
	//formula:
	//F = density * gravity * V_sub (some value that depends on the displaced height of the fluid)
	glm::vec3 norm = glm::vec3(0.f, 1.f, 0.f);

	float Vsub;
	float avg_Y = 0;
	float submergido;

	for (int i = 0; i < AvgParts; i++) {
		avg_Y += partForces_parts[i].currentPos.y;
	}

	avg_Y = avg_Y / AvgParts;

	submergido = avg_Y - (esfera->pos.y - esfera->radius);

	if (submergido > 0.f) {
		if (submergido < esfera->radius * 2.f) {
			Vsub = esfera->radius * esfera->radius * submergido;
		}
		else {
			Vsub = esfera->radius * esfera->radius * esfera->radius * 2.f;
		}
		esfera->forces += esfera->density * -GRAVITY * Vsub * norm;
	}

	std::cout << esfera->forces.y << std::endl;
	
}

static void Calculate_Drag(Esfera *esfera) {
	//formula
	//F = -0.5f * density * Drag_coefficient * crossSectionalArea * RelativeVelocityBetweenObject&Fluid

	float avg_Y = 0;
	float submergido;

	for (int i = 0; i < AvgParts; i++) {
		avg_Y += partForces_parts[i].currentPos.y;
	}

	avg_Y = avg_Y / AvgParts;

	submergido = avg_Y - (esfera->pos.y - esfera->radius);

	float r = sqrt((esfera->radius*esfera->radius)-(submergido * submergido));
	float Cross_Sectional_Area;

	if (r > 0) Cross_Sectional_Area = M_PI * r * r;
	else Cross_Sectional_Area = 0;

	esfera->forces += -0.5f * esfera->density * C_Drag * Cross_Sectional_Area * glm::normalize(esfera->currentV) * esfera->currentV;
}

static void Calculate_Lift(Esfera *esfera) {
	//formula
	//F = -0.5f * density * Lift_coefficient * crossSectionalArea * RelativeVelocityBetweenObject&Fluid * 

	esfera->forces += -0.5f * esfera->density * C_Lift;
}


static void Calculate_Forces(Esfera *esfera) {
	//first of all, we clean all the forces
	esfera->forces = glm::vec3{ 0.f,0.f,0.f };

	//calculate forces
	Calculate_Buoyancy(esfera);
	Calculate_Drag(esfera);

	esfera->collision = false;

}