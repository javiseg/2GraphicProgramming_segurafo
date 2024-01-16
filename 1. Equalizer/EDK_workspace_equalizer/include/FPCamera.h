#pragma once
#include "EDK3/Camera.h"
#include "math/vector_3.h"
#include "EffectCreator.h"
class GameState;

class FPCamera : public::EDK3::Camera 
{
public:
	FPCamera();
	~FPCamera();
	void move(float deltaTime);
	void autoPosition(float deltaTime, Vector3 moveTo);
	void autoRotate(Vector3 rotateTo, GameState* state);
	void autoMovement();
	void set_prevTime(float prevTime);
	void set_timeCont(float timeCont);
	float timeCont();

	EffectCreator effect_creator;

private:
	bool isAutoRotate;
	bool isAutoMove;
	float speed;
	
	float prevTime_;
	float timeCont_;

};

