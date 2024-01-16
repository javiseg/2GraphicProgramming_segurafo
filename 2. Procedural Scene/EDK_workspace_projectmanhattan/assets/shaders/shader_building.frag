#version 330

uniform float u_time;
uniform sampler2D texture_albedo;
uniform sampler2D texture_spec;
uniform vec3 u_camera_position;
uniform float far;
uniform float directional_intensity;
uniform vec3 patrol_position;

out vec4 fragColor;
 
in vec3 normal;
in float time;
in vec3 world_pos;
in vec2 uvs_;


struct Directional{

	vec3 direction;
	vec3 color;
	float intensity;
};

struct PointLight{

	vec3 position;
	vec3 color;
	float intensity;
	float range;

};

struct SpotLight{

	vec3 position;
	vec3 direction;
	vec3 color;
	float intensity;
	float range;
	float radius;

};
/*
vec3 DiffuseLight(DirectionalLight light, Model model)
{
	float diff = max(dot(model.normal, light.direction), 0.0);
	float multiplier = step(model.material.diffuse.limit, diff);
	diff *= multiplier;
	vec3 diffuse = diff * light.color;
	
	return diffuse;
}

vec3 SpecularLight(DirectionalLight light, Model model, View view)
{
	vec3 reflect_dir = reflect(normalize(light.direction), model.normal);
	
	float spec = pow(max(dot(normalize(view.direction), reflect_dir), 0.0), 256);
	vec3 specular = model.material.specular.specularity * spec * light.color;
	
	return specular;
}

void CalculateLighting(DirectionalLight light, Model model, View view, inout Lighting lighting)
{
	model.normal = normalize(model.normal);
	
	lighting.diffuse += DiffuseLight(light, model);
	lighting.specular += SpecularLight(light, model, view);
}*/

