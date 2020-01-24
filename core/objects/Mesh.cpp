#include "Mesh.h"

Mesh::Mesh(VAO * vao, unsigned int vertexCount) {
	this->vao = vao;
	this->vertexCount = vertexCount;
}
Mesh::~Mesh() {
}