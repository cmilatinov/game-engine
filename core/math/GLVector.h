#pragma once

#include <iostream>
#include <iomanip>
#include "GLMath.h"


namespace glmath {

	//========================== Data Types =================================

	union vec2 {
		vec2();
		vec2(float value);
		vec2(float x, float y);
	
		struct { float x, y; };
		struct { float s, t; };
		float v[2];

		float length() const;
		
		vec2 normalize();
		vec2 normalize(vec2 * dest);

		vec2 friend operator+(const vec2& left, const vec2& right);
		vec2 friend operator-(const vec2& left, const vec2& right);

		void operator+=(const vec2& right);
		void operator-=(const vec2& right);

		vec2 friend operator*(const float& left, const vec2& right);
		vec2 friend operator*(const vec2& left, const float& right);

		vec2 friend operator/(const vec2& left, const float& right);
		
		friend std::ostream& operator<<(std::ostream &left, const vec2& right);
	};

	union vec3 {
		vec3();
		vec3(float value);
		vec3(float x, float y, float z);
		
		struct { float x, y, z; };
		struct { float r, g, b; };
		float v[3];
	
		float length() const;

		vec3 normalize();
		vec3 normalize(vec3 * dest);

		vec3 friend operator+(const vec3& left, const vec3& right);
		vec3 friend operator-(const vec3& left, const vec3& right);
		
		void operator+=(const vec3& right);
		void operator-=(const vec3& right);

		vec3 friend operator*(const float& left, const vec3& right);
		vec3 friend operator*(const vec3& left, const float& right);

		vec3 friend operator/(const vec3& left, const float& right);

		friend std::ostream& operator<<(std::ostream &left, const vec3& right);
	};

	union vec4 {
		vec4();
		vec4(float value);
		vec4(float x, float y, float z, float w);

		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
		float v[4];

		float length() const;

		vec4 normalize();
		vec4 normalize(vec4 * dest);

		vec4 friend operator+(const vec4& left, const vec4& right);
		vec4 friend operator-(const vec4& left, const vec4& right);

		void operator+=(const vec4& right);
		void operator-=(const vec4& right);

		vec4 friend operator*(const float& left, const vec4& right);
		vec4 friend operator*(const vec4& left, const float& right);

		vec4 friend operator/(const vec4& left, const float& right);

		friend std::ostream& operator<<(std::ostream &left, const vec4& right);
	};

	//===================== Namespace Functions =============================
	
	vec2 normalize(vec2 * src, vec2 * dest);
	vec3 normalize(vec3 * src, vec3 * dest);
	vec4 normalize(vec4 * src, vec4 * dest);

	vec3 cross(const vec2& left, const vec2& right);
	vec3 cross(const vec3& left, const vec3& right);
	
	float dot(const vec2& left, const vec2& right);
	float dot(const vec3& left, const vec3& right);
	float dot(const vec4& left, const vec4& right);

	float angle(const vec2& left, const vec2& right);
	float angle(const vec3& left, const vec3& right);

	vec4 nlerp(vec4 a, vec4 b, float blend);

}