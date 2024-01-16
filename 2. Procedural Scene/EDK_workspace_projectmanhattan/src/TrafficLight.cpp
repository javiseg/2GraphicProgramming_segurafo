#include "TrafficLight.h"
#include <EDK3/texture.h>
#include <EDK3/drawable.h>
#include <EDK3/matdiffusetexture.h>


void JSF::TrafficLight::GenerateTrafficLight(int type_of_object)
{
	char* obj_src;
	if (type_of_object == 1) {
		obj_src = "../assets/Models/SM_TrafficL_00.obj";
	}
	else {
		obj_src = "../assets/Models/SM_TrafficL_01.obj";
	}

	char* texture_src;
	texture_src = "../assets/textures/T_LightsSigns_Dif.png";
	
	EDK3::scoped_array<char> errorLog;
	EDK3::Texture::Load(texture_src, &texture);
	texture->generateMipmaps();

	EDK3::LoadObj(obj_src, &geometries, &errorLog);
	

	//EDK3::ref_ptr<EDK3::MatDiffuseTexture> diffuse_material;
	//diffuse_material.alloc();
	//// Material Settings
	//EDK3::ref_ptr<EDK3::MatDiffuseTexture::Settings> diffuse_material_settings;
	//diffuse_material_settings.alloc();

	//
	//draw_traffic_light.alloc();

	//diffuse_material_settings->set_texture(texture.get());

	//draw_traffic_light->set_geometry(geometries[0].get());
	//draw_traffic_light->set_material(diffuse_material.get());
	//draw_traffic_light->set_material_settings(diffuse_material_settings.get());
	//draw_traffic_light->set_scale(1.0f, 1.0f, 1.0f);
	//draw_traffic_light->set_rotation_y(180.0f);

	//this->addChild(draw_traffic_light.get());

}
