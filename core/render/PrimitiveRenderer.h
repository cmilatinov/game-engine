#include <map>
#include <vector>
#include <glad/glad.h>

#include "../shaders/PrimitiveShader.h"
#include "../objects/Primitive.h"
#include "../camera/Camera.h"

#pragma once
class PrimitiveRenderer
{
private:
	unsigned int vaoID, vertexVboID, colorVboID;


	PrimitiveShader * shader;

	void beginRender(Camera * cam);
	void endRender();

public:
	PrimitiveRenderer();
	~PrimitiveRenderer();

	void render(Camera * cam, std::map<GLenum, std::vector<Primitive *>> & primitives);
};

