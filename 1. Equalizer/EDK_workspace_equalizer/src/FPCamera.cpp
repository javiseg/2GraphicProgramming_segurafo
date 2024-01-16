#include "FPCamera.h"
#include "ESAT/input.h"
#include "math/vector_4.h"
#include "..\include\FPCamera.h"
#include <ESAT/time.h>
#include <time.h> 
#include "EffectCreator.h"
#include "GameState.h"

FPCamera::FPCamera() {
	speed = 0.1f;
	timeCont_ = 0.0f;

}
FPCamera::~FPCamera() {
}


void FPCamera::move(float deltaTime)
{
	if (ESAT::MouseButtonPressed(0)) {

		Vector3 camPosition = Vector3(position()[0], position()[1], position()[2]);
		Vector3 camTarget = Vector3(target()[0], target()[1], target()[2]);
		Vector3 goUp = Vector3(up_direction()[0], up_direction()[1], up_direction()[2]);
		Vector3 goRight = Vector3(-1.0f, 0.0f, 0.0f);

		Vector3 directionView = (camTarget - camPosition).Normalized();
		Vector3 directionStrafe = Vector3::CrossProduct(directionView, goUp).Normalized();

		Vector3 camcamFocusVector = (camPosition - camTarget);

		float moveFactor = 2;

		//Matrix3x3 

		if (ESAT::IsKeyPressed('D')) {

			camPosition -= directionStrafe * speed * deltaTime;
			//camTarget -= directionStrafe * speed * deltaTime;
		}

		if (ESAT::IsKeyPressed('A')) {

			camPosition += directionStrafe * speed * deltaTime;
			//camTarget += directionStrafe * speed * deltaTime;
		}
	
		if (ESAT::IsKeyPressed('S')) {

			camPosition -= directionView * speed * deltaTime;
			camTarget -= directionView * speed * deltaTime;
		}

		if (ESAT::IsKeyPressed('W')) {

			camPosition += directionView * speed * deltaTime;
			//camTarget += directionView * speed * deltaTime;
		}

		if (ESAT::IsKeyPressed('Q')) {

			camPosition += goUp * speed * deltaTime;
			//camTarget += goUp * speed * deltaTime;
		}

		if (ESAT::IsKeyPressed('E')) {

			camPosition -= goUp * speed * deltaTime;
			//camTarget -= goUp * speed * deltaTime;
		}

		float posix[3] = { camPosition.x, camPosition.y, camPosition.z };
		set_position(posix);
		float targeted[3] = { camTarget.x, camTarget.y, camTarget.z };
		set_view_target(targeted);



		Vector3 current_mouse = Vector3{
			(float)ESAT::MousePositionX(),
			(float)ESAT::MousePositionY(), 0.0f
		};

	}
}

void FPCamera::autoPosition(float deltaTime, Vector3 moveTo)
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

void FPCamera::autoRotate(Vector3 rotateTo, GameState* state)
{
	//state->root->set_rotation_z();
}

void FPCamera::autoMovement()
{
	GameState& state = GameState::instance();
	
	/*
	if (timeCont_ > 3.0f && state.toDestroy) {
		state.destroyStage();
	}
	else 	if (timeCont_ >= 45.0f) {
		state.dropIt = true;
	}*/
	
	if (timeCont_ >= 3.0f && timeCont_ < 18.0f) {
		autoPosition(0.3f, Vector3(0.0f, 0.0f, -1.0f));
		
	}
	else if (timeCont_ >= 18.0f && timeCont_ < 32.0f){
		autoPosition(0.20f, Vector3(0.0f, 0.0f, 1.0f));
	}
	else if (timeCont_ >= 37.0f && timeCont_ < 38.0f) {
		
		effect_creator.RingOfCubes(1);
		
	}
	else if (timeCont_ >= 38.0f && timeCont_ <= 39.0f) {
		effect_creator.set_ring_done(false);
	}
	else if(timeCont_ > 41.0f && timeCont_ <= 42.0f){
		effect_creator.RingOfCubes(2);
		//autoPosition(1.0f, Vector3(0.0f, 0.0f, 1.0f));
	}	else if(timeCont_ > 42.0f && timeCont_ <= 43.0f) {
		effect_creator.set_ring_done(false);
	}
	else if (timeCont_ > 44.5f && timeCont_ <= 45.0f) {
		effect_creator.RingOfCubes(3);
	}	else if (timeCont_ > 80 && timeCont_ <= 84) {
		effect_creator.MoveOutRings();
	}
	else if (timeCont_ > 84 && timeCont_ <= 85) {
		effect_creator.DestroyRings();
	}
	else if (timeCont_ > 85.0f && timeCont_ <= 88.0f) {
		Vector3 camPosition = Vector3(position()[0], position()[1], position()[2]);
		Vector3 goUp = Vector3(up_direction()[0], up_direction()[1], up_direction()[2]);
		Vector3 camTarget = Vector3(target()[0], target()[1], target()[2]);

		Vector3 directionView = (camTarget - camPosition).Normalized();
		Vector3 directionStrafe = Vector3::CrossProduct(directionView, goUp).Normalized();
		camPosition -= directionStrafe * speed * 0.067f;

		float posix[3] = { camPosition.x, camPosition.y, camPosition.z };
		set_position(posix);
	}
	else if (timeCont_ >= 89.0f && timeCont_ <= 98.0f) {
		autoPosition(0.8f, Vector3(0.0f, 0.0f, 1.0f));
	}
	else if (timeCont_ > 98.0f && state.toDestroy) {
		state.destroyStage();
	}	if (timeCont_ >= 158.0f) {
		state.dropIt = true;
		//state.material_background_settings->set_color(1.0f, 1.0f, 1.0f, 0.0f);
	}
}

void FPCamera::set_prevTime(float prevTime)
{
	prevTime_ = prevTime;
}

void FPCamera::set_timeCont(float timeCont)
{
	timeCont_ +=  (timeCont - prevTime_) / 1000.0f;
}

float FPCamera::timeCont()
{
	return timeCont_;
}
