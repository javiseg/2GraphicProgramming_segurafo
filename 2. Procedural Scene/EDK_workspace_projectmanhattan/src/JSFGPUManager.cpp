#include "JSFGPUManager.h"
#include <EDK3/dev/gpumanager.h>
#include <EDK3/dev/program.h>

#include "JSFShader.h"
#include "JSFBuffer.h"
#include "JSFTexture.h"

JSF::JSFGPUManager::JSFGPUManager()
{

}

void JSF::JSFGPUManager::newShader(EDK3::ref_ptr<EDK3::dev::Shader>* output)
{
	output->allocT<JSF::JSFShader>();
}

void JSF::JSFGPUManager::newBuffer(EDK3::ref_ptr<EDK3::dev::Buffer>* output)
{
	output->allocT<JSF::JSFBuffer>();
}

void JSF::JSFGPUManager::newProgram(EDK3::ref_ptr<EDK3::dev::Program>* output)
{
	//output->allocT<EDK3::dev::Program>();
}

//void JSF::JSFGPUManager::newTexture2D(const EDK3::Texture::Format internal_format, const unsigned int width, const unsigned int height, EDK3::ref_ptr<EDK3::Texture>* output)
//{
//	output->allocT<UTRI::TextureCustom>();
//	UTRI::TextureCustom* texture = static_cast<UTRI::TextureCustom*>(output->get());
//	texture->initTexture(EDK3::Texture::Type::T_2D, internal_format, width, height, 0);
//}

GLenum JSF::JSFGPUManager::ConvertEDK3Type(EDK3::Type t) {
	switch (t) {
	case EDK3::T_FLOAT_1:
		return GL_FLOAT;
	case EDK3::T_FLOAT_2:
		return GL_FLOAT;
	case EDK3::T_FLOAT_3:
		return GL_FLOAT;
	case EDK3::T_FLOAT_4:
		return GL_FLOAT;
	case EDK3::T_DOUBLE_1:
		return GL_DOUBLE;
	case EDK3::T_DOUBLE_2:
		return GL_DOUBLE;
	case EDK3::T_DOUBLE_3:
		return GL_DOUBLE;
	case EDK3::T_DOUBLE_4:
		return GL_DOUBLE;
	case EDK3::T_INT_1:
		return GL_INT;
	case EDK3::T_INT_2:
		return GL_INT;
	case EDK3::T_INT_3:
		return GL_INT;
	case EDK3::T_INT_4:
		return GL_INT;
	case EDK3::T_UINT_1:
		return GL_UNSIGNED_INT;
	case EDK3::T_UINT_2:
		return GL_UNSIGNED_INT;
	case EDK3::T_UINT_3:
		return GL_UNSIGNED_INT;
	case EDK3::T_UINT_4:
		return GL_UNSIGNED_INT;
	case EDK3::T_BYTE_1:
		return GL_BYTE;
	case EDK3::T_BYTE_2:
		return GL_BYTE;
	case EDK3::T_BYTE_3:
		return GL_BYTE;
	case EDK3::T_BYTE_4:
		return GL_BYTE;
	case EDK3::T_UBYTE_1:
		return GL_UNSIGNED_BYTE;
	case EDK3::T_UBYTE_2:
		return GL_UNSIGNED_BYTE;
	case EDK3::T_UBYTE_3:
		return GL_UNSIGNED_BYTE;
	case EDK3::T_UBYTE_4:
		return GL_UNSIGNED_BYTE;
	case EDK3::T_SHORT_1:
		return GL_SHORT;
	case EDK3::T_SHORT_2:
		return GL_SHORT;
	case EDK3::T_SHORT_3:
		return GL_SHORT;
	case EDK3::T_SHORT_4:
		return GL_SHORT;
	case EDK3::T_USHORT_1:
		return GL_UNSIGNED_SHORT;
	case EDK3::T_USHORT_2:
		return GL_UNSIGNED_SHORT;
	case EDK3::T_USHORT_3:
		return GL_UNSIGNED_SHORT;
	case EDK3::T_USHORT_4:
		return GL_UNSIGNED_SHORT;
	case EDK3::T_SAMPLER_1D:
		return GL_SAMPLER_1D;
	case EDK3::T_SAMPLER_2D:
		return GL_SAMPLER_2D;
	case EDK3::T_SAMPLER_3D:
		return GL_SAMPLER_3D;
	default: return GL_NONE;
	}
}

