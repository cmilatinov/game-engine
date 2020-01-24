#include "MeshShader.h"

const char * MeshShader::VERTEX_FILE = "MeshShaderVertex.glsl";
const char * MeshShader::FRAGMENT_FILE = "MeshShaderFragment.glsl";

MeshShader::MeshShader() : Shader(VERTEX_FILE, FRAGMENT_FILE) {
	validate();
}

MeshShader::~MeshShader() {}

void MeshShader::bindAttributes() {
	bindAttribute(0, "pos");
	bindAttribute(1, "normal");
	bindAttribute(2, "uv");
	bindAttribute(3, "jointIDs");
	bindAttribute(4, "weights");
}

void MeshShader::getUniformLocations() {
	location_projViewMatrix = getUniformLocation("projViewMatrix");
	location_modelMatrix = getUniformLocation("modelMatrix");
	location_jointTransforms = getUniformLocation("jointTransforms[0]");
	location_animated = getUniformLocation("animated");
	location_tex = getUniformLocation("tex");
}