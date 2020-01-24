#include "Primitive.h"

Primitive::Primitive(unsigned int type, vector<vec3> & points, vec3 color) :
	type(type),
	points(points),
	color(color) {}

Primitive::~Primitive() {}

Primitive * Primitive::setType(unsigned int type) {
	this->type = type;
	return this;
}

Primitive * Primitive::setColor(vec3 color) {
	this->color = color;
	return this;
}

Primitive * Primitive::setPoints(vector<vec3> & points) {
	this->points = points;
	return this;
}

vec3 Primitive::getColor() {
	return color;
}

vec3 * Primitive::getPoints() {
	return points.data();
}

unsigned int Primitive::getSize() {
	return points.size();
}

GLenum Primitive::getType() {
	return type;
}