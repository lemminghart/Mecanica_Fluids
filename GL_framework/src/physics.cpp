#include <GL\glew.h>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <cstdio>
#include <iostream>

#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>

#include "../Particle.h"
#include "../Solvers.h"
#include "../Collision.h"
#include "../Sphere.h"
#include "../Forces.h"

namespace ClothMesh {
	extern void setupClothMesh();
	extern void cleanupClothMesh();
	extern void updateClothMesh(float* array_data);
	extern void drawClothMesh();
	extern const int numCols; //14
	extern const int numRows; //18
	extern const int numVerts; // 14 * 18 = 252
}

namespace Sphere {
	extern void setupSphere(glm::vec3 pos = glm::vec3(0.f, 1.f, 0.f), float radius = 1.f);
	extern void cleanupSphere();
	extern void updateSphere(glm::vec3 pos, float radius = 1.f);
	extern void drawSphere();
}

//Namespace para manejar variables propias del sistema
namespace Utils {
	//time
	int time = 0;
	//solver
	int solver = EULER; //CAN BE EULER or VERLET

						//separation between particles


	//position of first particle
	//glm::vec3 pos{ -3.5f, 7.f, -4.75f };
	glm::vec3 pos{ -5.f, 3.f, -5.f };

	float Col_separation = 10.f/ClothMesh::numCols;
	float Row_separation = 10.f / ClothMesh::numRows;

	float percent = 0.f;
	float percent_2 = 0.f;
	float percent_3 = 1.f;

	//SIMULATION DATA
	float A = .5f; //Amplitude of the wave
	float W = 2.f; //frequency of waves
	float L = 2.f; //Lambda (distance between wave crest)
	glm::vec3 WaveDirection = glm::vec3(1.f, 0.f, 0.f);

}

//variable global de la esfera
Esfera *esfera;


bool show_test_window = false;
void GUI() {
	{	//FrameRate
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		//TODO
	}

	// ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
	if(show_test_window) {
		ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
		ImGui::ShowTestWindow(&show_test_window);
	}
}

void PhysicsInit() {
	//TODO

	//initialize the sphere
	esfera = new Esfera;

	//we will set up a first particle and then build the mesh from that particle
	//set up the first particle
	

	//we initialite the following particles in base of the first particle
	for (int i = 0; i < ClothMesh::numRows; i++) {
		for (int j = 0; j < ClothMesh::numCols; j++) {
			if (i == 0 && j == 0) {
				Particle temp(false, Utils::pos); //the first particle is fixed
				temp.index = 0;
				partArray.push_back(temp);
			}
			else {
				Particle temp2(&partArray[0], Utils::Col_separation * j, Utils::Row_separation * i);
				//temp2.index = (j + ClothMesh::numCols * i)+1;
				//printf("%d \n", temp2.index);
				partArray.push_back(temp2);
			}
		}
	}

	//partArray.pop_back();

	//for (int i = 0; i < ClothMesh::numVerts; i++) {
	//	partArray[i].index = i;
	//	printf("%d \n", i);
	//}

	//fijamos las particulas en el techo
	//partArray[0].fixed = true;
	//partArray[ClothMesh::numCols - 1].fixed = true;

}
void PhysicsUpdate(float dt) {
	//TODO

	//aqui entra cada 1 segundos
	if (Utils::percent > 0.33f) {
		Utils::time++;
		std::cout << "TIME:" << Utils::time << std::endl;
		//aqui entra cada 5 segundos
		if (Utils::percent_2 > 0.33f * 20.f) {
			std::cout << "RESTART SIM" << std::endl;
			partArray.clear();
			PhysicsInit();

			//bajamos el contador a 0 para que a los 5 segundos vuelva a entrar aqui
			Utils::percent_2 = 0;
		}

		//bajamos el contador a 0 para que al segundo vuelva a entrar aqui
		Utils::percent = 0;

	}

	Utils::percent += dt; //contador incremental
	Utils::percent_2 += dt; //contador incremental
	Utils::percent_3 += dt; //contador incremental

	////Calculamos primero las fuerzas que afectan las particulas
	//for (int i = 0; i < ClothMesh::numVerts; i++) {
	//	Calculate_Forces(partArray[i]);
	//}

	//Actualizamos la posicion de las particulas
	if (Utils::solver == EULER) {
		for (int i = 0; i < ClothMesh::numVerts; i++) {
			if (!partArray[i].fixed) {
				Solver(&partArray[i], Utils::WaveDirection, Utils::A, Utils::W, Utils::percent_3);
				//Collision_Manager(&partArray[i], esfera, Utils::solver);
			}
		}
	}

	//------ UPDATE ZONE -------
	//Update de las particulas
	float *partVerts = new float[ClothMesh::numVerts * 3];
	for (int i = 0; i < ClothMesh::numVerts; ++i) {
			partVerts[i * 3 + 0] = partArray[i].currentPos.x;
			partVerts[i * 3 + 1] = partArray[i].currentPos.y;
			partVerts[i * 3 + 2] = partArray[i].currentPos.z;
			//std::cout << partArray[i].OriginalPos.x << std::endl;
			//std::cout << partArray[i].OriginalPos.y << std::endl;
			//std::cout << partArray[i].OriginalPos.z << std::endl;
			//std::cout << "----------------------" << std::endl;
	}
	ClothMesh::updateClothMesh(partVerts);
	
	delete[] partVerts;

	//update de la esfera
	Sphere::updateSphere(esfera->pos, esfera->radius);



}
void PhysicsCleanup() {
	//delete sphere
	delete esfera;
}