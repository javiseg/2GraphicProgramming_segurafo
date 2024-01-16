#pragma once
#include <EDK3/node.h>
#include <EDK3/texture.h>
#include <EDK3/scoped_array.h>
#include <EDK3/geometry.h>

namespace JSF {
	class TrafficLight : public EDK3::Node
	{
	public:
		void GenerateTrafficLight(int type_of_object);

		EDK3::scoped_array<EDK3::ref_ptr<EDK3::Geometry>> geometries;
		EDK3::ref_ptr<EDK3::Texture> texture;
	};
}


