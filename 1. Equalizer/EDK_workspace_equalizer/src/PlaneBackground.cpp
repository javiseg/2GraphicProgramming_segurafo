#include "PlaneBackground.h"
#include "..\include\PlaneBackground.h"

void PlaneBackground::init()
{

	// generate vertices
	float positions[] = {
		-0.5f, 0.5f, 0.5f,		// 0
		-0.5f, -0.5f, 0.5f,		// 1
		0.5f, -0.5f, 0.5f,		// 2
		0.5f, 0.5f, 0.5f, 		// 3

		0.5f, 0.5f, 0.5f,  		// 4
		0.5f, -0.5f, 0.5f,		// 5
		0.5f, -0.5f, -0.5f,		// 6
		0.5f, 0.5f, -0.5f,    // 7

		-0.5f, 0.5f, -0.5f,		// 8
		-0.5f, 0.5f, 0.5f,		// 9
		0.5f, 0.5f, 0.5f,			// 10
		0.5f, 0.5f, -0.5f,		// 11

		-0.5f, 0.5f, -0.5f,		// 12
		-0.5f, -0.5f, -0.5f,	// 13
		0.5f, -0.5f, -0.5f,		// 14
		0.5f, 0.5f, -0.5f, 		// 15

		-0.5f, 0.5f, 0.5f,  	// 16
		-0.5f, -0.5f, 0.5f,		// 17
		-0.5f, -0.5f, -0.5f,	// 18
		-0.5f, 0.5f, -0.5f,   // 19

		-0.5f, -0.5f, -0.5f,	// 20
		-0.5f, -0.5f, 0.5f,		// 21
		0.5f, -0.5f, 0.5f,		// 22
		0.5f, -0.5f, -0.5f,		// 23
	};


	float normals[] = {
		0.0f, 0.0f, 0.1f,
		0.0f, 0.0f, 0.1f,
		0.0f, 0.0f, 0.1f,
		0.0f, 0.0f, 0.1f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, -0.1f,
		0.0f, 0.0f, -0.1f,
		0.0f, 0.0f, -0.1f,
		0.0f, 0.0f, -0.1f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
	};


	int positions_size = sizeof(positions);
	int normals_size = sizeof(normals);
	int total_vertices_size = positions_size + normals_size;

	this->createVertices(total_vertices_size);

	this->uploadVertexPosition(positions, positions_size);
	this->uploadVertexNormals(normals, normals_size, positions_size);

	// generate idices
	unsigned int indices[] = { 0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7, 8, 9, 10, 8, 10, 11, 15, 14, 13, 15, 13, 12, 19, 18, 16, 16, 18, 17, 21, 20, 22, 22, 20, 23 };
	this->createIndices(36);
	this->uploadIndices(indices, sizeof(indices));





}
