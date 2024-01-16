#ifndef __MAT_CUSTOM_MONTEAL__
#define __MAT_CUSTOM_MONTEAL__ 1

#include <EDK3/material.h>
#include <EDK3/materialsettings.h>
#include <EDK3/ref_ptr.h>
#include <EDK3/dev/shader.h>
#include <EDK3/dev/program.h>
#include <EDK3/dev/gpumanager.h>
#include <EDK3/texture.h>
#include "JSFShader.h"


class MatCustomJSF : public EDK3::Material {
		public:

			MatCustomJSF() {}

			virtual bool enable(const EDK3::MaterialSettings *mat_set) const override;
			virtual void setupCamera(const float projecton[16], const float view[16]) const override;
			virtual void setupModel(const float m[16]) const override;
			virtual unsigned int num_attributes_required() const override;
			virtual EDK3::Attribute attribute_at_index(const unsigned int attrib_idx) const override;
			virtual EDK3::Type attribute_type_at_index(const unsigned int attrib_index) const override;
			virtual bool load_shaders(EDK3::ref_ptr<JSF::JSFShader> vertex_shader, EDK3::ref_ptr<JSF::JSFShader> fragment_shader);
			virtual bool load_shaders_from_filepaths(const char* shader1_path, const char* shader2_path);

			class Settings : public EDK3::MaterialSettings {
			public:
				Settings()
				{
					for (int i = 0; i < 4; ++i) {
						color_data[i] = 1.0f;
						custom_data_[i] = 01.0f;
					}
					
				}
				void set_color(const float v[4]) { memcpy(color_data, v, sizeof(color_data)); }
				void set_color(float r, float g, float b, float a = 1.0f) {
					color_data[0] = r; color_data[1] = g; color_data[2] = b; color_data[3] = a;
				}
				const float* color() const { return color_data; }

				
				void set_custom_data(const float data[4]) { memcpy(custom_data_, data, sizeof(custom_data_)); }
				const float* custom_data() const { return custom_data_; }

				EDK3::ref_ptr<EDK3::Texture> albedo;
				EDK3::ref_ptr<EDK3::Texture> specular;

			protected:
				virtual ~Settings() {}
			private:
				Settings(const Settings&);
				Settings& operator=(const Settings&);
				float color_data[4];
				float custom_data_[4];


			};

		protected:
			virtual ~MatCustomJSF();
			void set_program(EDK3::ref_ptr<EDK3::dev::Program> program);
			EDK3::dev::Program* get_program();
			const EDK3::dev::Program* get_program() const;
		private:
			EDK3::ref_ptr<EDK3::dev::Program> program_;
			MatCustomJSF(const MatCustomJSF&);
			MatCustomJSF& operator=(const MatCustomJSF&);
};

#endif