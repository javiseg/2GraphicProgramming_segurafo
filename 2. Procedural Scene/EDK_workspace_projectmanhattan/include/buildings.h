#pragma once
#include <EDK3/drawable.h>
#include <EDK3/node.h>
#include "math/vector_3.h"
#include "BuildingGeometries.h"

namespace JSF {


	class Building : public EDK3::Node {


	public:

		int CreateBuilding(EDK3::ref_ptr<JSF::BuildingGeometries> building_geo_text, int center_prox);
		void SetScale(float x, float y, float z);
		void SetPosition(float x, float y, float z);
		Vector3 GetPosition();

		EDK3::Node* getDrawable();


	private:

		EDK3::ref_ptr<EDK3::Drawable> drawable;


	};

}