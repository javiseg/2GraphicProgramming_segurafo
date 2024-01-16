#include "JSFShader.h"

JSF::JSFShader::JSFShader()
{
	shad_id_ = -1;
}

JSF::JSFShader::~JSFShader()
{
	if (-1 != shad_id_) {

		glDeleteShader(shad_id_);

	}
}

void JSF::JSFShader::loadSource(const Type shader_type, const char* source, const unsigned int source_size)
{
	int size = static_cast<int>(source_size);

	if (-1 != shad_id_) {

		glDeleteShader(shad_id_);

	}

	switch (shader_type)
	{
	case kType_Vertex:

			shad_id_ = glCreateShader(GL_VERTEX_SHADER);
		break;

	case kType_Fragment:

			shad_id_ = glCreateShader(GL_FRAGMENT_SHADER); 
		break;
	case kType_Geometry:
			
			shad_id_ = glCreateShader(GL_GEOMETRY_SHADER); 
		break;
	case kType_Invalid:
			printf("Invalid Type"); 
		break;

	default: 
		break;
	}

	glShaderSource(shad_id_, 1, &source, &size);
}

bool JSF::JSFShader::compile(EDK3::scoped_array<char>* output_log)
{
	GLint loglen = 0;

	glCompileShader(shad_id_);

	if (output_log != nullptr) {
		glGetShaderiv(shad_id_, GL_INFO_LOG_LENGTH, &loglen);
		output_log->alloc(loglen);

		glGetShaderInfoLog(shad_id_, loglen, &loglen, output_log->get());
	}

	return is_compiled();
}

bool JSF::JSFShader::is_compiled() const
{
	GLint shadercompiled;

	glGetShaderiv(shad_id_, GL_COMPILE_STATUS, &shadercompiled);

	return shadercompiled == GL_TRUE;
}

const EDK3::dev::Shader::Type JSF::JSFShader::type() const
{
	GLint type_;
	glGetShaderiv(shad_id_, GL_SHADER_TYPE, &type_);
	switch (type_){

	case GL_VERTEX_SHADER:
			return kType_Vertex; 
		break;

	case GL_FRAGMENT_SHADER:
			return kType_Fragment; 
		break;

	case GL_GEOMETRY_SHADER:
			return kType_Geometry; 
		break;
	}
	return kType_Invalid;
}

unsigned int JSF::JSFShader::internal_id() const
{
	return shad_id_;
}

