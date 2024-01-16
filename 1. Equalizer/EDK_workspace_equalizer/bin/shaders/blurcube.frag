#version 330
 
out vec4 fragColor;
in vec4 gl_FragCoord;

void main()
{ 
    
	fragColor = vec4(gl_FragCoord.x/1280.0, gl_FragCoord.y/720.0, 1, 1);  
	
}