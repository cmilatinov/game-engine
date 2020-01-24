#include <vector>

#include <glad/glad.h>

#include "../math/GLVector.h"

using namespace glmath;
using std::vector;

#pragma once
class Primitive {

	private:
		unsigned int type;

		vector<vec3> points;
		vec3 color;

	public:
		Primitive(unsigned int type, vector<vec3> & points, vec3 color);
		~Primitive();
		
		Primitive * setType(unsigned int type);
		Primitive * setColor(vec3 color);
		Primitive * setPoints(vector<vec3> & points);

		vec3 getColor();
		vec3 * getPoints();
		unsigned int getSize();
		GLenum getType();

};

