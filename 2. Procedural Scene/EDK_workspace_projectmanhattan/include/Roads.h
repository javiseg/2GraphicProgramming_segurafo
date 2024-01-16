#pragma once
#include "RoadGeometries.h"
#include <EDK3/node.h>

namespace JSF {
	class Roads : public EDK3::Node
	{
	public:
		void GenerateRoads(EDK3::ref_ptr<RoadGeometries> road_geometries);








	};

}


