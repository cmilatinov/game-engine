#version 400 core

in vec3 pass_pos;
in vec3 pass_normal;
in vec2 pass_uv;

out vec4 color;

uniform sampler2D tex;

void main(void){
	color = texture(tex, pass_uv);
}