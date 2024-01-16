#pragma once
#include <vector>
#include <EDK3/geometry.h>
#include "matcustom_jsf.h"
#include <EDK3/drawable.h>
#include "JCircle.h"


namespace JSF {

	class JCircle : public EDK3::CustomGeometry
	{
	public:

		void init();
		void buildVertices(float radius, int sectors, int stacks);
		void addVertex(float x, float y, float z);
		void addNormal(float nx, float ny, float nz);
		void addTexCoord(float s, float t);
		void addIndices(unsigned int i1, unsigned int i2, unsigned int i3);
		void buildInterleavedVertices();

		virtual bool bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute) const override;
		virtual void render() const override;


	private:
		int sectorCount;
		int stackCount;
		std::vector<float> vertices_c;
		std::vector<float> normals_c;
		std::vector<float> texCoords_c;
		std::vector<unsigned int> indices_c;
		std::vector<unsigned int> lineIndices_c;
		std::vector<float> interleavedVertices_c;
		int interleavedStride_c;

		EDK3::ref_ptr<EDK3::dev::Buffer> buffer_vertex_;
		EDK3::ref_ptr<EDK3::dev::Buffer> buffer_elements_;

	};
	void CreateSphere(EDK3::ref_ptr<EDK3::Drawable>* draw_output, EDK3::ref_ptr<JSF::JCircle>* g,
		EDK3::ref_ptr<MatCustomJSF>* mat,
		EDK3::ref_ptr<MatCustomJSF::Settings>* mat_settings,
		float* scale, float* positions);

	
}
