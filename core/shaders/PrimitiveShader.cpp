#include "PrimitiveShader.h"

const char * PrimitiveShader::VERTEX_FILE = "PrimitiveShaderVertex.glsl";
const char * PrimitiveShader::FRAGMENT_FILE = "PrimitiveShaderFragment.glsl";

PrimitiveShader::PrimitiveShader() : Shader(VERTEX_FILE, FRAGMENT_FILE){
	validate();
}

PrimitiveShader::~PrimitiveShader(){}


void PrimitiveShader::bindAttributes() {
	bindAttribute(0, "pos");
	bindAttribute(1, "color");
}

void PrimitiveShader::getUniformLocations() {
	location_projViewMatrix = getUniformLocation("projViewMatrix");
	location_uniformColor = getUniformLocation("uniformColor");
	location_useUniformColor = getUniformLocation("useUniformColor");
}