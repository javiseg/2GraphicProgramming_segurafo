#include <ESAT/window.h>
#include <ESAT/input.h>
#include <ESAT/draw.h>
#include <ESAT/time.h>

#include <EDK3/geometry.h>
#include <EDK3/camera.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffuse.h>
#include <EDK3/dev/gpumanager.h>
#include "matcustom_jsf.h"
#include "JGeometry.h"
#include "JCircle.h"
#include "JCylinder.h"
#include <time.h>
#include <cstdint>
#include <algorithm>

#include "GameState.h"
#include <ESAT_extra/soloud/soloud.h>
#include <ESAT_extra/soloud/soloud_wav.h>
#include "FPCamera.h"
#include "math/vector_3.h"
#include "PlaneBackground.h"

double previus_time;
const int kNumberCubes = 64;
const int kMaxWave = 256;
const int kMaxStars = 400;



void prepareStage1(GameState* state) {
	/////////////////////
	///// Background ////
	/////////////////////

	state->bg_color[0] = 0 / 255.0f;
	state->bg_color[1] = 0 / 255.0f;
	state->bg_color[2] = 0 / 255.0f, 1.0f;
	state->bg_color[3] = 1.0f;

	EDK3::ref_ptr<PlaneBackground> bgPlane;
	bgPlane.alloc();
	bgPlane->init();

	EDK3::ref_ptr < EDK3::Drawable> drawBackground;

	EDK3::ref_ptr<MatCustomJSF> diffuse_material_background;

	diffuse_material_background.alloc();

	state->material_background_settings.alloc();
	state->material_background_settings->set_color(state->bg_color);
	diffuse_material_background->load_shaders_from_filepaths("./shaders/background1.vert", "./shaders/background1.frag");

	drawBackground.alloc();
	drawBackground->set_geometry(bgPlane.get());
	drawBackground->set_material(diffuse_material_background.get());
	drawBackground->set_material_settings(state->material_background_settings.get());
	drawBackground->set_scale(310.5f, 260.5f, 0.5f);
	drawBackground->set_position(0.0f, 0.0f, -36.0f);

	state->root->addChild(drawBackground.get());

	state->root->childIndex(drawBackground.get(), &(state->childBackground));

	EDK3::ref_ptr < EDK3::Drawable> sideBackground;

	sideBackground.alloc();
	sideBackground->set_geometry(bgPlane.get());
	sideBackground->set_material(diffuse_material_background.get());
	sideBackground->set_material_settings(state->material_background_settings.get());
	sideBackground->set_scale(0.5f, 360.5f, 490.5f);
	sideBackground->set_position(200.0f, 0.0f, 0.0f);

	state->root->addChild(sideBackground.get());

	//////////////////////

	EDK3::ref_ptr<EDK3::Node> equalizer_node;
	equalizer_node.alloc();
	equalizer_node->set_position(0.0f, 0.0f, 0.0f);
	equalizer_node->set_scale(1.0f, 1.0f, 1.0f);

	// Create cube
	EDK3::ref_ptr<EDK3::Geometry> cube_geometry;
	EDK3::CreateCube(&cube_geometry, 1.0f, true, false);

	// Material
	EDK3::ref_ptr<MatCustomJSF> cube_material;
	EDK3::ref_ptr<MatCustomJSF::Settings> diffuse_material_settings;
	EDK3::ref_ptr<MatCustomJSF::Settings> diffuse_material_settings_bottom_cube;

	cube_material.alloc();
	diffuse_material_settings.alloc();
	diffuse_material_settings_bottom_cube.alloc();


	// Create a Drawable Node (Geometry + Material + Settings)
	EDK3::ref_ptr<EDK3::Drawable> drawable[kNumberCubes];

	// Create nodes for transform
	EDK3::ref_ptr<EDK3::Node> transformNodes[kNumberCubes];

	// Color 
	float blue_color[] = {0.0f, 100.0f, 255.0f, 1.0f };
	cube_material->load_shaders_from_filepaths("./shaders/equacube.vert", "./shaders/equacube.frag");
	diffuse_material_settings->set_color(blue_color);
	float blue_color_lowalpha[] = { 0.0f , 100.0f, 255.0f, 0.5f };
	diffuse_material_settings_bottom_cube->set_color(blue_color_lowalpha);

	// Graphic
	for (int i = 0; i < kNumberCubes / 2; i++) {
		drawable[i].alloc();
		drawable[i]->set_geometry(cube_geometry.get());
		drawable[i]->set_material(cube_material.get());
		drawable[i]->set_material_settings(diffuse_material_settings.get());
		drawable[i]->set_scale(0.5f, 0.5f, 0.5f);
		drawable[i]->set_position(-1.0f, 0.25f, 0.0f);
		transformNodes[i].alloc();
		transformNodes[i]->set_position(i * 0.7f - (kNumberCubes / 2.0f / 2.0f) * 0.7f, -7.0f, -15.0f);
		transformNodes[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes[i]->addChild(drawable[i].get());

		equalizer_node->addChild(transformNodes[i].get());
	}

	for (int i = kNumberCubes / 2; i < kNumberCubes; i++) {
		drawable[i].alloc();
		drawable[i]->set_geometry(cube_geometry.get());
		drawable[i]->set_material(cube_material.get());
		drawable[i]->set_material_settings(diffuse_material_settings_bottom_cube.get());
		drawable[i]->set_scale(0.5f, 0.5f, 0.5f);
		drawable[i]->set_position(-1.0f, -0.25f, 0.0f);
		transformNodes[i].alloc();
		transformNodes[i]->set_position(((i - kNumberCubes / 2.0f) * 0.7f - (kNumberCubes / 2.0f / 2.0f) * 0.7f), -7.0f - 0.3f, -15.0f);
		transformNodes[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes[i]->addChild(drawable[i].get());
		equalizer_node->addChild(transformNodes[i].get());
	}

	state->root->addChild(equalizer_node.get());
	state->root->childIndex(equalizer_node.get(), &state->equalizer_index);



	// Transform







	////// 
	//Circles
	//////

	// Y positive rotation

	EDK3::ref_ptr<EDK3::Node> circle_center_rotation_YPos;
	circle_center_rotation_YPos.alloc();
	circle_center_rotation_YPos->set_position(-5.0f, 0.0f, -17.0f);
	circle_center_rotation_YPos->set_scale(1.0f, 1.0f, 1.0f);

	state->circle_color[0] = 0.0f;
	state->circle_color[1] = 0.0f;
	state->circle_color[2] = 0.0f;
	state->circle_color[3] = 1.0f;
	EDK3::ref_ptr<JSF::JCircle> circle;
	circle.alloc();
	circle->buildVertices(0.5f, 64, 24);
	circle->init();
	EDK3::ref_ptr<MatCustomJSF> ma;
	EDK3::ref_ptr<EDK3::Drawable> circle1_Pos;
	EDK3::ref_ptr<EDK3::Drawable> circle2_Pos;

	ma.alloc();
	state->material_circles_settings.alloc();
	state->material_circles_settings->set_color(state->circle_color);
	ma->load_shaders_from_filepaths("./shaders/background1.vert", "./shaders/background1.frag");
	float scale[3] = { 1.0f, 1.0f, 1.0f };
	float positions[3] = { 15.0f, 0.0f, -10.0f };
	circle1_Pos.alloc();
	circle2_Pos.alloc();
	CreateSphere(&circle1_Pos, &circle, &ma, &state->material_circles_settings, scale, positions);
	float scale2[3] = { 1.0f, 1.0f, 1.0f };
	float positions2[3] = { 3.0f, 3.0f, 4.0f };
	CreateSphere(&circle2_Pos, &circle, &ma, &state->material_circles_settings, scale2, positions2);



	circle_center_rotation_YPos->addChild(circle1_Pos.get());
	circle_center_rotation_YPos->addChild(circle2_Pos.get());

	state->root->addChild(circle_center_rotation_YPos.get());
	state->root->childIndex(circle_center_rotation_YPos.get(), &state->circleIndex_left);


	// Y negative rotation 

	EDK3::ref_ptr<EDK3::Node> circle_center_rotation_YNeg;
	circle_center_rotation_YNeg.alloc();
	circle_center_rotation_YNeg->set_position(-5.0f, 0.0f, -10.0f);
	circle_center_rotation_YNeg->set_scale(1.0f, 1.0f, 1.0f);

	EDK3::ref_ptr<EDK3::Drawable> circle1_Neg;
	EDK3::ref_ptr<EDK3::Drawable> circle2_Neg;

	float scale3[3] = { 1.0f, 1.0f, 1.0f };
	float positions3[3] = { -3.0f, -2.0f, 4.0f };
	circle1_Neg.alloc();
	circle2_Neg.alloc();
	CreateSphere(&circle1_Neg, &circle, &ma, &state->material_circles_settings, scale3, positions3);
	float scale4[3] = { 1.0f, 1.0f, 1.0f };
	float positions4[3] = { -11.0f, -6.0f, -6.0f };
	CreateSphere(&circle2_Neg, &circle, &ma, &state->material_circles_settings, scale4, positions4);


	circle_center_rotation_YNeg->addChild(circle1_Neg.get());

	circle_center_rotation_YNeg->addChild(circle2_Neg.get());

	state->root->addChild(circle_center_rotation_YNeg.get());

	state->root->childIndex(circle_center_rotation_YNeg.get(), &state->circleIndex_right);



	////////
	//Stars
	///////
	EDK3::ref_ptr<JSF::JCircle> stars_geometry;
	stars_geometry.alloc();
	stars_geometry->buildVertices(0.1f, 32, 12);
	stars_geometry->init();


	EDK3::ref_ptr<MatCustomJSF> diffuse_material_stars;
	EDK3::ref_ptr<MatCustomJSF::Settings> diffuse_material_settings_stars;

	diffuse_material_stars.alloc();
	diffuse_material_settings_stars.alloc();

	float star_color[4] = { 255.0f, 255.0f, 255.0f, 1.0f };
	float scale_stars[3] = { 1.0f, 1.0f, 1.0f };
	float position_stars[3] = { 0.0f, 0.0f, -16.0f };

	diffuse_material_settings_stars->set_color(star_color);
	diffuse_material_stars->load_shaders_from_filepaths("./shaders/stars.vert", "./shaders/stars.frag");

	EDK3::ref_ptr<EDK3::Node> stars_node;
	stars_node.alloc();


	for (int i = 0; i < kMaxStars; i++) {
		EDK3::ref_ptr <EDK3::Drawable> drawStars;
		drawStars.alloc();
		position_stars[0] = ((float)rand()) / ((RAND_MAX / 192));
		position_stars[0] -= 96.0f;

		position_stars[1] = ((float)rand()) / ((RAND_MAX / 172));
		position_stars[1] -= 86.0f;

		CreateSphere(&drawStars, &stars_geometry, &diffuse_material_stars,
			&diffuse_material_settings_stars, scale_stars, position_stars);
		stars_node->addChild(drawStars.get());

	}

	state->root->addChild(stars_node.get());

	state->root->childIndex(stars_node.get(), &state->stars_index);


	///////
	// ring of cubes
	///////

	state->ring_index = 0;
}

void prepareStage2(GameState* state) {

	///////////
	/// Camera
	///////////

	float pos[] = { 0.0f, 0.0f, 8.00f };
	float view[] = { 0.0f, 0.0f, 0.0f };
	float target[] = { 0.0f, 0.0f, -30.0f };
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->set_view_target(target);
	state->camera->setupPerspective(70, 1280.0f / 720.0f, 1.0f, 1500.0f);
	state->camera->set_clear_color(0.99f, 0.99f, 0.99f, 1.0f);

	/////////////////////
	///// Background ////
	/////////////////////

	state->bg_color[0] = 0 / 255.0f;
	state->bg_color[1] = 0 / 255.0f;
	state->bg_color[2] = 0 / 255.0f;
	state->bg_color[3] = 1.0f;

	EDK3::ref_ptr<PlaneBackground> bgPlane;
	bgPlane.alloc();
	bgPlane->init();

	EDK3::ref_ptr < EDK3::Drawable> drawBackground;

	EDK3::ref_ptr<MatCustomJSF> diffuse_material_background;

	diffuse_material_background.alloc();

	state->material_background_settings.alloc();
	state->material_background_settings->set_color(0.0f,0.0f,0.0f,1.0f);
	diffuse_material_background->load_shaders_from_filepaths("./shaders/background2.vert", "./shaders/background2.frag");

	drawBackground.alloc();
	drawBackground->set_geometry(bgPlane.get());
	drawBackground->set_material(diffuse_material_background.get());
	drawBackground->set_material_settings(state->material_background_settings.get());
	drawBackground->set_scale(310.5f, 260.5f, 0.5f);
	drawBackground->set_position(0.0f, 0.0f, -36.0f);

	state->root->addChild(drawBackground.get());

	state->root->childIndex(drawBackground.get(), &(state->childBackground));


	////////////////
	/// CircleWave
	///////////////

	
	/*
	/////////////
	///////Create Cylinders
	/////////////
	
	EDK3::ref_ptr<EDK3::Node> cylinder_container;
	cylinder_container.alloc();
	cylinder_container->set_position(0.0f, 0.0f, -30.0f);
	cylinder_container->set_scale(1.0f, 1.0f, 1.0f);

	EDK3::ref_ptr<JSF::JCylinder> cylinder;
	cylinder.alloc();
	cylinder->set(4.0f, 2.0f, 8.0f, 64, 24, true);
	cylinder->init();
	EDK3::ref_ptr<MatCustomJSF> ma;
	

	ma.alloc();
	state->material_circles_settings.alloc();
	state->circle_color[0] = 255.0f;
	state->circle_color[1] = 0.0f;
	state->circle_color[2] = 255.0f;
	state->circle_color[3] = 1.0f;
	state->material_circles_settings->set_color(state->circle_color);
	ma->load_shaders_from_filepaths("./shaders/cylinder.vert", "./shaders/cylinder.frag");
	float scale[3] = { 1.0f, 1.0f, 1.0f };
	float positions[3] = { 0.0f, 0.0f, 0.0f };

	const int num_cilinders = 3;
	float base = 4.0f;
	float top = 4.0f;

	EDK3::ref_ptr<EDK3::Node> transformNodes[num_cilinders];
	transformNodes->alloc();

	for (int i = 0; i < num_cilinders; i++) {

		EDK3::ref_ptr<EDK3::Drawable> cylinder_draw;
		cylinder_draw.alloc();

		cylinder->set(base, top, 8.0f, 64, 24, true);
		cylinder->init();

		CreateCylinder(&cylinder_draw, &cylinder, &ma, &state->material_circles_settings, scale, positions);
		
		cylinder_draw->set_position(-1.0f, 0.25f, 0.0f);
		
		transformNodes[i].alloc();
		transformNodes[i]->set_position(0.0f, 0.0f, 0.0f);
		transformNodes[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes[i]->addChild(cylinder_draw.get());

		if (i > 0) {
			float posix[3];
			posix[0] = positions[0] * -1;
			posix[1] = positions[1];
			posix[2] = positions[2];

			EDK3::ref_ptr<EDK3::Drawable> cylinder_draw2;
			cylinder_draw2.alloc();

			cylinder->set(base, top, 8.0f, 64, 24, true);
			cylinder->init();

			CreateCylinder(&cylinder_draw2, &cylinder, &ma, &state->material_circles_settings, scale, posix);
			
			transformNodes[i]->addChild(cylinder_draw2.get());
			
			
		}
		cylinder_container->addChild(transformNodes[i].get());


		positions[0] -= 6.0f;
		scale[0] -= 0.25f;
		scale[1] -= 0.25f;
		scale[2] -= 0.25f;
		base -= 0.5f;
		top -= 1.5f;

	}


	state->root->addChild(cylinder_container.get());
	state->root->childIndex(cylinder_container.get(), &state->cylinder_index);
	*/

	EffectCreator ef_creator;
	ef_creator.sphereWave();

	state->toPrepare = false;

}

void prepare(GameState *state) {
	EDK3::dev::GPUManager::CheckGLError("Prepare Start");
	
	state->set_Stage(1);

	// Nodes
	EDK3::Node* root = state->root.alloc();

	prepareStage1(state);


	/////////
	// Create a Camera

	state->camera.alloc();
	float pos[] = { -6.8f, 0.0f, 8.01f };
	float view[] = { 0.9f, 0.0f, -0.14f };
	float target[] = { -6.5f, 0.0f, 5.9f };
	state->camera->set_position(pos);
	state->camera->set_view_direction(view);
	state->camera->set_view_target(target);
	state->camera->setupPerspective(70, 1280.0f / 720.0f, 1.0f, 1500.0f);
	state->camera->set_clear_color(0.99f, 0.99f, 0.99f, 1.0f);
	//state->camera->set_prevTime(ESAT::RawTime());
	EDK3::dev::GPUManager::CheckGLError("Prepare END");


}

void update_stage1() {

	GameState& state = GameState::instance();

	// Sound data
	state.soloud.setVisualizationEnable(true);
	float* waveData = state.soloud.calcFFT();
	float meanDatas[32];

	for (int i = 0; i < kNumberCubes / 2; i++) {


		meanDatas[i] = (waveData[i * 4] + waveData[i * 4 + 1] + waveData[i * 4 + 2] +
			waveData[i * 4 + 3]) / 4.0f;
	}
	// Rotation
	float pos[] = { 0.2f * ESAT::Time() / 300.0f, 0.0f, 0.5f * ESAT::Time() / 300.0f };

	state.camera->move(1.0f);
	// Scale

	state.camera->autoPosition(1.0f, Vector3(0, 0, 0));

	// Scale Equalizer
	for (int i = 0; i < kNumberCubes / 2; i++) {
		float newScale;


		float meanData = (waveData[i * 4] + waveData[i * 4 + 1] + waveData[i * 4 + 2] +
			waveData[i * 4 + 3]) / 4.0f;
		if (meanData > 13.0f) {
			meanData = rand() % 3 + 10.0f;
		}

		newScale = 1.0f + meanData * 3.0f;

		float transitionForce = 0.1f;
		float scale = newScale * transitionForce + state.root->child(state.equalizer_index)->child(i)->scale()[1] * (1.0f - transitionForce);


		state.root->child(state.equalizer_index)->child(i)->set_scale(1, scale, 1);
		state.root->child(state.equalizer_index)->child(i + (kNumberCubes / 2))->set_scale(1, scale, 1);
	}

	// Color Background

	float blue = (waveData[2 * 4] + waveData[2 * 4 + 1] + waveData[2 * 4 + 2] +
		waveData[2 * 4 + 3]) / 4.0f;
	state.bg_color[2] = (40.0f * blue) / 30.0f;
	state.material_background_settings->set_color(state.bg_color[0], state.bg_color[1], state.bg_color[2], state.bg_color[3]);


	float scalarData = (waveData[2 * 4] + waveData[2 * 4 + 1] + waveData[2 * 4 + 2] +
		waveData[2 * 4 + 3]) / 4.0f;


	// Scale Spheres

	for (int i = 0; i < state.root->child(state.circleIndex_left)->num_children(); i++) {

		float newScale = 1.0f + scalarData * 0.05f;

		float transitionForce = 0.5f;
		float scaleX = newScale * transitionForce + state.root->child(state.circleIndex_left)->child(i)->scale()[0] * (1.0f - transitionForce);
		float scaleY = newScale * transitionForce + state.root->child(state.circleIndex_left)->child(i)->scale()[1] * (1.0f - transitionForce);
		float scaleZ = newScale * transitionForce + state.root->child(state.circleIndex_left)->child(i)->scale()[2] * (1.0f - transitionForce);
		state.root->child(state.circleIndex_left)->child(i)->set_scale(scaleX, scaleY, scaleZ);

	}

	for (int i = 0; i < state.root->child(state.circleIndex_right)->num_children(); i++) {

		float newScale = 1.0f + scalarData * 0.05f;

		float transitionForce = 0.5f;
		float scaleX = newScale * transitionForce + state.root->child(state.circleIndex_right)->child(i)->scale()[0] * (1.0f - transitionForce);
		float scaleY = newScale * transitionForce + state.root->child(state.circleIndex_right)->child(i)->scale()[1] * (1.0f - transitionForce);
		float scaleZ = newScale * transitionForce + state.root->child(state.circleIndex_right)->child(i)->scale()[2] * (1.0f - transitionForce);
		state.root->child(state.circleIndex_right)->child(i)->set_scale(scaleX, scaleY, scaleZ);

	}


	state.root->child(state.circleIndex_left)->set_rotation_y(5.0f * ESAT::Time() / 300.0f);
	state.root->child(state.circleIndex_right)->set_rotation_y(-1.0f * (5.0f * ESAT::Time() / 300.0f));


	float yellowAdd = (255.0f * scalarData) / 11.7f;
	state.material_circles_settings->set_color(yellowAdd, yellowAdd, state.circle_color[2], state.circle_color[3]);


	// Move stars

	state.root->child(state.stars_index)->set_rotation_z(3.0f * ESAT::Time() / 300.0f);


	Vector3 rotateCam = Vector3(0.0f, 0.0f, 0.0f);
	Vector3 moveCam = Vector3(0.0f, 0.0f, 0.0f);

	state.camera->autoMovement();

	state.root->set_rotation_xyz(0, 0, 0);

	//state.root->set_rotation_z(1.0f * 3.0f * ESAT::Time() / 300.0f);


	////////////////
	////// Move ring of cubes
	////////////////

	float faster_ = 1.0f;
	if (state.camera->timeCont() >= 51.0f) {
		faster_ = 2.0f;
	}
	float scalarRingData = (waveData[6 * 4] + waveData[6 * 4 + 1] + waveData[6 * 4 + 2] +
		waveData[6 * 4 + 3]) / 4.0f;

	if (state.ring_index != 0) {

		float n_pi = (2 * M_PI) / state.root->child(state.ring_index)->num_children();
		float current = 0;
		Vector3 center_point = Vector3(0.0f, 0.0f, -20.0f);
		float radius_ring = 7.0f;

		for (int i = 0; i < state.root->child(state.ring_index)->num_children(); i++) {

			state.root->child(state.ring_index)->child(i)->set_position(
				state.root->child(state.ring_index)->child(i)->position()[0],
				state.root->child(state.ring_index)->child(i)->position()[1],
				state.root->child(state.ring_index)->child(i)->position()[2]
			);


			float newScale;


			newScale = 1.0f + scalarRingData * 0.05f;

			float transitionForce = 0.2f;
			float scale = newScale * transitionForce + state.root->child(state.ring_index)->child(i)->scale()[1] * (1.0f - transitionForce);

			//state.root->child(state.ring_index)->child(i)->set_scale();

			// Scale ring
			
			

			if (scalarRingData >= 6.5f) {
				state.root->child(state.ring_index)->child(i)->set_scale(scale, scale, scale);
			}
			else {
				state.root->child(state.ring_index)->child(i)->set_scale(1.0f, 1.0f, 1.0f);
			}

			state.root->child(state.ring_index)->child(i)->set_rotation_x(6.0f * ESAT::Time() / 300.0f);
			/*state.root->child(state.ring_index)->child(i)->set_position(
				
				(cos(current + ESAT::Time() / 1000.0f) * radius_ring) + center_point.x,
				
				(sin(current + ESAT::Time() / 1000.0f)* radius_ring) + center_point.y,

				0.0f);*/

			current += n_pi;
		}
		state.root->child(state.ring_index)->set_rotation_z(9.0f * ESAT::Time() / 300 * faster_);
	}

	if (state.ring_index != 0 && state.root->child(state.ring_index + 1) != nullptr) {

		for (int i = 0; i < state.root->child(state.ring_index + 1)->num_children(); i++) {

			state.root->child(state.ring_index + 1)->child(i)->set_position(
				state.root->child(state.ring_index + 1)->child(i)->position()[0],
				state.root->child(state.ring_index + 1)->child(i)->position()[1],
				state.root->child(state.ring_index + 1)->child(i)->position()[2]
			);

			float newScale;

			newScale = 1.0f + scalarRingData * 0.05f;
			float transitionForce = 0.2f;
			float scale = newScale * transitionForce + state.root->child(state.ring_index + 1)->child(i)->scale()[1] * (1.0f - transitionForce);

			//state.root->child(state.ring_index + 1)->child(i)->set_scale();

			// Scale ring

			if (scalarRingData >= 6.5f) {
				state.root->child(state.ring_index + 1)->child(i)->set_scale(scale, scale, scale);
			}
			else {
				state.root->child(state.ring_index + 1)->child(i)->set_scale(1.0f, 1.0f, 1.0f);
			}

			state.root->child(state.ring_index + 1)->child(i)->set_rotation_x(-1.0f * 6.0f * ESAT::Time() / 300.0f);


		}
		state.root->child(state.ring_index + 1)->set_rotation_z(-1.0f * 9.0f * ESAT::Time() / 300 * faster_);
	}

	if (state.ring_index != 0 && state.root->child(state.ring_index + 2) != nullptr) {

		for (int i = 0; i < state.root->child(state.ring_index + 2)->num_children(); i++) {

			state.root->child(state.ring_index + 2)->child(i)->set_position(
				state.root->child(state.ring_index + 2)->child(i)->position()[0],
				state.root->child(state.ring_index + 2)->child(i)->position()[1],
				state.root->child(state.ring_index + 2)->child(i)->position()[2]
			);

			float newScale;

			newScale = 1.0f + scalarRingData * 0.05f;
			float transitionForce = 0.2f;
			float scale = newScale * transitionForce + state.root->child(state.ring_index + 2)->child(i)->scale()[1] * (1.0f - transitionForce);

			//state.root->child(state.ring_index + 1)->child(i)->set_scale();

			// Scale ring

			if (scalarRingData >= 6.5f) {
				state.root->child(state.ring_index + 2)->child(i)->set_scale(scale, scale, scale);
			}
			else {
				state.root->child(state.ring_index + 2)->child(i)->set_scale(1.0f, 1.0f, 1.0f);
			}

			state.root->child(state.ring_index + 2)->child(i)->set_rotation_x(6.0f * ESAT::Time() / 300.0f);

		}
		state.root->child(state.ring_index + 2)->set_rotation_z(9.0f * ESAT::Time() / 300 * faster_);
	}
}

float max = 0;
void update_stage2() {

	GameState& state = GameState::instance();


	state.camera->autoMovement();
	state.camera->move(1.0f);
	state.soloud.setVisualizationEnable(true);
	float* waveData = state.soloud.calcFFT();


	float meanData = (waveData[2 * 4] + waveData[2 * 4 + 1] + waveData[2 * 4 + 2] +
		waveData[2 * 4 + 3]) / 4.0f;

	meanData /= 40.0f;

	float scalarData = MathUtils::Clamp(meanData, 0.0f, 1.0f);
	
	if (scalarData < 0.45f) {
		scalarData = 0.0f;
	}
	else if (scalarData >= 0.45f) {
		scalarData = 1.0f;
	}

	if (state.dropIt) {

		float bar_four = (waveData[3 * 4] + waveData[3 * 4 + 1] + waveData[3 * 4 + 2] +
			waveData[3 * 4 + 3]) / 4.0f;

		if(max < bar_four)
			max = bar_four;

		bar_four /= 20.0f;
		float scalarData = MathUtils::Clamp(bar_four, 0.0f, 1.0f);
		if (scalarData < 0.5f) {
			scalarData = 0.0f;
		}
		else if (scalarData > 0.5f) {
			scalarData = 1.0f;
		}
		state.material_background_settings->set_color(scalarData, scalarData, scalarData, 0.0f);
	}
	else {
		state.material_background_settings->set_color(scalarData, scalarData, scalarData, 1.0f);

	}

	///////
	// Second equalizer
	///////

	meanData = (waveData[2 * 4] + waveData[2 * 4 + 1] + waveData[2 * 4 + 2] +
		waveData[2 * 4 + 3]) / 4.0f;

	meanData /= 40.0f;

	scalarData = MathUtils::Clamp(meanData, 0.0f, 1.0f);

	if (scalarData < 0.45f) {
		scalarData = 0.0f;
	}
	else if (scalarData >= 0.45f) {
		scalarData = 1.0f;
	}

	if (state.dropIt) {

		float bar_four = (waveData[3 * 4] + waveData[3 * 4 + 1] + waveData[3 * 4 + 2] +
			waveData[3 * 4 + 3]) / 4.0f;

		if (max < bar_four)
			max = bar_four;

		bar_four /= 20.0f;
		float scalarData = MathUtils::Clamp(bar_four, 0.0f, 1.0f);
		if (scalarData < 0.5f) {
			scalarData = 0.0f;
		}
		else if (scalarData > 0.5f) {
			scalarData = 1.0f;
		}
		state.material_circles_settings->set_color(scalarData, scalarData, scalarData, 0.0f);
	}
	else {
		state.material_circles_settings->set_color(scalarData, scalarData, scalarData, 1.0f);

	}




	state.material_circles_settings->set_color(scalarData, scalarData, scalarData);

	waveData = state.soloud.getWave();
	
	for (int j = 1; j <= 4; j++) {

		for (int i = 0; i < state.root->child(state.childBackground + j)->num_children() / 2; i++) {
			float newScale;



			float meanData = (waveData[i * 4] + waveData[i * 4 + 1] + waveData[i * 4 + 2] +
				waveData[i * 4 + 3]) / 4.0f;
			if (meanData > 13.0f) {
				meanData = rand() % 3 + 10.0f;
			}

			newScale = 1.0f + meanData * 3.0f;

			float transitionForce = 0.3f;
			float scale = newScale * transitionForce + state.root->child(state.childBackground + j)->child(i)->scale()[1] * (1.0f - transitionForce);


			state.root->child(state.childBackground + j)->child(i)->set_scale(1, scale, 1);
			state.root->child(state.childBackground + j)->child(i + (state.root->child(state.childBackground + j)->num_children() / 2))->set_scale(1, scale, 1);
		}
	}

	



	/*
	//state.root->child(state.cylinder_index)->set_rotation_x(-820.0f);

	for (int i = 0; i < state.root->child(state.cylinder_index)->num_children(); i++) {
		
		float meanData = (waveData[i * 4] + waveData[i * 4 + 1] + waveData[i * 4 + 2] +
			waveData[i * 4 + 3]) / 4.0f;

		float newScale = 1.0f + meanData * 0.2f;

		float transitionForce = 0.3f;
		float scale = newScale * transitionForce + state.root->child(state.cylinder_index)->child(i)->scale()[2] * (1.0f - transitionForce);

		state.root->child(state.cylinder_index)->child(i)->set_scale(
			state.root->child(state.cylinder_index)->child(i)->scale()[0],
			state.root->child(state.cylinder_index)->child(i)->scale()[1],
			scale
		);

		float scale_data = (waveData[2 * 4] + waveData[2 * 4 + 1] + waveData[2 * 4 + 2] +
			waveData[2 * 4 + 3]) / 4.0f;

		scale_data /= 50.0f;

		float scalarData = MathUtils::Clamp(scale_data, 0.0f, 1.0f);

		if (scalarData < 0.45f) {
			scalarData = 0.0f;
		}
		else if (scalarData >= 0.45f) {
			scalarData = 1.0f;
		}
		state.material_circles_settings->set_color(scalarData, scalarData, scalarData);
	}

	*/


	/*
	
	waveData = state.soloud.getWave();

	for (int i = 0; i < state.root->child(state.sphere_index)->num_children(); i++) {

		float meanData = waveData[i];

		float newScale = 1.0f + meanData * 0.2f;

		float transitionForce = 0.3f;
		float scale = newScale * transitionForce + state.root->child(state.sphere_index)->child(i)->scale()[0] * (1.0f - transitionForce);

		state.root->child(state.sphere_index)->child(i)->set_scale(
			scale, scale, scale
		);

		meanData = (waveData[2 * 4] + waveData[2 * 4 + 1] + waveData[2 * 4 + 2] +
			waveData[2 * 4 + 3]) / 4.0f;
		float scale_data = meanData / 50.0f;

		float scalarData = MathUtils::Clamp(scale_data, 0.0f, 1.0f);

		if (scalarData < 0.45f) {
			scalarData = 0.0f;
		}
		else if (scalarData >= 0.45f) {
			scalarData = 1.0f;
		}
		state.material_circles_settings->set_color(scalarData, scalarData, scalarData);

	}
	*/
}

void updateStage(GameState *state) {
	
	switch (state->currentStage()) {
		case 1:
				update_stage1();
			break;
		case 2:
			if (state->toPrepare) {
					
					prepareStage2(state);
					update_stage2();
			}
			else {
				update_stage2();
			}
			break;

	}
}

void update_function(GameState *state) {

	updateStage(state);
	

}

void render_function(GameState *state) {
	

	// For Every frame... determine what's visible:
	state->camera->doCull(state->root.get());

	// Render
	EDK3::dev::GPUManager::CheckGLError("begin Render-->");
	state->camera->doRender();
	EDK3::dev::GPUManager::CheckGLError("end Render-->");
}

int ESAT::main(int argc, char **argv) {
	
	// State
	GameState& state = GameState::instance();
	ESAT::WindowInit(1280, 720);
	ESAT::DrawSetTextFont("test.ttf");
	ESAT::DrawSetTextSize(18);
	ESAT::DrawSetFillColor(253, 255, 255, 128);

	prepare(&state);


	// Init soloud and play sound	
	SoLoud::Wav sample;

	state.soloud.init(SoLoud::Soloud::ENABLE_VISUALIZATION);
	sample.load("song.ogg");
	SoLoud::handle handle = state.soloud.play(sample);
	
	// Main loop
	while (ESAT::WindowIsOpened() && !ESAT::IsSpecialKeyDown(ESAT::kSpecialKey_Escape)) {
		state.camera->set_prevTime(clock());
		double currentTime = RawTime();
		double delta_time = (currentTime - previus_time) / 1000.0f;
		previus_time = currentTime;
		update_function(&state);
		render_function(&state);
		ESAT::WindowFrame();

		state.camera->set_timeCont(clock());
	}

	return 0;
}