#pragma once

#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>

#define PI 3.14159265358979

namespace glmath {

	//===================== Namespace Functions =============================

	float rad(float degrees);
	float deg(float radians);

	float fovy(float fovx, float aspect = 16.0f / 9.0f);

	std::string centered(float value, unsigned int size);

}