unsigned JSF::JSFGPUManager::GetSize(EDK3::Type t) {
	switch (t) {
	case EDK3::T_FLOAT_1:
		return 1;
	case EDK3::T_FLOAT_2:
		return 2;
	case EDK3::T_FLOAT_3:
		return 3;
	case EDK3::T_FLOAT_4:
		return 4;
	case EDK3::T_DOUBLE_1:
		return 1;
	case EDK3::T_DOUBLE_2:
		return 2;
	case EDK3::T_DOUBLE_3:
		return 3;
	case EDK3::T_DOUBLE_4:
		return 4;
	case EDK3::T_INT_1:
		return 1;
	case EDK3::T_INT_2:
		return 2;
	case EDK3::T_INT_3:
		return 3;
	case EDK3::T_INT_4:
		return 4;
	case EDK3::T_UINT_1:
		return 1;
	case EDK3::T_UINT_2:
		return 2;
	case EDK3::T_UINT_3:
		return 3;
	case EDK3::T_UINT_4:
		return 4;
	case EDK3::T_BYTE_1:
		return 1;
	case EDK3::T_BYTE_2:
		return 2;
	case EDK3::T_BYTE_3:
		return 3;
	case EDK3::T_BYTE_4:
		return 4;
	case EDK3::T_UBYTE_1:
		return 1;
	case EDK3::T_UBYTE_2:
		return 2;
	case EDK3::T_UBYTE_3:
		return 3;
	case EDK3::T_UBYTE_4:
		return 4;
	case EDK3::T_SHORT_1:
		return 1;
	case EDK3::T_SHORT_2:
		return 2;
	case EDK3::T_SHORT_3:
		return 3;
	case EDK3::T_SHORT_4:
		return 4;
	case EDK3::T_USHORT_1:
		return 1;
	case EDK3::T_USHORT_2:
		return 2;
	case EDK3::T_USHORT_3:
		return 3;
	case EDK3::T_USHORT_4:
		return 4;
	default:
		return GL_NONE;
	}
}

void JSF::JSFGPUManager::enableVertexAttribute(const EDK3::dev::Buffer* buffer, const unsigned int attribute_index, const EDK3::Type type, const bool normalized, const unsigned int offset, const unsigned int stride)
{

	buffer->bind(EDK3::dev::Buffer::kTarget_Vertex_Data);

	glVertexAttribPointer(attribute_index, GetSize(type), ConvertEDK3Type(type), normalized, stride, (const void*)offset);
	
	glEnableVertexAttribArray(attribute_index);
}

void JSF::JSFGPUManager::disableVertexAttribute(const unsigned int attrib_index)
{
	glDisableVertexAttribArray(attrib_index);
}

/*
void JSF::JSFGPUManager::drawElements(const DrawMode mode, unsigned int count, const EDK3::dev::Buffer* buffer, const EDK3::Type element_type, const unsigned int offset) const
{
	GLenum modeGL;
	switch (mode)
	{
		case kDrawMode_Triangles:
				modeGL = GL_TRIANGLES; 
			break;
		case kDrawMode_TriangleStrip:
			modeGL = GL_TRIANGLE_STRIP; 
				break;
		case kDrawMode_Points:
			modeGL = GL_POINTS; 
				break;
		case kDrawMode_Lines:
			modeGL = GL_LINES; 
				break;
		case kDrawMode_LineStrip:
				modeGL = GL_LINE_STRIP; 
			break;
		case kDrawMode_LineLoop:
				modeGL = GL_LINE_LOOP; 
			break;
		default: 
			break;
	}

	buffer->bind(EDK3::dev::Buffer::kTarget_Elements);
	glDrawElements(modeGL, count, ConvertEDK3Type((EDK3::Type)element_type), (const void*)offset);
}*/

void JSF::JSFGPUManager::enableCullFaces(const FaceType f)
{
	glEnable(GL_CULL_FACE);
	switch (f)
	{
	case kFace_Back:
		glCullFace(GL_BACK); break;
	case kFace_Front:
		glCullFace(GL_FRONT); break;
	case kFace_FrontAndBack:
		glCullFace(GL_FRONT_AND_BACK); break;
	default: break;
	}
}

void JSF::JSFGPUManager::disableCullFaces()
{
	glDisable(GL_CULL_FACE);
}

void JSF::JSFGPUManager::changeColorMask(const bool red, const bool green, const bool blue, const bool alpha)
{
	glColorMask(red, green, blue, alpha);
}

void JSF::JSFGPUManager::changeDepthMask(bool enable)
{
	glDepthMask(enable);
}

void JSF::JSFGPUManager::enableDepthTest(const CompareFunc f)
{
	glEnable(GL_DEPTH_TEST);
	switch (f)
	{
	case kCompareFunc_Never:
		glDepthFunc(GL_NEVER); break;
	case kCompareFunc_Less:
		glDepthFunc(GL_LESS); break;
	case kCompareFunc_LessOrEqual:
		glDepthFunc(GL_LEQUAL); break;
	case kCompareFunc_Equal:
		glDepthFunc(GL_EQUAL); break;
	case kCompareFunc_NotEqual:
		glDepthFunc(GL_NOTEQUAL); break;
	case kCompareFunc_GreaterOrEqual:
		glDepthFunc(GL_GEQUAL); break;
	case kCompareFunc_Greater:
		glDepthFunc(GL_GREATER); break;
	case kCompareFunc_Always:
		glDepthFunc(GL_ALWAYS); break;
	default: break;
	}
}

