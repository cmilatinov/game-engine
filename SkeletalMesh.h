#include <string>

#include "GLMatrix.h"
#include "Mesh.h"

using namespace glmath;
using std::string;
using std::vector;

#pragma once
struct Joint {
	string name;
	mat4 offset;
	vector<Joint*> children;
};

class SkeletalMesh : public Mesh {
	
	friend class Loader;

	private: 

		Joint root;
			
	
		SkeletalMesh(VAO * vao, unsigned int vertexCount, Joint root);
	
	public:
		~SkeletalMesh();

};

