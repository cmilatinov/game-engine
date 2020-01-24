#version 400 core

in vec3 pos;
in vec3 color;

out vec3 pass_color;

uniform mat4 projViewMatrix;

void main(void){

	pass_color = color;

	gl_Position = projViewMatrix * vec4(pos, 1);

}