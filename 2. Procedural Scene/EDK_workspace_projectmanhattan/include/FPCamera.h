#pragma once
#include "EDK3/Camera.h"
#include "math/vector_3.h"
#include "math/matrix_4.h"
#include "EDK3/material.h"
#include "EDK3/geometry.h"
#include "EDK3/node.h"

class GameState;
using namespace EDK3;
struct RenderData {
	Matix4x4 model;
	const EDK3::Geometry* geometry;
	const EDK3::Material* material;
	const EDK3::MaterialSettings* mat_setting;
};

namespace JSF {
	
	class FPCamera : public::EDK3::Camera
	{
	public:
		FPCamera();
		~FPCamera();
		void move(float deltaTime);
		void RotateCamera(float dt, float speed);
		void autoPosition(float deltaTime, Vector3 moveTo);
		void autoRotate(Vector3 rotateTo, GameState* state);
		void set_prevTime(float prevTime);
		void set_timeCont(float timeCont);

		virtual void doCull(const EDK3::Node* root_node) override;

		virtual void doRender() const override;

		void Cull(const EDK3::Node* node, Matix4x4 matrix);

		float timeCont();


	private:
		bool isAutoRotate;
		bool isAutoMove;
		float speed;

		float prevTime_;
		float timeCont_;
	protected:
		std::vector<RenderData> rend_data;

	};

}

