#pragma once
#include "../Particle.h"
#include "../Collision.h"

#define ke 10.f
#define kd 2.f

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

static Index Calculate_Index(int indice) {
	return Index{
		(indice / ClothMesh::numCols),
		(indice % ClothMesh::numCols)
	};
}

static int Reverse_Index(Index index) {
	return (index.C * ClothMesh::numCols);
}


static void Apply_Formula(Particle P1, Particle P2) {
	//F_1 = - (ke(||P1-P2|| - L_12) + kd(v1-v2) · (P1-P2/||P1-P2||)) * (P1-P2/||P1-P2||)

	//- (ke(||P1-P2|| - L_12) +
	glm::vec3 result = -((ke * (glm::length(P1.currentPos - P2.currentPos)) - Utils::part_separation) +
	//kd(v1-v2) · (P1-P2/||P1-P2||))
	glm::dot(kd *(P1.currentV - P2.currentV), glm::normalize(P1.currentPos - P2.currentPos)))
	// (P1-P2/||P1-P2||)
	* glm::normalize(P1.currentPos-P2.currentPos);

	partArray[P1.index].forces = result;
	//partArray[indice2].forces += -1.f * result;
}

static void Calculate_Structural(Particle part, int tempIndex, int indice) {
	//HORIZONTAL
	//comprobar izquierda
	if ((part.index % ClothMesh::numCols) > 0) {
		Apply_Formula(partArray[part.index], partArray[part.index - 1]);
		printf("%d izquierda %d \n", part.index, part.index -1);
	}
	//comrpobar derecha
	if ((part.index % ClothMesh::numCols) < (ClothMesh::numCols-1)) {
		Apply_Formula(partArray[part.index], partArray[part.index + 1]);
		printf("%d derecha %d \n", part.index, part.index +1);
	}
	//VERTICAL
	//comprobar arriba
	if (part.index > ClothMesh::numCols) {
		Apply_Formula(partArray[part.index], partArray[part.index - ClothMesh::numCols]);
		printf("%d arriba %d \n", part.index, part.index - ClothMesh::numCols);
	}
	//comprobar abajo
	if (part.index < (ClothMesh::numCols * ClothMesh::numRows) - ClothMesh::numCols) {
		Apply_Formula(partArray[part.index], partArray[part.index + ClothMesh::numCols]);
		printf("%d abajo %d \n", part.index, part.index + ClothMesh::numCols);
	}	
}

static float Calculate_Shear(Index partIndex, int tempIndex, int indice) {
	//HORIZONTAL
	//comprobar izquierda
	if (partIndex.C > 0) {
		
	}
	//comrpobar derecha
	if (partIndex.C < (ClothMesh::numCols - 1)) {
		
	}
	//VERTICAL
	//comprobar arriba
	if (partIndex.F > 0) {
		
	}
	//comprobar abajo
	if (partIndex.F < (ClothMesh::numRows - 1)) {
		
	}
}

static float Calculate_Bending(Index partIndex, int tempIndex, int indice) {
	//HORIZONTAL
	//comprobar izquierda
	if (partIndex.C > 1) {
		Apply_Formula(partArray[indice], partArray[indice - 1]);
	}
	//comrpobar derecha
	if (partIndex.C < (ClothMesh::numCols - 2)) {

	}
	//VERTICAL
	//comprobar arriba
	if (partIndex.F > 1) {

	}
	//comprobar abajo
	if (partIndex.F < (ClothMesh::numRows - 2)) {

	}
}

static void Calculate_Forces(Particle part) {
	//first of all, we clean all the forces
	part.forces = glm::vec3{ 0,0,0 };

	Index partIndex = Calculate_Index(part.index);
	int tempIndex = 0;

	Calculate_Structural(part, tempIndex, part.index);

	//Calculate_Shear();

	//Calculate_Bending();
	//Comprobación de particulas colindantes
	
	//comprobar particulas colindantes


	
}