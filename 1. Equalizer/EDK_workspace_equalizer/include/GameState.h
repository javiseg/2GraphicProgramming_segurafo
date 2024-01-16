#pragma once
#include "FPCamera.h"
#include "matcustom_jsf.h"
#include <ESAT_extra/soloud/soloud.h>
#include <ESAT_extra/soloud/soloud_wav.h>
#include <EDK3/ref_ptr.h>
#include <EDK3/node.h>
#include "EffectCreator.h"

class GameState : public EDK3::Node {
public:


		static GameState& instance();
		~GameState();

		void set_Stage(unsigned int st);
		unsigned int currentStage();
		void destroyStage();

		
		EDK3::ref_ptr<FPCamera> camera;
		EDK3::ref_ptr<EDK3::Node> root;
		SoLoud::Soloud soloud;

		unsigned int equalizer_index;

		float bg_color[4];
		EDK3::ref_ptr<MatCustomJSF::Settings> material_background_settings;
		
		float cube_color[4];
		
		unsigned int childBackground;
		unsigned int circleIndex_left;
		unsigned int circleIndex_right;
		EDK3::ref_ptr<MatCustomJSF::Settings> material_circles_settings;
		float circle_color[4];
		unsigned int stars_index;

		unsigned int ring_index;
		unsigned int sphere_index;

		bool toPrepare = true;
		bool toDestroy = true;

		bool dropIt = false;

private:
	GameState();

	unsigned int stages_;
	static GameState* instance_;

};
