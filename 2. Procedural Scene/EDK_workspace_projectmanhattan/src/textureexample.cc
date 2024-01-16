#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>
#include "Singleton.h"
#include <EDK3/geometry.h>
#include "FPCamera.h"
#include <EDK3/drawable.h>
#include <EDK3/texture.h>
#include <EDK3/matdiffusetexture.h>
#include "matcustom_jsf.h"
#include "buildings.h"
#include "buildinggeometries.h"
#include "block.h"
#include "City.h"
#include "RoadGeometries.h"
#include "Roads.h"
#include "TrafficLight.h"
#include <EDK3/dev/gpumanager.h>
#include <time.h> 
#include <stdlib.h>
#include <string>
#include <vector>
#include <EDK3/dev/opengl.h>
#include <iostream>
#include "stb_image.h"
#include <EDK3/dev/shader.h>
#include "math/matrix_4.h"

#include <ESAT_extra/imgui.h>

using namespace std;

using namespace ESAT;
using namespace EDK3;
using namespace EDK3::dev;

bool wireframed = true;
double previus_time;
const float rgba[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
int rows = 3, cols = 3;



struct GameState {
	ref_ptr<JSF::FPCamera> camera;
	ref_ptr<Node> root;
	EDK3::ref_ptr<JSF::City> ProceduralCity;
	ref_ptr<JSF::BuildingGeometries> building_geo_text;
	ref_ptr<JSF::RoadGeometries> road_geometries;

};

void ChangeWireframe() {
	if (!wireframed) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void ImGUIRenger(GameState* state) {
	ImGui::Begin("Project Manhattan");

	ImGui::Checkbox("Wireframe: ", &wireframed);

	ImGui::InputInt("Rows: ", &rows);
	ImGui::InputInt("Cols: ", &cols);

	if (ImGui::Button("Generate City")) {
		if (rows != state->ProceduralCity->GetRows() || cols != state->ProceduralCity->GetCols()) {
				
			state->ProceduralCity->SetRows(rows);
			state->ProceduralCity->SetCols(cols);
			state->ProceduralCity->GenerateCity(state->building_geo_text, state->road_geometries);
			state->ProceduralCity->GenerateRoad(state->road_geometries.get());
			state->ProceduralCity->set_scale(0.3f, 0.3f, 0.3f);

		}

	}
	Singleton* s = Singleton::getInstance();
	float power = 10.0f;
	ImGui::DragFloat("Fog distance", &s->FarDistance, power);

	ImGui::DragFloat("Directional intensity", &s->DirectionalIntensity, 0.01f);


	ImGui::End();
	ImGui::Render();
}


//std::vector<double> CalcNormal(std::vector<double> v1, std::vector<double> v2, std::vector<double> v3)
//
//{
//	double v1x, v1y, v1z, v2x, v2y, v2z;
//	double nx, ny, nz;
//	double vLen;
//	std::vector<double> Result;
//
//	// Calculate vectors
//	v1x = v1.x - v2.x;
//	v1y = v1.y - v2.y;
//	v1z = v1.z - v2.z;
//	v2x = v2.x - v3.x;
//	v2y = v2.y - v3.y;
//	v2z = v2.z - v3.z;
//
//	// Get cross product of vectors
//	nx = (v1y * v2z) - (v1z * v2y);
//	ny = (v1z * v2x) - (v1x * v2z);
//	nz = (v1x * v2y) - (v1y * v2x);
//
//	// Normalise final vector
//	vLen = sqrt((nx * nx) + (ny * ny) + (nz * nz));
//	Result.x = (float)(nx / vLen);
//	Result.y = (float)(ny / vLen);
//	Result.z = (float)(nz / vLen);
//	return Result;
//}

const float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f, -1.0f,
	 1.0f,  1.0f,  1.0f,
	 1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f, -1.0f,
	 1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	 1.0f, -1.0f,  1.0f
};
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};
unsigned int loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

void prepare(GameState *state) {

	GPUManager::CheckGLError("Prepare Start");
	
	// Nodes
	Node* root = state->root.alloc();	



	state->building_geo_text.alloc();
	state->road_geometries.alloc();


	state->ProceduralCity.alloc();


	state->ProceduralCity->SetRows(rows);
	state->ProceduralCity->SetCols(cols);
	state->ProceduralCity->GenerateCity(state->building_geo_text.get(), state->road_geometries.get());
	state->ProceduralCity->GenerateRoad(state->road_geometries.get());
	state->ProceduralCity->set_scale(0.3f, 0.3f, 0.3f);
	root->addChild(state->ProceduralCity.get());





	











	float pos[] = { 500.0f, 1000.0f, 2200.0f };
	float view[] = { 0.0f, 0.0f, -1.0f };
	

	// Create a Camera
	state->camera.alloc();

	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->setupPerspective(70, 1280.0f / 720.0f, 0.01f, 25000.0f);
	state->camera->set_clear_color(0.0f, 0.0f, 0.0f, 0.0f);
	
	GPUManager::CheckGLError("Prepare END");
}

void render_function(GameState *state) {
	
	Singleton* s = Singleton::getInstance();


	if (!s->left_move && !s->up_move) {
		s->patrol_position.x++;
		if (s->patrol_position.x >= cols * 600.0f) {
			s->left_move = true;
			s->up_move = true;
		}
	}
	if (s->left_move && s->up_move) {
		s->patrol_position.z++;
		if (s->patrol_position.z >= rows * 600.0f) {
			s->left_move = true;
			s->up_move = false;
		}
	}
	else if (s->left_move && !s->up_move) {
		s->patrol_position.x--;
		if (s->patrol_position.x <= 10.0f) {
			s->left_move = false;
			s->up_move = true;
		}
	}if (!s->left_move && s->up_move) {
		s->patrol_position.z--;
		if (s->patrol_position.z <= 10.0f) {
			s->left_move = false;
			s->up_move = false;
		}
	}
		
	ChangeWireframe();
	// Update
	float rotationX = state->root->rotation_xyz()[0];
	rotationX = MousePositionY();


	float rotationY = state->root->rotation_xyz()[1];	
	rotationY = MousePositionX();

	
	state->camera->move(1.0f);
	state->camera->RotateCamera(1.0f, 1.0f);

	

	GPUManager::Instance()->clearFrameBuffer(rgba);
	// For Every frame... determine what's visible:
	state->camera->doCull(state->root.get());
	


	// Render
	GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	GPUManager::CheckGLError("end Render-->");
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}




int ESAT::main(int argc, char **argv) {
	
	Singleton* s = Singleton::getInstance();
	s->FarDistance = 4000.0f;
	// State
	GameState state;
	WindowInit(1280, 720);
	DrawSetTextFont("test.ttf");
	DrawSetTextSize(18);
	DrawSetFillColor(253, 255, 255, 128);
	
	prepare(&state);
	
	double lastTime = clock();
	int nbFrames = 0;

	
	// Main loop
	while (WindowIsOpened() && !IsSpecialKeyDown(kSpecialKey_Escape)) {
		srand(time(NULL));
	
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		if (ESAT::IsKeyDown('1')) {
			wireframed = !wireframed;
		}
		render_function(&state);
		
		ImGUIRenger(&state);

		
		WindowFrame();
	}

	return 0;
}
