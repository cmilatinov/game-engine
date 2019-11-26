#version 400 core

in vec3 pos;
in vec3 normal;
in vec2 uv;

out vec3 pass_pos;
out vec3 pass_normal;
out vec2 pass_uv;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;

void main(void){
	gl_Position = projViewMatrix * modelMatrix * vec4(pos, 1);

	pass_pos = pos;
	pass_normal = normal;
	pass_uv = uv;
}