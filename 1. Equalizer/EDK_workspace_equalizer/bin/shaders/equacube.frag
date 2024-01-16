#version 330

 out vec4 fragColor;

 in vec3 normal;
 uniform vec4 color;
vec3 lightRay;
float dotR;

in vec3 a_coord;

void main()
{
	fragColor = color;
	if(a_coord.y <= -7){

		float change_value = clamp(abs(a_coord.y), 7, 20);
		change_value = change_value - 7;
		change_value = change_value / 15;
		fragColor = vec4(color.x / 255.0,(color.y / 255.0) + change_value,color.z  / 255.0, 0.7); 
	}else{
		float change_value = clamp(a_coord.y, -7, 20);
		change_value = change_value + 7;
		change_value = change_value / 15;

		fragColor = vec4(color.x / 255.0,(color.y / 255.0) + change_value,color.z  / 255.0, color.w);
	}
		
	

	
	
}
