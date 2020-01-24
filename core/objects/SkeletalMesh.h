#include <string>

#include "../math/GLMatrix.h"
#include "../objects/Mesh.h"
#include "../animation/Animation.h"

using namespace glmath;
using std::string;
using std::vector;

class SkeletalMesh : public Mesh {
	
	friend class Loader;

	private: 
		Animator * anim;
	
		SkeletalMesh(VAO * vao, unsigned int vertexCount, Animator * animator);
	
	public:
		~SkeletalMesh();

		inline Animator * animator() { return anim; };

};

