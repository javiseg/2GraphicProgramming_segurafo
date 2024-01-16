#include "FPCamera.h"
#include "ESAT/input.h"
#include "math/matrix_4.h"
#include "EDK3/drawable.h"
#include "..\include\math\vector_4.h"
#include "..\include\FPCamera.h"
#include <ESAT/time.h>
#include <time.h>

JSF::FPCamera::FPCamera() {
	speed = 5.0f;
	timeCont_ = 0.0f;

}
JSF::FPCamera::~FPCamera() {
}


void JSF::FPCamera::move(float deltaTime)
{
	
	Vector3 camPosition = Vector3(position());
	Vector3 camTarget = Vector3(target());
	Vector3 goUp = Vector3(up_direction());
		//Vector3 goRight = Vector3(-1.0f, 0.0f, 0.0f);

	Vector3 directionView = (camPosition - camTarget).Normalized();
	Vector3 directionStrafe = Vector3::CrossProduct(goUp, directionView).Normalized();

	Vector3 camcamFocusVector = (camPosition - camTarget);

	float moveFactor = 2;

		//Matrix3x3 

	if (ESAT::IsKeyPressed('W')) {

		camPosition -= directionView * speed * deltaTime;
		camTarget -= directionView * speed * deltaTime;
	}

	if (ESAT::IsKeyPressed('S')) {

		camPosition += directionView * speed * deltaTime;
		camTarget += directionView * speed * deltaTime;
	}
	
	if (ESAT::IsKeyPressed('D')) {

		camPosition += directionStrafe * speed * deltaTime;
		camTarget += directionStrafe * speed * deltaTime;
	}

	if (ESAT::IsKeyPressed('A')) {

		camPosition -= directionStrafe * speed * deltaTime;
		camTarget -= directionStrafe * speed * deltaTime;
	}

	if (ESAT::IsKeyPressed('Q')) {
		
		camPosition -= goUp * speed * deltaTime;
		camTarget -= goUp * speed * deltaTime;
	}

	if (ESAT::IsKeyPressed('E')) {

		camPosition += goUp * speed * deltaTime;
		camTarget += goUp * speed * deltaTime;
	}

	float posix[3] = { camPosition.x, camPosition.y, camPosition.z };

	float targeted[3] = { camTarget.x, camTarget.y, camTarget.z };
	set_position(posix);
	set_view_target(targeted);
	
}

void JSF::FPCamera::RotateCamera(float dt, float speed)
{
	Vector3 position_ = Vector3(position());
	Vector3 target_ = Vector3(target());
	Vector3 up_direction_ = Vector3(up_direction());

	Vector3 view_direction = (position_ - target_).Normalized();
	Vector3 strafe_direction = Vector3::CrossProduct(up_direction(), view_direction).Normalized();

	if (ESAT::IsKeyPressed('A') || !ESAT::MouseButtonPressed(0)) {
		position_ += strafe_direction * speed * dt;
	}

	if (ESAT::IsKeyPressed('D') || !ESAT::MouseButtonPressed(0)) {
		position_ -= strafe_direction * speed * dt;
	}

	if (ESAT::IsKeyPressed('W') || !ESAT::MouseButtonPressed(0)) {
		position_ -= up_direction_ * speed * dt;
	}
	if (ESAT::IsKeyPressed('S') || !ESAT::MouseButtonPressed(0)) {
		position_ += up_direction_ * speed * dt;
	}

	float pos[3] = { position_.x, position_.y, position_.z };
	set_position(pos);
}


void JSF::FPCamera::autoPosition(float deltaTime, Vector3 moveTo)
{
	/////////////////////////////////////////////
	//GameState& state = GameState::instance();




	Vector3 camPosition = Vector3(position()[0], position()[1], position()[2]);
	Vector3 camTarget = Vector3(target()[0], target()[1], target()[2]);
	Vector3 goUp = Vector3(up_direction()[0], up_direction()[1], up_direction()[2]);
	Vector3 goRight = Vector3(-1.0f, 0.0f, 0.0f);

	Vector3 directionView = (camTarget - camPosition).Normalized();
	Vector3 directionStrafe = Vector3::CrossProduct(directionView, goUp).Normalized();

	Vector3 camcamFocusVector = (camPosition - camTarget);

	if (moveTo.x < 0 || moveTo.y < 0 || moveTo.z < 0) {
		camPosition -= directionView * speed * deltaTime;
		camTarget -= directionView * speed * deltaTime;
	}
	else if (moveTo.x > 0 || moveTo.y > 0 || moveTo.z > 0) {
		camPosition += directionView * speed * deltaTime;
		camTarget += directionView * speed * deltaTime;
	}
	
	

	float posix[3] = { camPosition.x, camPosition.y, camPosition.z };
	set_position(posix);
	float targeted[3] = { camTarget.x, camTarget.y, camTarget.z };
	set_view_target(targeted);
	////////////////////////////////////////////////////////////////////

}

void JSF::FPCamera::autoRotate(Vector3 rotateTo, GameState* state)
{
	//state->root->set_rotation_z();
}

void JSF::FPCamera::set_prevTime(float prevTime)
{
	prevTime_ = prevTime;
}

void JSF::FPCamera::set_timeCont(float timeCont)
{
	timeCont_ +=  (timeCont - prevTime_) / 1000.0f;
}

void JSF::FPCamera::doCull(const EDK3::Node* root_node)
{
	rend_data.clear();
	Matix4x4 mI;

	Cull(root_node, mI.Identity());
}

void JSF::FPCamera::doRender() const
{
	for (int i = 0; i < rend_data.size(); i++)
	{
		rend_data[i].material->enable(rend_data[i].mat_setting);

		rend_data[i].material->setupModel(rend_data[i].model.m);

		rend_data[i].material->setupCamera(projection_matrix(), view_matrix());

		rend_data[i].geometry->bindAttributesAndRenderWithCurrentMaterial(rend_data[i].material);
	}
}

void JSF::FPCamera::Cull(const EDK3::Node* node, Matix4x4 matrix)
{
	Matix4x4 multiplied_matrix = Matix4x4(node->local_transform()).Multiply(matrix);


	if (node->num_children() > 0) {

		for (int i = 0; i < node->num_children(); i++) {

			Cull(node->child(i), multiplied_matrix);

		}
	}

	const EDK3::Drawable* drawable = dynamic_cast<const EDK3::Drawable*>(node);

	if (drawable != nullptr && drawable->visible()) {
		RenderData rend_data_aux;
		rend_data_aux.model = multiplied_matrix;
		rend_data_aux.geometry = drawable->geometry();
		rend_data_aux.material = drawable->material();
		rend_data_aux.mat_setting = drawable->material_settings();

		rend_data.push_back(rend_data_aux);
	}
}

float JSF::FPCamera::timeCont()
{
	return timeCont_;
}
