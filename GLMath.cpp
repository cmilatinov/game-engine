#include "GLMath.h"
#include <iostream>

std::ostringstream ss;

float glmath::rad(float degrees){
	return degrees * (float)PI / 180.0f;
}

float glmath::deg(float radians){
	return radians * 180.0f / (float) PI;
}

float glmath::fovy(float fovx, float aspect){
	return atan(tan(fovx / 2) / aspect) * 2;
}

std::string glmath::centered(float value, unsigned int size) {
	ss << std::setprecision(6) << value;
	std::string strVal = ss.str();

	ss.str("");
	ss.clear();

	size_t len = strVal.length();

	return std::string((size_t)(((size - len) / 2.0) + 0.5), ' ') + strVal + std::string((size - len) / 2, ' ');
}
