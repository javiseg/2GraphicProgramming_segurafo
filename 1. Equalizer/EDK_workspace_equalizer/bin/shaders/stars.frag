#version 330

 out vec4 fragColor;

 in vec3 normal;
 uniform vec4 color;
 uniform vec4 patata;
vec3 lightRay;
float dotR;

void main()
{
	
	fragColor = vec4(color.x/255,color.y/255, color.z/255, color.w); 
}
