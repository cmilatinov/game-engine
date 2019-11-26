#include "GLVector.h"

#define NUM_LEN 14

namespace glmath {

	//=========================== VECTORS =============================
	
	vec2::vec2() {
		this->x = 0;
		this->y = 0;
	}
	vec2::vec2(float value) {
		this->x = value;
		this->y = value;
	}
	vec2::vec2(float x, float y) {
		this->x = x;
		this->y = y;
	}

	vec3::vec3() {
		this->x = 0;
		this->y = 0;
	}
	vec3::vec3(float value) {
		this->x = value;
		this->y = value;
		this->z = value;
	}
	vec3::vec3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	vec4::vec4() {
		this->x = 0;
		this->y = 0;
		this->z = 0;
		this->w = 0;
	}
	vec4::vec4(float value) {
		this->x = value;
		this->y = value;
		this->z = value;
		this->w = value;
	}
	vec4::vec4(float x, float y, float z, float w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	//========================= VECTOR FUNCS ==========================

	float vec2::length() const {
		return sqrt(pow(this->x, 2) + pow(this->y, 2));
	}
	float vec3::length() const {
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2));
	}
	float vec4::length() const {
		return sqrt(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2) + pow(this->w, 2));
	}

	vec2 vec2::normalize() {
		return normalize(this);
	}
	vec2 vec2::normalize(vec2 * dest) {
		return glmath::normalize(this, dest);
	}

	vec3 vec3::normalize() {
		return normalize(this);
	}
	vec3 vec3::normalize(vec3 * dest) {
		return glmath::normalize(this, dest);
	}

	vec4 vec4::normalize() {
		return normalize(this);
	}
	vec4 vec4::normalize(vec4 * dest) {
		return glmath::normalize(this, dest);
	}

	//======================= NAMESPACE FUNCS =========================

	vec2 normalize(vec2 * src, vec2 * dest) {
		if (src == nullptr)
			return vec2();

		if (dest == nullptr)
			dest = new vec2;

		float length = src->length();
		dest->x = src->x / length;
		dest->y = src->y / length;

		return *dest;
	}
	vec3 normalize(vec3 * src, vec3 * dest) {
		if (src == nullptr)
			return vec3();

		if (dest == nullptr)
			dest = new vec3;

		float length = src->length();
		dest->x = src->x / length;
		dest->y = src->y / length;
		dest->z = src->z / length;

		return *dest;
	}
	vec4 normalize(vec4 * src, vec4 * dest) {
		if (src == nullptr)
			return vec4();

		if (dest == nullptr)
			dest = new vec4;

		float length = src->length();
		dest->x = src->x / length;
		dest->y = src->y / length;
		dest->z = src->z / length;
		dest->w = src->w / length;

		return *dest;
	}

	vec3 cross(const vec2& left, const vec2& right) {
		return glmath::cross(vec3(left.x, left.y, 0.0f), vec3(right.x, right.y, 0.0));
	}
	vec3 cross(const vec3& left, const vec3& right) {
		return vec3(left.y * right.z - left.z * right.y, 
					right.x * left.z - right.z * left.x, 
					left.x * right.y - left.y * right.x);
	}

	float dot(const vec2& left, const vec2& right) {
		return left.x * right.x + left.y * right.y;
	}
	float dot(const vec3& left, const vec3& right) {
		return left.x * right.x + left.y * right.y + left.z * right.z;
	}
	float dot(const vec4& left, const vec4& right) {
		return left.x * right.x + left.y * right.y + left.z * right.z + left.w * right.w;
	}

	float angle(const vec2& left, const vec2& right) {
		return glmath::angle(vec3(left.x, left.y, 0), vec3(right.x, right.y, 0));
	}
	float angle(const vec3& left, const vec3& right) {
		return (float) acos(dot(left, right) / (left.length() * right.length()));
	}

	//========================== OPERATORS ============================

	vec2 operator+(const vec2& left, const vec2& right) {
		return vec2(left.x + right.x, left.y + right.y);
	}
	vec2 operator-(const vec2& left, const vec2& right) {
		return vec2(left.x - right.x, left.y - right.y);
	}
	void vec2::operator+=(const vec2& right) {
		this->x += right.x;
		this->y += right.y;
	}
	void vec2::operator-=(const vec2& right) {
		this->x -= right.x;
		this->y -= right.y;
	}
	vec2 operator*(const float& left, const vec2& right) {
		return vec2(left * right.x, left * right.y);
	}
	vec2 operator*(const vec2& left, const float& right) {
		return vec2(right * left.x, right * left.y);
	}
	vec2 operator/(const vec2& left, const float& right) {
		return vec2(left.x / right, left.y / right);
	}
	std::ostream& operator<<(std::ostream &left, const vec2 &right) {
		left << std::setprecision(6) << std::setfill(' ') << std::dec;
		left << char(218) << ' ' << centered(right.x, NUM_LEN) << ' ' << char(191) << std::endl;
		left << char(192) << ' ' << centered(right.y, NUM_LEN) << ' ' << char(217) << std::endl;
		return left;
	}

	vec3 operator+(const vec3& left, const vec3& right) {
		return vec3(left.x + right.x, left.y + right.y, left.z + right.z);
	}
	vec3 operator-(const vec3& left, const vec3& right) {
		return vec3(left.x - right.x, left.y - right.y, left.z - right.z);
	}
	void vec3::operator+=(const vec3& right) {
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;
	}
	void vec3::operator-=(const vec3& right) {
		this->x -= right.x;
		this->y -= right.y;
		this->z -= right.z;
	}
	vec3 operator*(const float& left, const vec3& right) {
		return vec3(left * right.x, left * right.y, left * right.z);
	}
	vec3 operator*(const vec3& left, const float& right) {
		return vec3(right * left.x, right * left.y, right * left.z);
	}
	vec3 operator/(const vec3& left, const float& right) {
		return vec3(left.x / right, left.y / right, left.z / right);
	}
	std::ostream& operator<<(std::ostream &left, const vec3 &right) {
		left << std::setprecision(6) << std::setfill(' ') << std::dec;
		left << char(218) << ' ' << centered(right.x, NUM_LEN) << ' ' << char(191) << std::endl;
		left << char(179) << ' ' << centered(right.y, NUM_LEN) << ' ' << char(179) << std::endl;
		left << char(192) << ' ' << centered(right.z, NUM_LEN) << ' ' << char(217) << std::endl;
		return left;
	}

	vec4 operator+(const vec4& left, const vec4& right) {
		return vec4(left.x + right.x, left.y + right.y, left.z + right.z, left.w + right.w);
	}
	vec4 operator-(const vec4& left, const vec4& right) {
		return vec4(left.x - right.x, left.y - right.y, left.z - right.z, left.w + right.w);
	}
	void vec4::operator+=(const vec4& right) {
		this->x += right.x;
		this->y += right.y;
		this->z += right.z;
		this->w += right.w;
	}
	void vec4::operator-=(const vec4& right) {
		this->x -= right.x;
		this->y -= right.y;
		this->z -= right.z;
		this->w -= right.w;
	}
	vec4 operator*(const float& left, const vec4& right) {
		return vec4(left * right.x, left * right.y, left * right.z, left * right.w);
	}
	vec4 operator*(const vec4& left, const float& right) {
		return vec4(right * left.x, right * left.y, right * left.z, right * left.w);
	}
	vec4 operator/(const vec4& left, const float& right) {
		return vec4(left.x / right, left.y / right, left.z / right, left.w / right);
	}
	std::ostream& operator<<(std::ostream &left, const vec4 &right) {
		left << std::setprecision(6) << std::setfill(' ') << std::dec;
		left << char(218) << ' ' << centered(right.x, NUM_LEN) << ' ' << char(191) << std::endl;
		left << char(179) << ' ' << centered(right.y, NUM_LEN) << ' ' << char(179) << std::endl;
		left << char(179) << ' ' << centered(right.z, NUM_LEN) << ' ' << char(179) << std::endl;
		left << char(192) << ' ' << centered(right.w, NUM_LEN) << ' ' << char(217) << std::endl;
		return left;
	}
}