#include "RoadGeometries.h"
#include <EDK3/ref_ptr.h>

JSF::RoadGeometries::RoadGeometries()
{
	char* obj_src[5];
	obj_src[0] = "../assets/Models/SM_Road_00.obj";
	obj_src[1] = "../assets/Models/SM_Road_01.obj";
	obj_src[2] = "../assets/Models/SM_Road_02.obj";
	obj_src[3] = "../assets/Models/SM_Road_03.obj";
	obj_src[4] = "../assets/Models/SM_Road_04.obj";

	char* texture_src;
	texture_src = "../assets/textures/T_Street_Diffuse.png";
	EDK3::scoped_array<char> errorLog;
	EDK3::Texture::Load(texture_src, &texture);
	texture->generateMipmaps();
	for (int i = 0; i < 5; i++) {

		EDK3::LoadObj(obj_src[i], &geometries[i], &errorLog);
	}
}
