#include "BuildingGeometries.h"
#include <EDK3/geometry.h>
#include "JSFTexture.h"

JSF::BuildingGeometries::BuildingGeometries() {


	char* obj_src[6];
	obj_src[0] = "../assets/Models/SM_Building_00.obj";
	obj_src[1] = "../assets/Models/SM_Building_01.obj";
	obj_src[2] = "../assets/Models/SM_Building_02.obj";
	obj_src[3] = "../assets/Models/SM_Building_03.obj";
	obj_src[4] = "../assets/Models/SM_Building_04.obj";
	obj_src[5] = "../assets/Models/SM_Building_05.obj";

	char* texture_src[6];
	texture_src[0] = "../assets/textures/T_building_01_Dif.png";
	texture_src[1] = "../assets/textures/T_building_01_Dif_b.png";
	texture_src[2] = "../assets/textures/T_building_01_Dif_C.png";
	texture_src[3] = "../assets/textures/T_building_03_Dif.png";
	texture_src[4] = "../assets/textures/T_building_03_Dif_B.png";
	texture_src[5] = "../assets/textures/T_building_03_Dif_C.png";
	EDK3::scoped_array<char> errorLog;

	for (int i = 0; i < 6; i++) {
		//texture[i].alloc();
		JSF::JSFTexture::Load(texture_src[i], &texture[i]);
		texture[i]->generateMipmaps();
		EDK3::LoadObj(obj_src[i], &geometries[i], &errorLog);
	}
	

	

}