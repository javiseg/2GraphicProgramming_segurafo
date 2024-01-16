#pragma once

#include <EDK3/dev/shader.h>
#include <EDK3/ref_ptr.h>
#include <EDK3/dev/opengl.h>


namespace JSF {


	class JSFShader : public EDK3::dev::Shader {

	public:

		virtual void loadSource(const EDK3::dev::Shader::Type shader_type, const char* source, const unsigned int source_size) override;
		virtual bool compile(EDK3::scoped_array<char>* output_log) override;
		virtual bool is_compiled() const override;

		virtual const EDK3::dev::Shader::Type type() const override;
		
		virtual unsigned int internal_id() const override;

	protected:
		JSFShader();
		virtual ~JSFShader();

	private:
		GLuint shad_id_;


		friend class EDK3::ref_ptr<EDK3::dev::Shader>;
	};
}
