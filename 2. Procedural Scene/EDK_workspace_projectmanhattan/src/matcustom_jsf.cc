#include "../include/matcustom_jsf.h"
#include "../include/ESAT/math.h"
#include "../include/math/matrix_4.h"
#include <EDK3/dev/gpumanager.h>
#include "Singleton.h"

bool MatCustomJSF::enable(const EDK3::MaterialSettings *mat_set) const {
	const EDK3::dev::Program* program_ = get_program();
	program_->use();

	int color = program_->get_uniform_position("color");
	const Settings* set = static_cast<const Settings*>(mat_set);
	program_->set_uniform_value(color, EDK3::Type::T_FLOAT_4, set->color());


	int slot = 0;
	if (set->albedo.get()) {
		set->albedo->bind(slot);
		program_->set_uniform_value(program_->get_uniform_position("texture_albedo"),
			EDK3::Type::T_INT, &slot);
	}
	Singleton* s = Singleton::getInstance();
	
	program_->set_uniform_value(program_->get_uniform_position("far"),
		EDK3::Type::T_FLOAT, &s->FarDistance);

	program_->set_uniform_value(program_->get_uniform_position("directional_intensity"),
		EDK3::Type::T_FLOAT, &s->DirectionalIntensity);

	program_->set_uniform_value(program_->get_uniform_position("patrol_position"),
		EDK3::Type::T_FLOAT_3, &s->patrol_position.x);


	return true;
}

void MatCustomJSF::setupCamera(const float projecton[16], const float view[16]) const {
	
	Matix4x4 proj_ = Matix4x4(projecton);
	Matix4x4 view_ = Matix4x4(view);
	Matix4x4 camera_mat_ = view_.Multiply(proj_);
	Vector3 cam_pos = Vector3(view_.m + 12);
	
	int projection_mat = get_program()->get_uniform_position("u_vp_matrix");
	get_program()->set_uniform_value(projection_mat, EDK3::Type::T_MAT_4x4, camera_mat_.m);
	int position_camera = get_program()->get_uniform_position("u_camera_position");
	get_program()->set_uniform_value(position_camera, EDK3::Type::T_FLOAT_3, &cam_pos.x);
}
void MatCustomJSF::setupModel(const float m[16]) const {
	int model_mat = get_program()->get_uniform_position("u_m_matrix");
	get_program()->set_uniform_value(model_mat, EDK3::Type::T_MAT_4x4, m);
}

unsigned int MatCustomJSF::num_attributes_required() const {
	return 3;
}

EDK3::Attribute MatCustomJSF::attribute_at_index(const unsigned int attrib_idx) const {
	if (attrib_idx == 0) {
		return EDK3::Attribute::A_POSITION;
	}
	if (attrib_idx == 1) {
		return EDK3::Attribute::A_NORMAL;
	}
	if (attrib_idx == 2) {
		return EDK3::Attribute::A_UV;
	}
}

EDK3::Type MatCustomJSF::attribute_type_at_index(const unsigned int attrib_index) const
{
    return EDK3::Type();
}

bool MatCustomJSF::load_shaders(EDK3::ref_ptr<JSF::JSFShader> vertex_shader, EDK3::ref_ptr<JSF::JSFShader> fragment_shader) {
	
	EDK3::scoped_array<char> output_log;

	vertex_shader->compile(&output_log);
	fragment_shader->compile(&output_log);

	EDK3::ref_ptr<EDK3::dev::Program> program_;
	EDK3::dev::GPUManager::Instance()->newProgram(&program_);
	set_program(program_);

	program_->attach(vertex_shader.get());
	program_->attach(fragment_shader.get());

	return program_->link();
}

bool MatCustomJSF::load_shaders_from_filepaths(const char* vert_shader_path, const char* frag_shader_path)
{
	EDK3::ref_ptr<EDK3::dev::Shader> vertex_shader;
	EDK3::ref_ptr<EDK3::dev::Shader> fragment_shader;

	EDK3::dev::GPUManager::Instance()->newProgram(&program_);
	EDK3::dev::GPUManager::Instance()->newShader(&vertex_shader);
	EDK3::dev::GPUManager::Instance()->newShader(&fragment_shader);
	
	
	loadFragmentShaderFile(&fragment_shader, frag_shader_path);
	loadVertexShaderFile(&vertex_shader, vert_shader_path);


	//vertex_shader->loadSource(EDK3::dev::Shader::Type::kType_Vertex, shader1_path, sizeof(shader1_path));
	//fragment_shader->loadSource(EDK3::dev::Shader::Type::kType_Fragment, shader2_path, sizeof(shader2_path));

	if (!vertex_shader->compile()) {
		printf("\nVertex compiled not ok \n");
	}
	if (!fragment_shader->compile()) {
		printf("\Fragment compiled not ok \n");
	}
	set_program(program_);

	program_->attach(vertex_shader.get());
	program_->attach(fragment_shader.get());

	return program_->link();
}

MatCustomJSF::~MatCustomJSF()
{
}

void MatCustomJSF::set_program(EDK3::ref_ptr<EDK3::dev::Program> program)
{
	program_ = program;
}

EDK3::dev::Program* MatCustomJSF::get_program()
{
	return program_.get();
}

const EDK3::dev::Program* MatCustomJSF::get_program() const
{
	return program_.get();
}

MatCustomJSF& MatCustomJSF::operator=(const MatCustomJSF&)
{
	// TODO: Insertar una instrucción "return" aquí
	return *this;
}
