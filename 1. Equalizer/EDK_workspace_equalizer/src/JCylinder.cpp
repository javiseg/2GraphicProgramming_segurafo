#include "JCylinder.h"
#include <EDK3/dev/gpumanager.h>

const int MIN_SECTOR_COUNT = 3;
const int MIN_STACK_COUNT = 1;

JSF::JCylinder::JCylinder(float baseRadius, float topRadius, float height, int sectors,
	int stacks, bool smooth) : interleavedStride_c(32)
{
	set(baseRadius, topRadius, height, sectors, stacks, smooth);
}

void JSF::JCylinder::init()
{
	EDK3::dev::GPUManager::Instance()->newBuffer(&buffer_vertex_);

	buffer_vertex_->init(sizeof(float) * (vertices_c.size() + normals_c.size()));
	float* vert = vertices_c.data();
	float* norms = normals_c.data();
	buffer_vertex_->uploadData(vert, sizeof(float) * vertices_c.size(), 0);
	buffer_vertex_->uploadData(norms, sizeof(float) * normals_c.size(), sizeof(float) * vertices_c.size());


	EDK3::dev::GPUManager::Instance()->newBuffer(&buffer_elements_);
	unsigned int* index = indices_c.data();
	buffer_elements_->init(sizeof(float) * indices_c.size());
	buffer_elements_->uploadData(index, sizeof(float) * indices_c.size(), 0);


}



void JSF::JCylinder::set(float baseRadius, float topRadius, float height, int sectors,
	int stacks, bool smooth)
{
	this->baseRadius = baseRadius;
	this->topRadius = topRadius;
	this->height = height;
	this->sectorCount = sectors;
	if (sectors < MIN_SECTOR_COUNT)
		this->sectorCount = MIN_SECTOR_COUNT;
	this->stackCount = stacks;
	if (stacks < MIN_STACK_COUNT)
		this->stackCount = MIN_STACK_COUNT;
	this->smooth = smooth;

	// generate unit circle vertices_c first
	buildUnitCircleVertices();

	buildVerticesSmooth();
}

void JSF::JCylinder::buildUnitCircleVertices()
{
	const float PI = acos(-1);
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle;  // radian

	std::vector<float>().swap(unitCircleVertices);
	for (int i = 0; i <= sectorCount; ++i)
	{
		sectorAngle = i * sectorStep;
		unitCircleVertices.push_back(cos(sectorAngle)); // x
		unitCircleVertices.push_back(sin(sectorAngle)); // y
		unitCircleVertices.push_back(0);                // z
	}
}

void JSF::JCylinder::buildVerticesSmooth()
{

	clearArrays();

	float x, y, z;   

	float radius;                                  


	std::vector<float> sideNormals = getSideNormals();


	for (int i = 0; i <= stackCount; ++i)
	{
		z = -(height * 0.5f) + (float)i / stackCount * height;     
		radius = baseRadius + (float)i / stackCount * (topRadius - baseRadius);    
		float t = 1.0f - (float)i / stackCount;   

		for (int j = 0, k = 0; j <= sectorCount; ++j, k += 3)
		{
			x = unitCircleVertices[k];
			y = unitCircleVertices[k + 1];
			addVertex(x * radius, y * radius, z);   
			addNormal(sideNormals[k], sideNormals[k + 1], sideNormals[k + 2]);
			addTexCoord((float)j / sectorCount, t);
		}
	}


	unsigned int baseVertexIndex = (unsigned int)vertices_c.size() / 3;


	z = -height * 0.5f;
	addVertex(0, 0, z);
	addNormal(0, 0, -1);
	addTexCoord(0.5f, 0.5f);
	for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		addVertex(x * baseRadius, y * baseRadius, z);
		addNormal(0, 0, -1);
		addTexCoord(-x * 0.5f + 0.5f, -y * 0.5f + 0.5f);    
	}


	unsigned int topVertexIndex = (unsigned int)vertices_c.size() / 3;


	z = height * 0.5f;
	addVertex(0, 0, z);
	addNormal(0, 0, 1);
	addTexCoord(0.5f, 0.5f);
	for (int i = 0, j = 0; i < sectorCount; ++i, j += 3)
	{
		x = unitCircleVertices[j];
		y = unitCircleVertices[j + 1];
		addVertex(x * topRadius, y * topRadius, z);
		addNormal(0, 0, 1);
		addTexCoord(x * 0.5f + 0.5f, -y * 0.5f + 0.5f);
	}

	// put indices_c for sides
	unsigned int k1, k2;
	for (int i = 0; i < stackCount; ++i)
	{
		k1 = i * (sectorCount + 1);    
		k2 = k1 + sectorCount + 1;   


		for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
		{

			addIndices(k1, k1 + 1, k2);
			addIndices(k2, k1 + 1, k2 + 1);


			lineIndices_c.push_back(k1);
			lineIndices_c.push_back(k2);

			lineIndices_c.push_back(k2);
			lineIndices_c.push_back(k2 + 1);
			if (i == 0)
			{
				lineIndices_c.push_back(k1);
				lineIndices_c.push_back(k1 + 1);
			}
		}
	}

	baseIndex = (unsigned int)indices_c.size();

	for (int i = 0, k = baseVertexIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < (sectorCount - 1))
			addIndices(baseVertexIndex, k + 1, k);
		else   
			addIndices(baseVertexIndex, baseVertexIndex + 1, k);
	}

	topIndex = (unsigned int)indices_c.size();

	for (int i = 0, k = topVertexIndex + 1; i < sectorCount; ++i, ++k)
	{
		if (i < (sectorCount - 1))
			addIndices(topVertexIndex, k, k + 1);
		else
			addIndices(topVertexIndex, k, topVertexIndex + 1);
	}

	buildInterleavedVertices();
}


