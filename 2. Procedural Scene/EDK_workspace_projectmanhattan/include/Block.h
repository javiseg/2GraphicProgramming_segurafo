#pragma once
#include "buildings.h"
#include "RoadGeometries.h"


namespace JSF {
	class Block : public EDK3::Node
	{
		public:	

			Block();

			void GenerateRandomBlock(EDK3::ref_ptr<JSF::BuildingGeometries> building_geo_text, int center_prox);
			void SetBuildingsPerBlock(int num_buildings);


			int GetNumBuildings() { return num_buildings_; }

			void AddBlocks();

		private:
			EDK3::ref_ptr<Building> buildings_;
			int num_buildings_;
			int num_obj_;
			int num_src_;

			char* obj_src[6];
			char* texture_src[6];

	};
}


