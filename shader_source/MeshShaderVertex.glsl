#version 400 core

const int MAX_JOINTS = 50;
const int MAX_WEIGHTS = 3;

in vec3 pos;
in vec3 normal;
in vec2 uv;
in uvec3 jointIDs;
in vec3 weights;

out vec2 pass_uv;

uniform mat4 projViewMatrix;
uniform mat4 modelMatrix;

uniform mat4 jointTransforms[MAX_JOINTS];

uniform bool animated;

void main(void){
	
	vec4 totalPos = vec4(0);
	vec4 totalNormal = vec4(0);

	// Calculate position and normal based on current pose
	if(animated) {
		for (int i = 0; i < MAX_WEIGHTS; i++) {
			mat4 transform = jointTransforms[jointIDs[i]];
			totalPos += weights[i] * transform * vec4(pos, 1.0);
			totalNormal = weights[i] * transform * vec4(normal, 0.0);
		}
	} else {
		totalPos = vec4(pos, 1.0);
		totalNormal = vec4(normal, 0.0);
	}

	// Set world position
	gl_Position = projViewMatrix * modelMatrix * totalPos;

	// Pass the texture coordinates to fragment shader
	pass_uv = uv;

}