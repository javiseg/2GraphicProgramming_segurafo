#include "JCircle.h"
#include <EDK3/dev/gpumanager.h>

void JSF::JCircle::init()
{
	EDK3::dev::GPUManager::Instance()->newBuffer(&buffer_vertex_);

	buffer_vertex_->init(sizeof(float) * (vertices_c.size() + normals_c.size()));
	float* vert = vertices_c.data();
	float* norms = normals_c.data();
	buffer_vertex_->uploadData(vert, sizeof(float) * vertices_c.size(), 0);
	buffer_vertex_->uploadData(norms, sizeof(float) * normals_c.size(), sizeof(float) * vertices_c.size());


	EDK3::dev::GPUManager::Instance()->newBuffer(&buffer_elements_);
	unsigned int* index = indices_c.data();
	buffer_elements_->init(sizeof(float)* indices_c.size());
	buffer_elements_->uploadData(index, sizeof(float) * indices_c.size(), 0);


}


void JSF::JCircle::buildVertices(float radius, int sectors, int stacks)
{
	const float PI = acos(-1);
	this->sectorCount = sectors;
	this->stackCount = stacks;
	float x, y, z, xy;                           
	float nx, ny, nz, lengthInv = 1.0f / radius;   
	float s, t;                                    

	float sectorStep = 2 * PI / sectorCount;
	float stackStep = PI / stackCount;
	float sectorAngle, stackAngle;

	for (int i = 0; i <= stackCount; ++i)
	{
		stackAngle = PI / 2 - i * stackStep;   
		xy = radius * cosf(stackAngle);       
		z = radius * sinf(stackAngle);             

		for (int j = 0; j <= sectorCount; ++j)
		{
			sectorAngle = j * sectorStep;         

			// vertex position
			x = xy * cosf(sectorAngle);           
			y = xy * sinf(sectorAngle);        
			addVertex(x, y, z);

			// normalized vertex normal
			nx = x * lengthInv;
			ny = y * lengthInv;
			nz = z * lengthInv;
			addNormal(nx, ny, nz);

			// vertex tex coord between [0, 1]
			s = (float)j / sectorCount;
			t = (float)i / stackCount;
			addTexCoord(s, t);
		}
	}

	
	unsigned int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);  
		k2 = k1 + sectorCount + 1;     

		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{
			if (i != 0)
			{
				addIndices(k1, k2, k1 + 1); 
			}

			if (i != (stackCount - 1))
			{
				addIndices(k1 + 1, k2, k2 + 1);
			}

			// vertical lines for all stacks
			lineIndices_c.push_back(k1);
			lineIndices_c.push_back(k2);
			if (i != 0)  // horizontal lines except 1st stack
			{
				lineIndices_c.push_back(k1);
				lineIndices_c.push_back(k1 + 1);
			}
		}
	}

	// generate interleaved vertex array as well
	buildInterleavedVertices();
}

void JSF::JCircle::addVertex(float x, float y, float z)
{
	vertices_c.push_back(x);
	vertices_c.push_back(y);
	vertices_c.push_back(z);
}

void JSF::JCircle::addNormal(float nx, float ny, float nz)
{
	normals_c.push_back(nx);
	normals_c.push_back(ny);
	normals_c.push_back(nz);
}

void JSF::JCircle::addTexCoord(float s, float t)
{
	texCoords_c.push_back(s);
	texCoords_c.push_back(t);
}

void JSF::JCircle::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
	indices_c.push_back(i1);
	indices_c.push_back(i2);
	indices_c.push_back(i3);
}

void JSF::JCircle::buildInterleavedVertices()
{
	std::vector<float>().swap(interleavedVertices_c);

	std::size_t i, j;
	std::size_t count = vertices_c.size();
	for (i = 0, j = 0; i < count; i += 3, j += 2)
	{
		interleavedVertices_c.push_back(vertices_c[i]);
		interleavedVertices_c.push_back(vertices_c[i + 1]);
		interleavedVertices_c.push_back(vertices_c[i + 2]);

		interleavedVertices_c.push_back(normals_c[i]);
		interleavedVertices_c.push_back(normals_c[i + 1]);
		interleavedVertices_c.push_back(normals_c[i + 2]);

		interleavedVertices_c.push_back(texCoords_c[j]);
		interleavedVertices_c.push_back(texCoords_c[j + 1]);
	}
}

bool JSF::JCircle::bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute) const {
	EDK3::dev::GPUManager::Instance()->enableVertexAttribute(buffer_vertex_.get(), 0, EDK3::Type::T_FLOAT_3, false, 0, 0);
	return true;
}

void JSF::JCircle::render() const {
	EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::Instance()->kDrawMode_Triangles, indices_c.size(), buffer_elements_.get(), EDK3::Type::T_UINT, 0);
}

void JSF::CreateSphere(EDK3::ref_ptr<EDK3::Drawable>* draw_output, EDK3::ref_ptr<JSF::JCircle>* g,
	EDK3::ref_ptr<MatCustomJSF>* mat,
	EDK3::ref_ptr<MatCustomJSF::Settings>* mat_settings,
	float* scale, float* positions) {

	(*draw_output)->set_geometry(g->get());
	(*draw_output)->set_material(mat->get());
	(*draw_output)->set_material_settings(mat_settings->get());
	(*draw_output)->set_scale(scale);
	(*draw_output)->set_position(positions);

}
