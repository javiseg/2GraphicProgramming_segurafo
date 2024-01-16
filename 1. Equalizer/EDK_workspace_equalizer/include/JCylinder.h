#pragma once
#include <EDK3/geometry.h>
#include <vector>
#include <EDK3/drawable.h>
#include "matcustom_jsf.h"

namespace JSF {


class JCylinder :
	public EDK3::CustomGeometry
{

		public:

			JCylinder(float baseRadius = 1.0f, float topRadius = 1.0f, float height = 1.0f,
				int sectorCount = 36, int stackCount = 1, bool smooth = true);
			~JCylinder() {}

			void init();

			// getters/setters
			float getBaseRadius() const { return baseRadius; }
			float getTopRadius() const { return topRadius; }
			float getHeight() const { return height; }
			int getSectorCount() const { return sectorCount; }
			int getStackCount() const { return stackCount; }
			void set(float baseRadius, float topRadius, float height,
				int sectorCount, int stackCount, bool smooth = true);
			void buildInterleavedVertices();

			virtual bool bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute) const override;
			virtual void render() const override;

	protected:

	private:
		// member functions
		void clearArrays();
		void buildVerticesSmooth();
		void buildUnitCircleVertices();
		void addVertex(float x, float y, float z);
		void addNormal(float x, float y, float z);
		void addTexCoord(float s, float t);
		void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
		std::vector<float> getSideNormals();


		// memeber vars
		float baseRadius;
		float topRadius;
		float height;
		int sectorCount;                        // # of slices
		int stackCount;                         // # of stacks
		unsigned int baseIndex;                 // starting index of base
		unsigned int topIndex;                  // starting index of top
		bool smooth;
		std::vector<float> unitCircleVertices;
		std::vector<float> vertices_c;
		std::vector<float> normals_c;
		std::vector<float> texCoords_c;
		std::vector<unsigned int> indices_c;
		std::vector<unsigned int> lineIndices_c;

		// interleaved
		std::vector<float> interleavedVertices_c;
		int interleavedStride_c;

	EDK3::ref_ptr<EDK3::dev::Buffer> buffer_vertex_;
	EDK3::ref_ptr<EDK3::dev::Buffer> buffer_elements_;

	};
void CreateCylinder(EDK3::ref_ptr<EDK3::Drawable>* draw_output, EDK3::ref_ptr<JSF::JCylinder>* g,
	EDK3::ref_ptr<MatCustomJSF>* mat,
	EDK3::ref_ptr<MatCustomJSF::Settings>* mat_settings,
	float* scale, float* positions);

}

