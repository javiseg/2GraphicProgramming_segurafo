#include "EffectCreator.h"
#include "GameState.h"
#include "PlaneBackground.h"
#include <EDK3/drawable.h>
#include "JCircle.h"

EffectCreator::EffectCreator()
{
	num_cubes_ = 24.0f;
	ring_done_ = false;
}

EffectCreator::~EffectCreator()
{
}

void EffectCreator::RingOfCubes(int ring)
{
	if (!ring_done_) {
		GameState& state = GameState::instance();
		EDK3::ref_ptr<EDK3::Node> cube_ring_center;
		EDK3::ref_ptr<PlaneBackground> sphere_geometry;
		EDK3::ref_ptr<MatCustomJSF> material_cubes;
		EDK3::ref_ptr<MatCustomJSF::Settings> material_cubes_settings;

		switch (ring) {
			
			case 1:
				
				num_cubes_ = 24.0f;

				cube_ring_center.alloc();
				cube_ring_center->set_position(0.0f, 0.0f, -20.0f);
				cube_ring_center->set_scale(1.0f, 1.0f, 1.0f);
				
				sphere_geometry.alloc();
				sphere_geometry->init();

				material_cubes.alloc();

				material_cubes_settings.alloc();
				material_cubes_settings->set_color(255.0f, 255.0f, 255.0f, 1.0f);
				material_cubes->load_shaders_from_filepaths("./shaders/blurcube.vert", "./shaders/blurcube.frag");

				for (int i = 0; i < num_cubes_; i++) {
					EDK3::ref_ptr < EDK3::Drawable> drawCubes;
					drawCubes.alloc();
					drawCubes->set_geometry(sphere_geometry.get());
					drawCubes->set_material(material_cubes.get());
					drawCubes->set_material_settings(material_cubes_settings.get());
					drawCubes->set_scale(1.0f, 1.0f, 1.0f);
					drawCubes->set_position(sin(i) * 6.0f, cos(i) * 6.0f, 0.0f);
					cube_ring_center->addChild(drawCubes.get());
				}

				state.root->addChild(cube_ring_center.get());

				state.root->childIndex(cube_ring_center.get(), &state.ring_index);

				ring_done_ = true;

				break;

			case 2:

				num_cubes_ = 44.0f;

				cube_ring_center.alloc();
				cube_ring_center->set_position(0.0f, 0.0f, -20.0f);
				cube_ring_center->set_scale(1.0f, 1.0f, 1.0f);

				sphere_geometry.alloc();
				sphere_geometry->init();

				material_cubes.alloc();

				material_cubes_settings.alloc();
				material_cubes_settings->set_color(255.0f, 255.0f, 255.0f, 1.0f);
				material_cubes->load_shaders_from_filepaths("./shaders/blurcube.vert", "./shaders/blurcube.frag");


				for (int i = 0; i < num_cubes_; i++) {
					EDK3::ref_ptr < EDK3::Drawable> drawCubes;
					drawCubes.alloc();
					drawCubes->set_geometry(sphere_geometry.get());
					drawCubes->set_material(material_cubes.get());
					drawCubes->set_material_settings(material_cubes_settings.get());
					drawCubes->set_scale(1.0f, 1.0f, 1.0f);
					drawCubes->set_position(sin(i) * 16.0f, cos(i) * 16.0f, 0.0f);
					cube_ring_center->addChild(drawCubes.get());
				}

				state.root->addChild(cube_ring_center.get());


				ring_done_ = true;

				break;

			case 3:

				num_cubes_ = 64.0f;

				cube_ring_center.alloc();
				cube_ring_center->set_position(0.0f, 0.0f, -20.0f);
				cube_ring_center->set_scale(1.0f, 1.0f, 1.0f);

				sphere_geometry.alloc();
				sphere_geometry->init();

				material_cubes.alloc();

				material_cubes_settings.alloc();
				material_cubes_settings->set_color(255.0f, 255.0f, 255.0f, 1.0f);
				material_cubes->load_shaders_from_filepaths("./shaders/blurcube.vert", "./shaders/blurcube.frag");


				for (int i = 0; i < num_cubes_; i++) {
					EDK3::ref_ptr < EDK3::Drawable> drawCubes;
					drawCubes.alloc();
					drawCubes->set_geometry(sphere_geometry.get());
					drawCubes->set_material(material_cubes.get());
					drawCubes->set_material_settings(material_cubes_settings.get());
					drawCubes->set_scale(1.0f, 1.0f, 1.0f);
					drawCubes->set_position(sin(i) * 24.0f, cos(i) * 24.0f, 0.0f);
					cube_ring_center->addChild(drawCubes.get());
				}

				state.root->addChild(cube_ring_center.get());


				ring_done_ = true;

				break;
		}

		
	}
}

