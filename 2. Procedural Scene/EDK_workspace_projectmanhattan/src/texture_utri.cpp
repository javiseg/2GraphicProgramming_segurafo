#include <texture_utri.h>
#include <EDK3/dev/gpumanager.h>

UTRI::TextureCustom::TextureCustom()
{
	id_texture_ = -1;
	glGenTextures(1, &id_texture_);
}

UTRI::TextureCustom::~TextureCustom()
{
	if (-1 != id_texture_) {
		glDeleteTextures(1, &id_texture_);
	}
}

void UTRI::TextureCustom::set_data(const Format f, const EDK3::Type t, const void * data, unsigned int mipmap_LOD)
{
	bind(0);
	switch (type()) {
	case T_1D:
		glTexImage1D(ConvertType(type()), mipmap_LOD, ConvertFormat(f), width(), 0, ConvertFormat(f), EDK3::dev::GPUManager::ConvertEDK3Type(t), data);
		break;
	case T_2D:
		glTexImage2D(ConvertType(type()), mipmap_LOD, ConvertFormat(f), width(), height(), 0, ConvertFormat(f), GPUManagerCustom::ConvertEDK3Type(t), data);
		break;
	case T_3D:
		glTexImage3D(ConvertType(type()), mipmap_LOD, ConvertFormat(f), width(), height(), depth(), 0, ConvertFormat(f), GPUManagerCustom::ConvertEDK3Type(t), data);
		break;
	}
	generateMipmaps();
}

void UTRI::TextureCustom::bind(unsigned int textUnit) const
{
	glActiveTexture(GL_TEXTURE0 + textUnit);
	glBindTexture(ConvertType(type()), id_texture_);
}

unsigned int UTRI::TextureCustom::internal_id() const
{
	return id_texture_;
}

void UTRI::TextureCustom::set_min_filter(Filter f)
{
	EDK3::Texture::set_min_filter(f);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_MIN_FILTER, GL_NEAREST + f);
}

void UTRI::TextureCustom::set_mag_filter(Filter f)
{
	EDK3::Texture::set_mag_filter(f);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_MAG_FILTER, GL_NEAREST + f);
}

void UTRI::TextureCustom::set_wrap_s(Wrap c)
{
	EDK3::Texture::set_wrap_s(c);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_WRAP_S, ConvertWrap(c));
}

void UTRI::TextureCustom::set_wrap_t(Wrap c)
{
	EDK3::Texture::set_wrap_t(c);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_WRAP_T, ConvertWrap(c));
}

void UTRI::TextureCustom::set_wrap_r(Wrap c)
{
	EDK3::Texture::set_wrap_r(c);
	glTexParameteri(ConvertType(type()), GL_TEXTURE_WRAP_R, ConvertWrap(c));
}

void UTRI::TextureCustom::generateMipmaps() const
{
	glGenerateMipmap(ConvertType(type()));
}

GLenum UTRI::TextureCustom::ConvertType(Type t) const {
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

GLint UTRI::TextureCustom::ConvertWrap(Wrap c) const {
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

GLenum UTRI::TextureCustom::ConvertFormat(Format t) const {
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

void UTRI::TextureCustom::initTexture(Type t, Format internal_format, unsigned int width, unsigned int height, unsigned int depth)
{
	init(t, internal_format, width, height, depth);
}
