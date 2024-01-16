#include "JSFTexture.h"

//#include <UTRI/gpumanager_utri.h>

JSF::JSFTexture::JSFTexture()
{
	text_id_ = -1;
	glGenTextures(1, &text_id_);
}

JSF::JSFTexture::~JSFTexture()
{
	if (text_id_ != -1) {
		glDeleteTextures(1, &text_id_);
	}
}

void JSF::JSFTexture::set_data(const Format f, const EDK3::Type t, const void* data, unsigned int mipmap_LOD)
{
	
	this->bind(0);
	switch (type()) {
	
		case T_1D:

				//glTexImage1D(ConvertType(type()), mipmap_LOD, ConvertFormat(f), width(), 0, ConvertFormat(f), GPUManagerCustom::ConvertEDK3Type(t), data);
		
			break;
		case T_2D:

			//glTexImage2D(ConvertType(type()), mipmap_LOD, ConvertFormat(f), width(), height(), 0, ConvertFormat(f), GPUManagerCustom::ConvertEDK3Type(t), data);
		
			break;

		case T_3D:

			//glTexImage3D(ConvertType(type()), mipmap_LOD, ConvertFormat(f), width(), height(), depth(), 0, ConvertFormat(f), GPUManagerCustom::ConvertEDK3Type(t), data);
		
			break;
	}

}

void JSF::JSFTexture::bind(unsigned int utext) const
{
	glActiveTexture(GL_TEXTURE0 + utext)
		;
	glBindTexture(ConvertType(type()), text_id_);
}

unsigned int JSF::JSFTexture::internal_id() const
{
	return text_id_;
}

void JSF::JSFTexture::set_min_filter(Filter f)
{
	EDK3::Texture::set_min_filter(f);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_MIN_FILTER, GL_NEAREST + f);
}

void JSF::JSFTexture::set_mag_filter(Filter f)
{
	EDK3::Texture::set_mag_filter(f);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_MAG_FILTER, GL_NEAREST + f);
}

void JSF::JSFTexture::set_wrap_s(Wrap c)
{
	EDK3::Texture::set_wrap_s(c);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_WRAP_S, ConvertWrap(c));
}

void JSF::JSFTexture::set_wrap_t(Wrap c)
{
	EDK3::Texture::set_wrap_t(c);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_WRAP_T, ConvertWrap(c));
}

void JSF::JSFTexture::set_wrap_r(Wrap c)
{
	EDK3::Texture::set_wrap_r(c);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_WRAP_R, ConvertWrap(c));
}

void JSF::JSFTexture::generateMipmaps() const
{
	glGenerateMipmap(ConvertType(type()));
}

GLenum JSF::JSFTexture::ConvertType(Type t) const {
	switch (t) {
	case T_1D:
		return GL_TEXTURE_1D; break;
	case T_2D:
		return GL_TEXTURE_2D; break;
	case T_3D:
		return GL_TEXTURE_3D; break;
	case T_CUBEMAP:
		return GL_TEXTURE_CUBE_MAP; break;
	default:
		return GL_NONE; break;
	}
}

GLint JSF::JSFTexture::ConvertWrap(Wrap c) const {
	
	switch (c) {

		case W_REPEAT:

			return GL_REPEAT; break;

		case W_MIRRORED_REPEAT:

			return GL_MIRRORED_REPEAT; break;

		case W_CLAMP_TO_EDGE:

			return GL_CLAMP_TO_EDGE; break;

		default:

			return -1; break;
	}
}

GLenum JSF::JSFTexture::ConvertFormat(Format t) const {
	switch (t) {
	case F_R:

		return GL_RED; break;

	case F_RG:

		return GL_RG; break;

	case F_BGR:

		return GL_BGR; break;

	case F_RGB:

		return GL_RGB; break;

	case F_BGRA:

		return GL_BGRA; break;

	case F_RGBA:

		return GL_RGBA; break;

	case F_DEPTH:

		return GL_DEPTH; break;

	default:

		return GL_NONE; break;
	}
}

void JSF::JSFTexture::initTexture(Type t, Format internal_format, unsigned int width, unsigned int height, unsigned int depth)
{
	init(t, internal_format, width, height, depth);
}