std::vector<float> JSF::JCylinder::getSideNormals()
{
	const float PI = acos(-1);
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle;  // radian


	float zAngle = atan2(baseRadius - topRadius, height);
	float x0 = cos(zAngle);     // nx
	float y0 = 0;               // ny
	float z0 = sin(zAngle);     // nz

	std::vector<float> normals_c;
	for (int i = 0; i <= sectorCount; ++i)
	{
		sectorAngle = i * sectorStep;
		normals_c.push_back(cos(sectorAngle) * x0 - sin(sectorAngle) * y0);   // nx
		normals_c.push_back(sin(sectorAngle) * x0 + cos(sectorAngle) * y0);   // ny
		normals_c.push_back(z0);  
		
	}

	return normals_c;
}

void JSF::JCylinder::buildInterleavedVertices()
{
	std::vector<float>().swap(interleavedVertices_c);

	std::size_t i, j;
	std::size_t count = vertices_c.size();
	for (i = 0, j = 0; i < count; i += 3, j += 2)
	{
		//interleavedVertices_c.push_back(vertices_c[i]);
		//interleavedVertices_c.push_back(vertices_c[i+1]);
		//interleavedVertices_c.push_back(vertices_c[i+2]);
		interleavedVertices_c.insert(interleavedVertices_c.end(), &vertices_c[i], &vertices_c[i] + 3);

		//interleavedVertices_c.push_back(normals_c[i]);
		//interleavedVertices_c.push_back(normals_c[i+1]);
		//interleavedVertices_c.push_back(normals_c[i+2]);
		interleavedVertices_c.insert(interleavedVertices_c.end(), &normals_c[i], &normals_c[i] + 3);

		//interleavedVertices_c.push_back(texCoords_c[j]);
		//interleavedVertices_c.push_back(texCoords_c[j+1]);
		interleavedVertices_c.insert(interleavedVertices_c.end(), &texCoords_c[j], &texCoords_c[j] + 2);
	}
}



void JSF::JCylinder::addVertex(float x, float y, float z)
{
	vertices_c.push_back(x);
	vertices_c.push_back(y);
	vertices_c.push_back(z);
}

void JSF::JCylinder::addNormal(float nx, float ny, float nz)
{
	normals_c.push_back(nx);
	normals_c.push_back(ny);
	normals_c.push_back(nz);
}


void JSF::JCylinder::addTexCoord(float s, float t)
{
	texCoords_c.push_back(s);
	texCoords_c.push_back(t);
}


void JSF::JCylinder::addIndices(unsigned int i1, unsigned int i2, unsigned int i3)
{
	indices_c.push_back(i1);
	indices_c.push_back(i2);
	indices_c.push_back(i3);
}

void JSF::JCylinder::clearArrays()
{
	std::vector<float>().swap(vertices_c);
	std::vector<float>().swap(normals_c);
	std::vector<float>().swap(texCoords_c);
	std::vector<unsigned int>().swap(indices_c);
	std::vector<unsigned int>().swap(lineIndices_c);
}


bool JSF::JCylinder::bindAttribute(const EDK3::Attribute a, unsigned int where_to_bind_attribute) const {
	EDK3::dev::GPUManager::Instance()->enableVertexAttribute(buffer_vertex_.get(), 0, EDK3::Type::T_FLOAT_3, false, 0, 0);
	return true;
}

void JSF::JCylinder::render() const {
	EDK3::dev::GPUManager::Instance()->drawElements(EDK3::dev::GPUManager::Instance()->kDrawMode_Triangles, indices_c.size(), buffer_elements_.get(), EDK3::Type::T_UINT, 0);
}

void JSF::CreateCylinder(EDK3::ref_ptr<EDK3::Drawable>* draw_output, EDK3::ref_ptr<JSF::JCylinder>* g,
	EDK3::ref_ptr<MatCustomJSF>* mat,
	EDK3::ref_ptr<MatCustomJSF::Settings>* mat_settings,
	float* scale, float* positions) {

	(*draw_output)->set_geometry(g->get());
	(*draw_output)->set_material(mat->get());
	(*draw_output)->set_material_settings(mat_settings->get());
	(*draw_output)->set_scale(scale);
	(*draw_output)->set_position(positions);

}