#include "City.h"
#include <time.h>
#include <EDK3/matdiffusetexture.h>
#include <stdlib.h>
#include "TrafficLight.h"
#include <EDK3/drawable.h>
#include <EDK3/geometry.h>
#include "matcustom_jsf.h"

JSF::City::City()
{
	rows_ = 10;
	cols_ = 10;

	map_cols_ = (cols_ * 2) + 1;
	map_rows_ = (rows_ * 2) + 1;

	map = (int*)calloc((map_rows_ * map_cols_),sizeof(int));

	distance_rows_ = 600.0f;
	distance_cols_ = 700.0f;
	distance_road_rows_ = 994.0f;
	distance_road_cols_ = 994.0f;

	num_blocks_ = 100.0f;
	blocks_.alloc();

	
	tr_lg.alloc();
	tr_lg->GenerateTrafficLight(0);
}

void JSF::City::GenerateCity(EDK3::ref_ptr<JSF::BuildingGeometries> building_geo_text, EDK3::ref_ptr<JSF::RoadGeometries> road_geometries)
{

	EDK3::ref_ptr<EDK3::Drawable> road_dr;
	EDK3::ref_ptr<EDK3::MatDiffuseTexture> road_mat;
	road_mat.alloc();
	EDK3::ref_ptr<EDK3::MatDiffuseTexture::Settings> road_mat_settings;
	road_mat_settings.alloc();
	road_mat_settings->set_texture(road_geometries->texture.get());

	float x_road_offset = 200.0f;
	int manhattan_distance = 0;
	int center_prox;
	srand(time(NULL));
	for (int i = 0; i < cols_; i++) {
		for (int j = 0; j < rows_; j++) {
			blocks_.alloc();
			manhattan_distance = (abs(i - (cols_ / 2))) + (abs(j - (rows_ / 2)));
			if (manhattan_distance <= 1) {
				center_prox = 3;
			}
			else if (manhattan_distance <= 2) {
				center_prox = 2;
			}
			else if (manhattan_distance <= 3) {
				center_prox = 1;
			}
			else
				center_prox = 0;


			blocks_->GenerateRandomBlock(building_geo_text.get(), center_prox);
			blocks_->set_position(distance_rows_ + (distance_road_rows_ * 2) * i, 0.0f, distance_cols_ + ((distance_road_cols_ * 2) *  j));
			blocks_->set_scale(0.3f, 0.3f, 0.3f);
			this->addChild(blocks_.get());
						
			//road_dr->set_geometry(road_geometries[)

		}
	}
	this->set_position(0.0f, 0.0f, 0.0f);
	this->set_scale(1.0f, 1.0f, 1.0f);

}

void JSF::City::GenerateRoad(EDK3::ref_ptr<JSF::RoadGeometries> road_geometries)
{

	GenerateLogicRoad(); 

	char* texture_src = "../assets/textures/T_building_01_Dif.png";
	

	EDK3::ref_ptr<EDK3::Drawable> road_dr;
	EDK3::ref_ptr<MatCustomJSF> diffuse_material;
	diffuse_material.alloc();
	char* vert_shader = "../assets/shaders/shader_building.vert";
	char* frag_shader = "../assets/shaders/shader_building.frag";

	diffuse_material->load_shaders_from_filepaths(vert_shader, frag_shader);

	EDK3::ref_ptr<MatCustomJSF::Settings> diffuse_material_settings;
	diffuse_material_settings.alloc();
	diffuse_material_settings->albedo = road_geometries->texture.get();


	/*EDK3::ref_ptr<MatCustomJSF> diffuse_material;
	diffuse_material.alloc();
	diffuse_material->load_shaders_from_filepaths(
	"../assets/shaders/shader_traffic_light.vert",
		"../assets/shaders/shader_traffic_light.frag"
	);*/

	//diffuse_material_settings->set_texture(tr_lg->texture.get());
	//diffuse_material_settings->texture()->bind(0);



	for (int i = 0; i < map_rows_; i++) {
		for (int j = 0; j < map_cols_; j++) {

			float y_offset = 0.0f;
			road_dr.alloc();
			road_dr->set_material(diffuse_material.get());
			//diffuse_material_settings->albedo = tr_lg->texture.get();
			road_dr->set_material_settings(diffuse_material_settings.get());
			road_dr->set_scale(1.0f, 1.0f, 1.0f);

			if (map[i * map_rows_ + j] == 5) {
				road_dr->set_rotation_y(90.0f);
				map[i * map_rows_ + j] = 4;
			}
			else if (map[i * map_rows_ + j] == 3) {
				y_offset = 5.0f;
			}
			if (map[i * map_rows_ + j] == 0) {
				EDK3::ref_ptr<EDK3::Drawable> draw_traffic_light;
				draw_traffic_light.alloc();
				EDK3::ref_ptr<MatCustomJSF::Settings> traffic_light_settings_material;
				traffic_light_settings_material.alloc();
				draw_traffic_light->set_geometry(tr_lg->geometries[0].get());
				draw_traffic_light->set_material(diffuse_material.get());
				traffic_light_settings_material->albedo = tr_lg->texture.get();

				draw_traffic_light->set_material_settings(traffic_light_settings_material.get());
				draw_traffic_light->set_rotation_y(180.0f);
				draw_traffic_light->set_position(-270.0f, 0.0f, -270.0f);
				//draw_traffic_light->set_position(road_dr->position()[0], road_dr->position()[1], road_dr->position()[2]);
				road_dr->addChild(draw_traffic_light.get());
			}

			road_dr->set_geometry(road_geometries->geometries[map[i * map_rows_ + j]][0].get());
			
			
			
			road_dr->set_position(distance_road_cols_ * j, y_offset,distance_road_rows_ * i);
			


			this->addChild(road_dr.get());
			/*road_dr.alloc();
			road_dr->set_material(road_mat.get());
			road_dr->set_material_settings(road_mat_settings.get());
			road_dr->set_scale(1.0f, 1.0f, 1.0f);
			road_dr->set_geometry(road_geometries->geometries[0][0].get());
			road_dr->set_position(1000.0f, 0.0f, 200.0f);*/
			//this->addChild(road_dr.get());
		}
	}

}

void JSF::City::GenerateLogicRoad()
{
	for (int i = 0; i < map_rows_; i++) {
		for (int j = 0; j < map_cols_; j++) {
		
			if (i % 2 != 0 && j % 2 != 0) {
				map[i * map_rows_ + j] = 3;
			}
			else if (i % 2 == 0 && j % 2 == 0) {
				map[i * map_rows_ + j] = 0;
			}
			else if (i % 2 == 0 && j % 2 != 0) {
				map[i * map_rows_ + j] = 4;
			}
			else {
				map[i * map_rows_ + j] = 5;
			}
		}
	}
}

void JSF::City::AddRows()
{
}

void JSF::City::AddCols()
{
}

void JSF::City::QuitRows()
{
}

void JSF::City::QuitCols()
{
}


