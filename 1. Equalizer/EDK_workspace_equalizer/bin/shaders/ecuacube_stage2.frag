#version 330

 out vec4 fragColor;

 in vec3 normal;
 uniform vec4 color;
 uniform vec4 patata;
vec3 lightRay;
float dotR;

void main()
{
	vec4 inverse_color;
    inverse_color.x = 1 - color.x;
    inverse_color.y = 1 - color.y;
    inverse_color.z = 1 - color.z;
    inverse_color.w = color.w;

	float setX = 256;
    float setY = 144;

    float offsetX = 0;
    float offsetY = 0;
    
    int resultX = int(gl_FragCoord.x/setX);
    int resultY = int(gl_FragCoord.y/setY);
    int result = resultX + resultY;

    float rect = result - (2 * floor(float(result)/float(2)));


  if(rect == 0){
    if(color.w == 0){
      fragColor = vec4(0.6 * color.x, 1.0 * color.y, 0.0 * color.z, 1);
    }else{
      fragColor = vec4(0.9 * color.x, 0 * color.y, 1.0 * color.z, 1);
  }
        
  }else{
    if(color.w == 0){
      fragColor = vec4(1.0 * inverse_color.x, 1.0 * inverse_color.y, 0.0 * inverse_color.z, 1);
    }else{
      fragColor = vec4(0.0 * inverse_color.x, 1 * inverse_color.y, 1.0 * inverse_color.z, 1);
    }
  }



}
