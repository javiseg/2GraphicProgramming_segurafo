#include "buildings.h"
#include "EDK3/geometry.h"
#include "EDK3/texture.h"
#include "matcustom_jsf.h"
#include "EDK3/matdiffusetexture.h"
#include <time.h> 



int JSF::Building::CreateBuilding(EDK3::ref_ptr<JSF::BuildingGeometries> building_geo_text, int center_prox) {
		
		drawable.alloc();
		
		// Material
		EDK3::ref_ptr<MatCustomJSF> diffuse_material;
		diffuse_material.alloc();
		char* vert_shader = "../assets/shaders/shader_building.vert";
		char* frag_shader = "../assets/shaders/shader_building.frag";

		diffuse_material->load_shaders_from_filepaths(vert_shader, frag_shader);
		//diffuse_material->enable();
		EDK3::ref_ptr<MatCustomJSF::Settings> diffuse_material_settings;
		diffuse_material_settings.alloc();

		//diffuse_material_settings->set_texture(building_geo_text->texture->get());
		

		
		int random = rand() % 6;
		if (center_prox > 0) {
			if (random != 3 && random != 4) {
				random = rand() % 6;
			}
			if (center_prox > 1) {
				if (random != 3 && random != 4) {
					random = rand() % 6;
				}
				if (center_prox > 2) {
					if (random != 3 && random != 4) {
						random = rand() % 6;
					}
					if (center_prox > 3) {
						if (random != 3 && random != 4) {
							random = rand() % 6;
						}

					}
				}
			}
			
			
		}
		


		/*diffuse_material_settings->set_texture(building_geo_text->texture[random].get());
		diffuse_material_settings->texture()->bind(0);*/
		
		random = rand() % 6;
		
		diffuse_material_settings->albedo = building_geo_text->texture[random].get();


		// Graphic
		drawable->set_geometry(building_geo_text->geometries[random][0].get());
		drawable->set_material(diffuse_material.get());
		drawable->set_material_settings(diffuse_material_settings.get());

		return random;
}

EDK3::Node* JSF::Building::getDrawable()
{
	return drawable.get();
}

void JSF::Building::SetScale(float x, float y, float z) {
	drawable->set_scale(x, y, z);
	
}

void JSF::Building::SetPosition(float x, float y, float z) {
	drawable->set_position(x, y, z);
}

Vector3 JSF::Building::GetPosition()
{
	return Vector3(drawable->position());
}
