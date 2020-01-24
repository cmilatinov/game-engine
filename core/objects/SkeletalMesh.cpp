#include "SkeletalMesh.h"

SkeletalMesh::SkeletalMesh(VAO * vao, unsigned int vertexCount, Animator * animator) : Mesh(vao, vertexCount) {
	this->anim = animator;
}

SkeletalMesh::~SkeletalMesh(){

}

