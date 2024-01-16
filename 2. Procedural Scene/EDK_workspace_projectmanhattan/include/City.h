#pragma once

#include "Block.h"
#include "BuildingGeometries.h"
#include "RoadGeometries.h"
#include "TrafficLight.h"

namespace JSF {

	class City : public EDK3::Node
	{

	public:

		City();

		void GenerateCity(EDK3::ref_ptr<JSF::BuildingGeometries> building_geo_text, EDK3::ref_ptr<JSF::RoadGeometries> road_geometries);
		void GenerateRoad(EDK3::ref_ptr<JSF::RoadGeometries> road_geometries);
		void GenerateLogicRoad();

		void SetNumBlocks(float num_blocks) { num_blocks_ = num_blocks; }
		int GetNumBlocks() { return num_blocks_; }

		void SetRows(int rows) { rows_ = rows; map_rows_ = (rows_ * 2) + 1;}
		int GetRows() { return rows_; }

		void SetCols(int cols) { cols_ = cols;  map_cols_ = (cols_ * 2) + 1;}
		int GetCols() { return cols_; }

		void AddRows();
		void AddCols();

		void QuitRows();
		void QuitCols();

	private:

		EDK3::ref_ptr<Block> blocks_;
		EDK3::ref_ptr<TrafficLight> tr_lg;
		int num_blocks_;
		int rows_;
		int cols_;
		float distance_rows_;
		float distance_cols_;
		float distance_road_rows_;
		float distance_road_cols_;

		int map_cols_;
		int map_rows_;
		int* map;



	};

}

