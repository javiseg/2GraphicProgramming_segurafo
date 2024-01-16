#include "Block.h"
#include "..\include\Block.h"
#include <stdlib.h>
#include <time.h> 
#include <EDK3/matdiffusetexture.h>

JSF::Block::Block() {

	num_buildings_ = 4;
	num_obj_ = 6;
	num_src_ = num_obj_;
	buildings_.alloc();
}

void JSF::Block::GenerateRandomBlock(EDK3::ref_ptr<JSF::BuildingGeometries> building_geo_text, int center_prox)
{


	int selected = 0;
	int building_index = 0;
	
	for (int i = 0; i < num_buildings_; i++) {
		
		selected = buildings_->CreateBuilding(building_geo_text.get(), center_prox);
		buildings_->set_rotation_y(115.0f);
	
		buildings_->SetScale(1.0f, 1.0f + center_prox / 3.0f, 1.0f);

		if (i % 2 == 0) {
			buildings_->SetPosition(i * 1500, 0.0f, 0.0f);
		}
		else {
			buildings_->SetPosition((i - 1) * 1500,0.0f, 1500.0f);
		}
		buildings_->set_rotation_y(45.0f);
		this->addChild(buildings_->getDrawable());
		if (selected == 4 && i >= 2) {
			this->child(building_index)->set_rotation_y(180.0f);
		}
		
		building_index++;
		
	}
	this->set_scale(0.2f, 0.2f, 0.2f);
	this->set_position(0.0f, 0.0f, 0.0f);
	

}

void JSF::Block::SetBuildingsPerBlock(int num_buildings)
{
	num_buildings_ = num_buildings;
}



void JSF::Block::AddBlocks()
{
	for (int i = 0; i < num_buildings_; i++) {
		//this->addChild(buildings_[i].get());
	}
	this->set_scale(1.0f, 1.0f, 1.0f);
	this->set_position(0.0f, 0.0f, 0.0f);
}