void EffectCreator::set_ring_done(bool srd)
{
	ring_done_ = srd;
}

bool EffectCreator::isRingDone()
{
	return ring_done_;
}

int EffectCreator::numberCubes()
{
	return num_cubes_;
}

void EffectCreator::MoveOutRings()
{

	GameState& state = GameState::instance();


	for (int i = state.ring_index; i <= state.ring_index + 2; i++) {

		for (int j = 0; j < state.root->child(i)->num_children(); j++) {

			state.root->child(i)->child(j)->set_position(
				state.root->child(i)->child(j)->position()[0] + (cos(j) * 0.35 ),
				state.root->child(i)->child(j)->position()[1] + (sin(j) * 0.35),
				state.root->child(i)->child(j)->position()[2]);

		}
	}


}

void EffectCreator::DestroyRings()
{
	GameState& state = GameState::instance();

	if (state.ring_index != 0) {
		for (int i = state.ring_index + 2; i >= state.ring_index; i--) {

			state.root->removeChildByIndex(i);

		}

		state.ring_index = 0;
	}


}

void EffectCreator::sphereWave()
{
	
	GameState& state = GameState::instance();
	/*
	EDK3::ref_ptr<EDK3::Node> sphere_center;
	EDK3::ref_ptr<JSF::JCircle> sphere_geometry;
	EDK3::ref_ptr<EDK3::Drawable> draw_spheres[104];
	EDK3::ref_ptr<MatCustomJSF> material_sphere;
	EDK3::ref_ptr<MatCustomJSF::Settings> material_sphere_settings;

	sphere_center.alloc();
	sphere_geometry.alloc();
	material_sphere.alloc();
	material_sphere_settings.alloc();

	sphere_geometry.alloc();
	sphere_geometry->buildVertices(0.5f, 64, 24);
	sphere_geometry->init();

	sphere_center->set_position(-25.0f, -5.5f, -15.0f);
	sphere_center->set_scale(1.0f, 1.0f, 1.0f);

	material_sphere->load_shaders_from_filepaths("./shaders/cylinder.vert", "./shaders/cylinder.frag");

	state.material_circles_settings.alloc();
	

	state.material_circles_settings->set_color(0.0f, 255.0f / 255.0f, 0.0f, 1.0f);

	for (int i = 0; i < num_spheres_ / 13; i++) {

		for (int j = 0; j < num_spheres_ / 8; j++) {
			draw_spheres[i * (num_spheres_ / 8) + j].alloc();
			draw_spheres[i * (num_spheres_ / 8) + j]->set_geometry(sphere_geometry.get());
			draw_spheres[i * (num_spheres_ / 8) + j]->set_material(material_sphere.get());
			draw_spheres[i * (num_spheres_ / 8) + j]->set_material_settings(state.material_circles_settings.get());
			draw_spheres[i * (num_spheres_ / 8) + j]->set_position(
				4.0f * j, 2.0f * i, 0.0f);
			draw_spheres[i * (num_spheres_ / 8) + j]->set_scale(3.0f, 3.0f, 3.0f);
			sphere_center->addChild(draw_spheres[i * (num_spheres_ / 8) + j].get());


		}

	}

	state.root->addChild(sphere_center.get());
	state.root->childIndex(sphere_center.get(), &state.sphere_index);

	*/
	const int kNumberCubes = 64;
	EDK3::ref_ptr<EDK3::Node> equalizer_node;
	equalizer_node.alloc();
	equalizer_node->set_position(0.0f, -2.3f, 0.0f);
	equalizer_node->set_scale(1.0f, 1.0f, 1.0f);

	// Create sphere
	EDK3::ref_ptr<JSF::JCircle> sphere_geometry;
	sphere_geometry.alloc();
	sphere_geometry->buildVertices(0.5f, 64, 24);
	sphere_geometry->init();

	// Create cube
	EDK3::ref_ptr<EDK3::Geometry> cube_geometry;
	EDK3::CreateCube(&cube_geometry, 1.0f, true, false);

	// Material
	EDK3::ref_ptr<MatCustomJSF> sphere_material;
	EDK3::ref_ptr<MatCustomJSF::Settings> sphere_material_settings;
	EDK3::ref_ptr<MatCustomJSF::Settings> diffuse_material_settings_bottom_cube;
	
	state.material_circles_settings.alloc();
	state.material_circles_settings->set_color(0.0f, 255.0f / 255.0f, 0.0f, 1.0f);


	sphere_material.alloc();
	sphere_material_settings.alloc();
	diffuse_material_settings_bottom_cube.alloc();


	// Create a Drawable Node (Geometry + Material + Settings)
	EDK3::ref_ptr<EDK3::Drawable> drawable[kNumberCubes];

	// Create nodes for transform
	EDK3::ref_ptr<EDK3::Node> transformNodes[kNumberCubes];

	// Color 
	float blue_color[] = { 0.0f, 255.0f / 255.0f, 0.0f, 1.0f };
	sphere_material->load_shaders_from_filepaths("./shaders/ecuacube_stage2.vert", "./shaders/ecuacube_stage2.frag");
	sphere_material_settings->set_color(blue_color);
	float blue_color_lowalpha[] = { 0.0f , 100.0f, 255.0f, 0.5f };
	diffuse_material_settings_bottom_cube->set_color(blue_color_lowalpha);
	// Graphic

	// Bottom

	float scale[3] = { 1.0f, 1.0f, 1.0f };
	float pos[3] = { -1.0f, 0.25f, 0.0f };
	for (int i = 0; i < kNumberCubes / 2; i++) {
		drawable[i].alloc();
		JSF::CreateSphere(&drawable[i], &sphere_geometry, &sphere_material, &state.material_circles_settings, scale, pos);
		transformNodes[i].alloc();
		transformNodes[i]->set_position(i * 0.7f - (kNumberCubes / 2.0f / 2.0f) * 0.7f, -7.0f, -15.0f);
		transformNodes[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes[i]->addChild(drawable[i].get());

		equalizer_node->addChild(transformNodes[i].get());
	}

	for (int i = kNumberCubes / 2; i < kNumberCubes; i++) {
		drawable[i].alloc();
		drawable[i]->set_geometry(cube_geometry.get());
		drawable[i]->set_material(sphere_material.get());
		drawable[i]->set_material_settings(state.material_circles_settings.get());
		drawable[i]->set_scale(0.5f, 0.5f, 0.5f);
		drawable[i]->set_position(-1.0f, -0.25f, 0.0f);
		transformNodes[i].alloc();
		transformNodes[i]->set_position(((i - kNumberCubes / 2.0f) * 0.7f - (kNumberCubes / 2.0f / 2.0f) * 0.7f), -7.0f - 0.3f, -15.0f);
		transformNodes[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes[i]->addChild(drawable[i].get());
		equalizer_node->addChild(transformNodes[i].get());
	}

	// Top

	EDK3::ref_ptr<EDK3::Node> equalizer_nodeTop;
	equalizer_nodeTop.alloc();
	equalizer_nodeTop->set_rotation_z(180.0f);
	equalizer_nodeTop->set_position(-2.0f, 2.2f, 0.0f);
	equalizer_nodeTop->set_scale(1.0f, 1.0f, 1.0f);

	// Create a Drawable Node (Geometry + Material + Settings)
	EDK3::ref_ptr<EDK3::Drawable> drawable_top[kNumberCubes];

	// Create nodes for transform
	EDK3::ref_ptr<EDK3::Node> transformNodes_top[kNumberCubes];

	for (int i = 0; i < kNumberCubes / 2; i++) {
		drawable_top[i].alloc();
		JSF::CreateSphere(&drawable_top[i], &sphere_geometry, &sphere_material, &state.material_circles_settings, scale, pos);
		transformNodes_top[i].alloc();
		transformNodes_top[i]->set_position(i * 0.7f - (kNumberCubes / 2.0f / 2.0f) * 0.7f, -7.0f, -15.0f);
		transformNodes_top[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes_top[i]->addChild(drawable_top[i].get());

		equalizer_nodeTop->addChild(transformNodes_top[i].get());
	}

	for (int i = kNumberCubes / 2; i < kNumberCubes; i++) {
		drawable_top[i].alloc();
		drawable_top[i]->set_geometry(cube_geometry.get());
		drawable_top[i]->set_material(sphere_material.get());
		drawable_top[i]->set_material_settings(state.material_circles_settings.get());
		drawable_top[i]->set_scale(0.5f, 0.5f, 0.5f);
		drawable_top[i]->set_position(-1.0f, -0.25f, 0.0f);
		transformNodes_top[i].alloc();
		transformNodes_top[i]->set_position(((i - kNumberCubes / 2.0f) * 0.7f - (kNumberCubes / 2.0f / 2.0f) * 0.7f), -7.0f - 0.3f, -15.0f);
		transformNodes_top[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes_top[i]->addChild(drawable_top[i].get());
		equalizer_nodeTop->addChild(transformNodes_top[i].get());
	}


	// Left
	EDK3::ref_ptr<EDK3::Node> equalizer_nodeLeft;
	const int kNumberCubes_sides = 56;
	equalizer_nodeLeft.alloc();
	equalizer_nodeLeft->set_rotation_z(-90.0f);
	equalizer_nodeLeft->set_position(-10.0f, -1.5f, 0.0f);
	equalizer_nodeLeft->set_scale(1.0f, 1.0f, 1.0f);
	
	// Create a Drawable Node (Geometry + Material + Settings)
	EDK3::ref_ptr<EDK3::Drawable> drawable_left[kNumberCubes_sides];

	// Create nodes for transform
	EDK3::ref_ptr<EDK3::Node> transformNodes_left[kNumberCubes_sides];

	for (int i = 0; i < kNumberCubes_sides / 2; i++) {
		drawable_left[i].alloc();
		JSF::CreateSphere(&drawable_left[i], &sphere_geometry, &sphere_material, &state.material_circles_settings, scale, pos);
		transformNodes_left[i].alloc();
		transformNodes_left[i]->set_position(i * 0.7f - (kNumberCubes_sides / 2.0f / 2.0f) * 0.7f, -7.0f, -15.0f);
		transformNodes_left[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes_left[i]->addChild(drawable_left[i].get());

		equalizer_nodeLeft->addChild(transformNodes_left[i].get());
	}

	for (int i = kNumberCubes_sides / 2; i < kNumberCubes_sides; i++) {
		drawable_left[i].alloc();
		drawable_left[i]->set_geometry(cube_geometry.get());
		drawable_left[i]->set_material(sphere_material.get());
		drawable_left[i]->set_material_settings(state.material_circles_settings.get());
		drawable_left[i]->set_scale(0.5f, 0.5f, 0.5f);
		drawable_left[i]->set_position(-1.0f, -0.25f, 0.0f);
		transformNodes_left[i].alloc();
		transformNodes_left[i]->set_position(((i - kNumberCubes_sides / 2.0f) * 0.7f - (kNumberCubes_sides / 2.0f / 2.0f) * 0.7f), -7.0f - 0.3f, -15.0f);
		transformNodes_left[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes_left[i]->addChild(drawable_left[i].get());
		equalizer_nodeLeft->addChild(transformNodes_left[i].get());
	}

	// Right

	EDK3::ref_ptr<EDK3::Node> equalizer_nodeRight;
	equalizer_nodeRight.alloc();
	equalizer_nodeRight->set_rotation_z(90.0f);
	equalizer_nodeRight->set_position(10.0f, 1.2f, 0.0f);
	equalizer_nodeRight->set_scale(1.0f, 1.0f, 1.0f);

	// Create a Drawable Node (Geometry + Material + Settings)
	EDK3::ref_ptr<EDK3::Drawable> drawable_right[kNumberCubes_sides];

	// Create nodes for transform
	EDK3::ref_ptr<EDK3::Node> transformNodes_right[kNumberCubes_sides];

	for (int i = 0; i < kNumberCubes_sides / 2; i++) {
		drawable_right[i].alloc();
		JSF::CreateSphere(&drawable_right[i], &sphere_geometry, &sphere_material, &state.material_circles_settings, scale, pos);
		transformNodes_right[i].alloc();
		transformNodes_right[i]->set_position(i * 0.7f - (kNumberCubes_sides / 2.0f / 2.0f) * 0.7f, -7.0f, -15.0f);
		transformNodes_right[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes_right[i]->addChild(drawable_right[i].get());

		equalizer_nodeRight->addChild(transformNodes_right[i].get());
	}

	for (int i = kNumberCubes_sides / 2; i < kNumberCubes_sides; i++) {
		drawable_right[i].alloc();
		drawable_right[i]->set_geometry(cube_geometry.get());
		drawable_right[i]->set_material(sphere_material.get());
		drawable_right[i]->set_material_settings(state.material_circles_settings.get());
		drawable_right[i]->set_scale(0.5f, 0.5f, 0.5f);
		drawable_right[i]->set_position(-1.0f, -0.25f, 0.0f);
		transformNodes_right[i].alloc();
		transformNodes_right[i]->set_position(((i - kNumberCubes_sides / 2.0f) * 0.7f - (kNumberCubes_sides / 2.0f / 2.0f) * 0.7f), -7.0f - 0.3f, -15.0f);
		transformNodes_right[i]->set_scale(1.0f, 1.0f, 1.0f);
		transformNodes_right[i]->addChild(drawable_right[i].get());
		equalizer_nodeRight->addChild(transformNodes_right[i].get());
	}



	state.root->addChild(equalizer_node.get());
	state.root->addChild(equalizer_nodeLeft.get());
	state.root->addChild(equalizer_nodeTop.get());
	state.root->addChild(equalizer_nodeRight.get());
	state.root->childIndex(equalizer_node.get(), &state.equalizer_index);



}