void main() 
{
	float near = 0.01;

	float z_ndc = gl_FragCoord.z * 2.0 - 1.0;
	float depth = (2.0 * near * far) / (far + near - z_ndc * (far - near));
	depth/=-far;

	Directional directional_light;
	directional_light.color = vec3(1.0);
	directional_light.direction = normalize(vec3(0.0,-1.0,0.0));

	directional_light.intensity = directional_intensity;

	PointLight pointlight;
	pointlight.color = vec3(1.0,0.0,1.0);
	pointlight.position = patrol_position;
	pointlight.range = 500.0;
	pointlight.intensity = 1.0;


	SpotLight spotlight;
	spotlight.position = vec3(600.0,150.0, 1000.0);
	spotlight.direction = normalize(vec3(0.0,-1.0,0.0));
	spotlight.color = vec3(0.0,1.0,0.0);
	spotlight.intensity = 1.0;
	spotlight.range = 50.0;
	spotlight.radius = 1.1;

	SpotLight spotlights[10];
	for(int i = 0; i < 10; i++){
		spotlights[i] = spotlight;
		spotlights[i].position = vec3(600.0,150.0, i*500.0);
	}
	SpotLight spotlights_left[10];
	for(int i = 0; i < 10; i++){
		spotlights_left[i] = spotlight;
		spotlights_left[i].position = vec3(20.0,150.0, i*500.0);
	}
	SpotLight spotlights_right[10];
	for(int i = 0; i < 10; i++){
		spotlights_right[i] = spotlight;
		spotlights_right[i].position = vec3(1200.0,150.0, i*500.0);
		spotlights_right[i].color = vec3(1.0,0.0,0.0);
	}

	SpotLight spotlight2 = spotlight;
	spotlight2.position = vec3(600.0,150.0, 100.0);
	spotlight2.color = vec3(1.0,0.0,0.0);

	vec3 view_dir = world_pos - u_camera_position;
	SpotLight spotlight_player;
	spotlight_player.position = u_camera_position;
	spotlight_player.direction = normalize(vec3(1.0,1.0,1.0));
	spotlight_player.color = vec3(0.0,0.0,1.0);
	spotlight_player.intensity = 1.0;
	spotlight_player.range = 850.0;
	spotlight_player.radius = 10.5;


	vec4 texture_color = texture(texture_albedo, uvs_);
	//float texture_specular = texture(texture_spec, uvs_).r;
	float texture_specular = 1.0;



	vec3 result = vec3(0.1);
	vec3 normalized_normal = normalize(normal);
	
	// Directional diffuse calculations

	float diffuse = -dot(normalized_normal, directional_light.direction);
	diffuse = max(diffuse, 0.0);

	vec3 reflection = reflect(directional_light.direction, normalized_normal);

	
	view_dir = normalize(view_dir);

	float specular = max(-dot(view_dir,reflection), 0.0);


	result += (diffuse + specular * texture_specular) * directional_light.color * directional_light.intensity;


	// Pointlight 

	vec3 light_dir = world_pos - pointlight.position;
	float lightlength = length(light_dir);
	light_dir /= lightlength;
	diffuse = max(-dot(light_dir,normalized_normal), 0.0);
	reflection = reflect(light_dir, normalized_normal);

	specular = max(-dot(reflection,view_dir), 0.0);

	float atenuation = 1.0 - min(lightlength/pointlight.range, 1.0);


	result += (diffuse) * pointlight.color * pointlight.intensity * atenuation;


	// Spotlight 1

	light_dir = world_pos - spotlight.position;
	lightlength = length(light_dir);
	light_dir /= lightlength;
	diffuse = max(-dot(spotlight.direction,normalized_normal), 0.0);
	reflection = reflect(spotlight.direction, normalized_normal);

	specular = max(-dot(reflection,view_dir), 0.0);

	
	float angle = dot(spotlight.direction, light_dir);
	float epsilon = 0.97f - 0.91f;

	atenuation = clamp((angle-0.91f) / epsilon, 0.0,1.0);
	result += diffuse * spotlight.color * spotlight.intensity * atenuation;

	// Spotlight 2

	light_dir = world_pos - spotlight2.position;
	lightlength = length(light_dir);
	light_dir /= lightlength;
	diffuse = max(-dot(spotlight2.direction,normalized_normal), 0.0);
	reflection = reflect(spotlight2.direction, normalized_normal);

	specular = max(-dot(reflection,view_dir), 0.0);

	
	angle = dot(spotlight2.direction, light_dir);
	epsilon = 0.97f - 0.91f;

	atenuation = clamp((angle-0.91f) / epsilon, 0.0,1.0);
	result += diffuse * spotlight2.color * spotlight2.intensity * atenuation;

	
	for(int i = 0; i < 10; i++){
	
		light_dir = world_pos - spotlights[i].position;
		lightlength = length(light_dir);
		light_dir /= lightlength;
		diffuse = max(-dot(spotlights[i].direction,normalized_normal), 0.0);
		reflection = reflect(spotlights[i].direction, normalized_normal);

		specular = max(-dot(reflection,view_dir), 0.0);

	
		angle = dot(spotlights[i].direction, light_dir);
		epsilon = 0.97f - 0.91f;

		atenuation = clamp((angle-0.91f) / epsilon, 0.0,1.0);
		result += diffuse * spotlights[i].color * spotlights[i].intensity * atenuation;
		
	}

	for(int i = 0; i < 10; i++){
	
		light_dir = world_pos - spotlights_left[i].position;
		lightlength = length(light_dir);
		light_dir /= lightlength;
		diffuse = max(-dot(spotlights_left[i].direction,normalized_normal), 0.0);
		reflection = reflect(spotlights_left[i].direction, normalized_normal);

		specular = max(-dot(reflection,view_dir), 0.0);

	
		angle = dot(spotlights_left[i].direction, light_dir);
		epsilon = 0.97f - 0.91f;

		atenuation = clamp((angle-0.91f) / epsilon, 0.0,1.0);
		result += diffuse * spotlights_left[i].color * spotlights_left[i].intensity * atenuation;
		
	}

	for(int i = 0; i < 10; i++){
	
		light_dir = world_pos - spotlights_right[i].position;
		lightlength = length(light_dir);
		light_dir /= lightlength;
		diffuse = max(-dot(spotlights_right[i].direction,normalized_normal), 0.0);
		reflection = reflect(spotlights_right[i].direction, normalized_normal);

		specular = max(-dot(reflection,view_dir), 0.0);

	
		angle = dot(spotlights_right[i].direction, light_dir);
		epsilon = 0.97f - 0.91f;

		atenuation = clamp((angle-0.91f) / epsilon, 0.0,1.0);
		result += diffuse * spotlights_right[i].color * spotlights_right[i].intensity * atenuation;
		
	}

	// Spotlight Player

	light_dir = world_pos - spotlight_player.position;
	lightlength = length(light_dir);
	light_dir /= lightlength;
	diffuse = max(-dot(spotlight_player.direction,normalized_normal), 0.0);
	reflection = reflect(spotlight_player.direction, normalized_normal);

	specular = max(-dot(reflection,view_dir), 0.0);

	
	angle = dot(spotlight_player.direction, light_dir);
	epsilon = 0.97f - 0.91f;

	atenuation = clamp((angle-0.91f) / epsilon, 0.0,1.0);
	result += diffuse * spotlight_player.color * spotlight_player.intensity * atenuation;



	vec3 finalresult = texture_color.rgb * result + depth;
	fragColor = vec4(finalresult,1.0);
}