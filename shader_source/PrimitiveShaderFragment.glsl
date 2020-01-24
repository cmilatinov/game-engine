#version 400 core

in vec3 pass_color;

uniform vec3 uniformColor;
uniform bool useUniformColor;

layout (location = 0) out vec4 finalColor;

void main(void){
	
	if(useUniformColor)
		finalColor = vec4(uniformColor, 1);
	else
		finalColor = vec4(pass_color, 1);

}