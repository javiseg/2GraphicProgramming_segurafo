#pragma once
#include <EDK3/node.h>
#include "EDK3/geometry.h"
#include <EDK3/texture.h>

namespace JSF {
	class BuildingGeometries : public EDK3::Node
	{
	public:
		BuildingGeometries();

		EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> geometries[6];
		EDK3::ref_ptr<EDK3::Texture> texture[6];
	};
}