void JSF::JSFGPUManager::disableDepthTest()
{
	glDisable(GL_DEPTH_TEST);
}

void JSF::JSFGPUManager::enableScissor(int x, int y, unsigned int width, unsigned int height)
{
	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, width, height);
}

void JSF::JSFGPUManager::disableScissor()
{
	glDisable(GL_SCISSOR_TEST);
}

void JSF::JSFGPUManager::enableBlend(BlendParam source, BlendParam destination, BlendOp operation, const float ConstantColor[4])
{
	GLint source_, destination_, operation_;
	glEnable(GL_BLEND);
	switch (source)
	{
	case kBlendParam_Zero:
		source_ = GL_ZERO; break;
	case kBlendParam_One:
		source_ = GL_ONE; break;
	case kBlendParam_SourceColor:
		source_ = GL_SRC_COLOR; break;
	case kBlendParam_OneMinusSourceColor:
		source_ = GL_ONE_MINUS_SRC_COLOR; break;
	case kBlendParam_DestinationColor:
		source_ = GL_DST_COLOR; break;
	case kBlendParam_OneMinusDestinationColor:
		source_ = GL_ONE_MINUS_DST_COLOR; break;
	case kBlendParam_SourceAlpha:
		source_ = GL_SRC_ALPHA; break;
	case kBlendParam_OneMinusSourceAlpha:
		source_ = GL_ONE_MINUS_SRC_ALPHA; break;
	case kBlendParam_DestinationAlpha:
		source_ = GL_DST_ALPHA; break;
	case kBlendParam_OneMinusDestinationAlpha:
		source_ = GL_ONE_MINUS_DST_ALPHA; break;
	case kBlendParam_ConstantColor:
		source_ = GL_CONSTANT_COLOR; break;
	case kBlendParam_OneMinusConstantColor:
		source_ = GL_ONE_MINUS_CONSTANT_COLOR; break;
	case kBlendParam_ConstantAlpha:
		source_ = GL_CONSTANT_ALPHA; break;
	case kBlendParam_OneMinusConstantAlpha:
		source_ = GL_ONE_MINUS_CONSTANT_ALPHA; break;
	case kBlendParam_SourceAlphaSaturate:
		source_ = GL_SRC_ALPHA_SATURATE; break;
	default: break;
	}

	switch (destination)
	{
	case kBlendParam_Zero:
		destination_ = GL_ZERO; break;
	case kBlendParam_One:
		destination_ = GL_ONE; break;
	case kBlendParam_SourceColor:
		destination_ = GL_SRC_COLOR; break;
	case kBlendParam_OneMinusSourceColor:
		destination_ = GL_ONE_MINUS_SRC_COLOR; break;
	case kBlendParam_DestinationColor:
		destination_ = GL_DST_COLOR; break;
	case kBlendParam_OneMinusDestinationColor:
		destination_ = GL_ONE_MINUS_DST_COLOR; break;
	case kBlendParam_SourceAlpha:
		destination_ = GL_SRC_ALPHA; break;
	case kBlendParam_OneMinusSourceAlpha:
		destination_ = GL_ONE_MINUS_SRC_ALPHA; break;
	case kBlendParam_DestinationAlpha:
		destination_ = GL_DST_ALPHA; break;
	case kBlendParam_OneMinusDestinationAlpha:
		destination_ = GL_ONE_MINUS_DST_ALPHA; break;
	case kBlendParam_ConstantColor:
		destination_ = GL_CONSTANT_COLOR; break;
	case kBlendParam_OneMinusConstantColor:
		destination_ = GL_ONE_MINUS_CONSTANT_COLOR; break;
	case kBlendParam_ConstantAlpha:
		destination_ = GL_CONSTANT_ALPHA; break;
	case kBlendParam_OneMinusConstantAlpha:
		destination_ = GL_ONE_MINUS_CONSTANT_ALPHA; break;
	case kBlendParam_SourceAlphaSaturate:
		destination_ = GL_SRC_ALPHA_SATURATE; break;
	default: break;
	}

	switch (operation)
	{
	case kBlendOp_Add:
		operation_ = GL_FUNC_ADD; break;
	case kBlendOp_Subtract:
		operation_ = GL_FUNC_SUBTRACT; break;
	case kBlendOp_ReverseSubtract:
		operation_ = GL_FUNC_REVERSE_SUBTRACT; break;
	case kBlendOp_Min:
		operation_ = GL_MIN; break;
	case kBlendOp_Max:
		operation_ = GL_MAX; break;
	default: break;
	}

	glBlendFunc(source_, destination_);
	glBlendEquation(operation_);
	if (ConstantColor != nullptr) {
		glBlendColor(ConstantColor[0], ConstantColor[1], ConstantColor[2], ConstantColor[3]);
	}
	else {
		glBlendColor(0, 0, 0, 0);
	}

}

void JSF::JSFGPUManager::disableBlend()
{
	glDisable(GL_BLEND);
}

JSF::JSFGPUManager::~JSFGPUManager()
{

}
