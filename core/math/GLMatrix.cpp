#include "GLMatrix.h"

#define NUM_LEN 14

namespace glmath {

	//======================== Constructors =================================

	mat4::mat4() {
		*this = Mat4Identity;
	}
	mat4::mat4( float m00, float m01, float m02, float m03,
				float m10, float m11, float m12, float m13,
				float m20, float m21, float m22, float m23,
				float m30, float m31, float m32, float m33) {
		this->m00 = m00;
		this->m01 = m01;
		this->m02 = m02;
		this->m03 = m03;
		this->m10 = m10;
		this->m11 = m11;

		this->m12 = m12;
		this->m13 = m13;
		this->m20 = m20;
		this->m21 = m21;
		this->m22 = m22;
		this->m23 = m23;
		this->m30 = m30;
		this->m31 = m31;
		this->m32 = m32;
		this->m33 = m33;
	}
	mat4::mat4(const float * arr, const int &arrSize) {
		memcpy_s(this->m, sizeof(mat4), arr, arrSize);
		memset(this->m + arrSize, NULL, sizeof(mat4) - arrSize * sizeof(float));
	}

	//========================= Operators ===================================

	mat4 operator+(const mat4 &left, const mat4 &right) {
		mat4 result = left;
		for (int i = 0; i < sizeof(mat4) / sizeof(float); i++)
			result.m[i] += right.m[i];
		return result;
	}
	mat4 operator-(const mat4 &left, const mat4 &right) {
		mat4 result = left;
		for (int i = 0; i < sizeof(mat4) / sizeof(float); i++)
			result.m[i] -= right.m[i];
		return result;
	}
	mat4 operator*(const mat4 &left, const mat4 &right) {
		mat4 result;

		float m00 = left.m00 * right.m00 + left.m10 * right.m01 + left.m20 * right.m02 + left.m30 * right.m03;
		float m01 = left.m01 * right.m00 + left.m11 * right.m01 + left.m21 * right.m02 + left.m31 * right.m03;
		float m02 = left.m02 * right.m00 + left.m12 * right.m01 + left.m22 * right.m02 + left.m32 * right.m03;
		float m03 = left.m03 * right.m00 + left.m13 * right.m01 + left.m23 * right.m02 + left.m33 * right.m03;
		float m10 = left.m00 * right.m10 + left.m10 * right.m11 + left.m20 * right.m12 + left.m30 * right.m13;
		float m11 = left.m01 * right.m10 + left.m11 * right.m11 + left.m21 * right.m12 + left.m31 * right.m13;
		float m12 = left.m02 * right.m10 + left.m12 * right.m11 + left.m22 * right.m12 + left.m32 * right.m13;
		float m13 = left.m03 * right.m10 + left.m13 * right.m11 + left.m23 * right.m12 + left.m33 * right.m13;
		float m20 = left.m00 * right.m20 + left.m10 * right.m21 + left.m20 * right.m22 + left.m30 * right.m23;
		float m21 = left.m01 * right.m20 + left.m11 * right.m21 + left.m21 * right.m22 + left.m31 * right.m23;
		float m22 = left.m02 * right.m20 + left.m12 * right.m21 + left.m22 * right.m22 + left.m32 * right.m23;
		float m23 = left.m03 * right.m20 + left.m13 * right.m21 + left.m23 * right.m22 + left.m33 * right.m23;
		float m30 = left.m00 * right.m30 + left.m10 * right.m31 + left.m20 * right.m32 + left.m30 * right.m33;
		float m31 = left.m01 * right.m30 + left.m11 * right.m31 + left.m21 * right.m32 + left.m31 * right.m33;
		float m32 = left.m02 * right.m30 + left.m12 * right.m31 + left.m22 * right.m32 + left.m32 * right.m33;
		float m33 = left.m03 * right.m30 + left.m13 * right.m31 + left.m23 * right.m32 + left.m33 * right.m33;

		result.m00 = m00;
		result.m01 = m01;
		result.m02 = m02;
		result.m03 = m03;
		result.m10 = m10;
		result.m11 = m11;
		result.m12 = m12;
		result.m13 = m13;
		result.m20 = m20;
		result.m21 = m21;
		result.m22 = m22;
		result.m23 = m23;
		result.m30 = m30;
		result.m31 = m31;
		result.m32 = m32;
		result.m33 = m33;

		return result;
	}

	vec4 operator*(const mat4 &left, const vec4 &right) {
		vec4 result;

		result.x = left.m00 * right.x + left.m01 * right.y + left.m02 * right.z + left.m03 * right.w;
		result.y = left.m10 * right.x + left.m11 * right.y + left.m12 * right.z + left.m13 * right.w;
		result.z = left.m20 * right.x + left.m21 * right.y + left.m22 * right.z + left.m23 * right.w;
		result.w = left.m30 * right.x + left.m31 * right.y + left.m32 * right.z + left.m33 * right.w;

		return result;
	}

	std::ostream & operator<<(std::ostream &left, const mat4 &right){
		left << std::dec;
		left << char(218) << ' ' << centered(right.m00, NUM_LEN) << '\t' << centered(right.m10, NUM_LEN) << '\t' << centered(right.m20, NUM_LEN) << '\t' << centered(right.m30, NUM_LEN) << ' ' << char(191) << std::endl;
		left << char(179) << ' ' << centered(right.m01, NUM_LEN) << '\t' << centered(right.m11, NUM_LEN) << '\t' << centered(right.m21, NUM_LEN) << '\t' << centered(right.m31, NUM_LEN) << ' ' << char(179) << std::endl;
		left << char(179) << ' ' << centered(right.m02, NUM_LEN) << '\t' << centered(right.m12, NUM_LEN) << '\t' << centered(right.m22, NUM_LEN) << '\t' << centered(right.m32, NUM_LEN) << ' ' << char(179) << std::endl;
		left << char(192) << ' ' << centered(right.m03, NUM_LEN) << '\t' << centered(right.m13, NUM_LEN) << '\t' << centered(right.m23, NUM_LEN) << '\t' << centered(right.m33, NUM_LEN) << ' ' << char(217) << std::endl;
		return left;
	}

	//==================== Namespace Functions ==============================

	mat4 translate(const vec3 &vec, const mat4 * src, mat4 * dest) {
		if (dest == nullptr)
			dest = new mat4;

		dest->m30 += src->m00 * vec.x + src->m10 * vec.y + src->m20 * vec.z;
		dest->m31 += src->m01 * vec.x + src->m11 * vec.y + src->m21 * vec.z;
		dest->m32 += src->m02 * vec.x + src->m12 * vec.y + src->m22 * vec.z;
		dest->m33 += src->m03 * vec.x + src->m13 * vec.y + src->m23 * vec.z;

		return *dest;
	}
	mat4 scale(const vec3 & vec, const mat4 * src, mat4 * dest){
		if (dest == nullptr)
			dest = new mat4;

		dest->m00 = src->m00 * vec.x;
		dest->m01 = src->m01 * vec.x;
		dest->m02 = src->m02 * vec.x;
		dest->m03 = src->m03 * vec.x;
		dest->m10 = src->m10 * vec.y;
		dest->m11 = src->m11 * vec.y;
		dest->m12 = src->m12 * vec.y;
		dest->m13 = src->m13 * vec.y;
		dest->m20 = src->m20 * vec.z;
		dest->m21 = src->m21 * vec.z;
		dest->m22 = src->m22 * vec.z;
		dest->m23 = src->m23 * vec.z;

		return *dest;
	}
	mat4 rotate(float angle, const vec3 & axis, const mat4 * src, mat4 * dest){
		if (dest == nullptr)
			dest = new mat4;

		float c = cos(angle);
		float s = sin(angle);
		float oneminusc = 1.0f - c;
		float xy = axis.x*axis.y;
		float yz = axis.y*axis.z;
		float xz = axis.x*axis.z;
		float xs = axis.x*s;
		float ys = axis.y*s;
		float zs = axis.z*s;

		float f00 = axis.x*axis.x*oneminusc + c;
		float f01 = xy * oneminusc + zs;
		float f02 = xz * oneminusc - ys;
		// n[3] not used
		float f10 = xy * oneminusc - zs;
		float f11 = axis.y*axis.y*oneminusc + c;
		float f12 = yz * oneminusc + xs;
		// n[7] not used
		float f20 = xz * oneminusc + ys;
		float f21 = yz * oneminusc - xs;
		float f22 = axis.z*axis.z*oneminusc + c;

		float t00 = src->m00 * f00 + src->m10 * f01 + src->m20 * f02;
		float t01 = src->m01 * f00 + src->m11 * f01 + src->m21 * f02;
		float t02 = src->m02 * f00 + src->m12 * f01 + src->m22 * f02;
		float t03 = src->m03 * f00 + src->m13 * f01 + src->m23 * f02;
		float t10 = src->m00 * f10 + src->m10 * f11 + src->m20 * f12;
		float t11 = src->m01 * f10 + src->m11 * f11 + src->m21 * f12;
		float t12 = src->m02 * f10 + src->m12 * f11 + src->m22 * f12;
		float t13 = src->m03 * f10 + src->m13 * f11 + src->m23 * f12;
		dest->m20 = src->m00 * f20 + src->m10 * f21 + src->m20 * f22;
		dest->m21 = src->m01 * f20 + src->m11 * f21 + src->m21 * f22;
		dest->m22 = src->m02 * f20 + src->m12 * f21 + src->m22 * f22;
		dest->m23 = src->m03 * f20 + src->m13 * f21 + src->m23 * f22;
		dest->m00 = t00;
		dest->m01 = t01;
		dest->m02 = t02;
		dest->m03 = t03;
		dest->m10 = t10;
		dest->m11 = t11;
		dest->m12 = t12;
		dest->m13 = t13;

		return *dest;
	}
	
	mat4 transpose(const mat4 * src, mat4 * dest){
		if (dest == nullptr)
			dest = new mat4;

		float nm00 = src->m00;
		float nm01 = src->m10;
		float nm02 = src->m20;
		float nm03 = src->m30;
		float nm10 = src->m01;
		float nm11 = src->m11;
		float nm12 = src->m21;
		float nm13 = src->m31;
		float nm20 = src->m02;
		float nm21 = src->m12;
		float nm22 = src->m22;
		float nm23 = src->m32;
		float nm30 = src->m03;
		float nm31 = src->m13;
		float nm32 = src->m23;
		float nm33 = src->m33;
		dest->m00 = nm00;
		dest->m01 = nm01;
		dest->m02 = nm02;
		dest->m03 = nm03;
		dest->m10 = nm10;
		dest->m11 = nm11;
		dest->m12 = nm12;
		dest->m13 = nm13;
		dest->m20 = nm20;
		dest->m21 = nm21;
		dest->m22 = nm22;
		dest->m23 = nm23;
		dest->m30 = nm30;
		dest->m31 = nm31;
		dest->m32 = nm32;
		dest->m33 = nm33;

		return *dest;
	}

	mat4 perspective(float width, float height, float fov, bool rightHanded){
		return perspective(width, height, fov, NEAR_PLANE, FAR_PLANE, rightHanded);
	}
	mat4 perspective(float width, float height, float fov, float near_plane, float far_plane, bool rightHanded){
		float aspectRatio = width / height;
		float y_scale = (float)((1.0f / tan(rad(fov / 2.0f))) * aspectRatio);
		float x_scale = y_scale / aspectRatio;
		float frustum_length = far_plane - near_plane;

		mat4 projectionMatrix;
		projectionMatrix.m00 = x_scale;
		projectionMatrix.m11 = y_scale;
		projectionMatrix.m22 = ((far_plane + near_plane) / frustum_length);
		if (rightHanded)
			projectionMatrix.m22 *= -1;
		projectionMatrix.m23 = rightHanded ? -1.0f : 1.0f;
		projectionMatrix.m32 = -((near_plane * far_plane) / frustum_length);
		if (rightHanded)
			projectionMatrix.m32 *= 2;
		projectionMatrix.m33 = 0;

		return projectionMatrix;
	}

	mat4 inverse(const mat4 * src, mat4 * dest)	{
		
		float det = src->determinant();
		if(det != 0) {
			if (dest == nullptr)
				dest = new mat4;

			float determinant_inv = 1.0f / det;

			// first row
			float t00 = determinant3x3(src->m11, src->m12, src->m13, src->m21, src->m22, src->m23, src->m31, src->m32, src->m33);
			float t01 = -determinant3x3(src->m10, src->m12, src->m13, src->m20, src->m22, src->m23, src->m30, src->m32, src->m33);
			float t02 = determinant3x3(src->m10, src->m11, src->m13, src->m20, src->m21, src->m23, src->m30, src->m31, src->m33);
			float t03 = -determinant3x3(src->m10, src->m11, src->m12, src->m20, src->m21, src->m22, src->m30, src->m31, src->m32);
			// second row
			float t10 = -determinant3x3(src->m01, src->m02, src->m03, src->m21, src->m22, src->m23, src->m31, src->m32, src->m33);
			float t11 = determinant3x3(src->m00, src->m02, src->m03, src->m20, src->m22, src->m23, src->m30, src->m32, src->m33);
			float t12 = -determinant3x3(src->m00, src->m01, src->m03, src->m20, src->m21, src->m23, src->m30, src->m31, src->m33);
			float t13 = determinant3x3(src->m00, src->m01, src->m02, src->m20, src->m21, src->m22, src->m30, src->m31, src->m32);
			// third row
			float t20 = determinant3x3(src->m01, src->m02, src->m03, src->m11, src->m12, src->m13, src->m31, src->m32, src->m33);
			float t21 = -determinant3x3(src->m00, src->m02, src->m03, src->m10, src->m12, src->m13, src->m30, src->m32, src->m33);
			float t22 = determinant3x3(src->m00, src->m01, src->m03, src->m10, src->m11, src->m13, src->m30, src->m31, src->m33);
			float t23 = -determinant3x3(src->m00, src->m01, src->m02, src->m10, src->m11, src->m12, src->m30, src->m31, src->m32);
			// fourth row
			float t30 = -determinant3x3(src->m01, src->m02, src->m03, src->m11, src->m12, src->m13, src->m21, src->m22, src->m23);
			float t31 = determinant3x3(src->m00, src->m02, src->m03, src->m10, src->m12, src->m13, src->m20, src->m22, src->m23);
			float t32 = -determinant3x3(src->m00, src->m01, src->m03, src->m10, src->m11, src->m13, src->m20, src->m21, src->m23);
			float t33 = determinant3x3(src->m00, src->m01, src->m02, src->m10, src->m11, src->m12, src->m20, src->m21, src->m22);

			// transpose and divide by the determinant
			dest->m00 = t00 * determinant_inv;
			dest->m11 = t11 * determinant_inv;
			dest->m22 = t22 * determinant_inv;
			dest->m33 = t33 * determinant_inv;
			dest->m01 = t10 * determinant_inv;
			dest->m10 = t01 * determinant_inv;
			dest->m20 = t02 * determinant_inv;
			dest->m02 = t20 * determinant_inv;
			dest->m12 = t21 * determinant_inv;
			dest->m21 = t12 * determinant_inv;
			dest->m03 = t30 * determinant_inv;
			dest->m30 = t03 * determinant_inv;
			dest->m13 = t31 * determinant_inv;
			dest->m31 = t13 * determinant_inv;
			dest->m32 = t23 * determinant_inv;
			dest->m23 = t32 * determinant_inv;

			return *dest;
		}else
			return mat4();
	}

	float determinant3x3(float t00, float t01, float t02, float t10, float t11, float t12, float t20, float t21, float t22){
		return    t00 * (t11 * t22 - t12 * t21)
				+ t01 * (t12 * t20 - t10 * t22)
				+ t02 * (t10 * t21 - t11 * t20);
	}

	vec4 transform(const mat4 & left, const vec4 & right, vec4 * dest){
		if (dest == nullptr)
			dest = new vec4;

		float x = left.m00 * right.x + left.m10 * right.y + left.m20 * right.z + left.m30 * right.w;
		float y = left.m01 * right.x + left.m11 * right.y + left.m21 * right.z + left.m31 * right.w;
		float z = left.m02 * right.x + left.m12 * right.y + left.m22 * right.z + left.m32 * right.w;
		float w = left.m03 * right.x + left.m13 * right.y + left.m23 * right.z + left.m33 * right.w;

		dest->x = x;
		dest->y = y;
		dest->z = z;
		dest->w = w;

		return *dest;
	}

	mat4 toMatrix(vec4 quaternion) {
		const float xy = quaternion.x * quaternion.y;
		const float xz = quaternion.x * quaternion.z;
		const float xw = quaternion.x * quaternion.w;
		const float yz = quaternion.y * quaternion.z;
		const float yw = quaternion.y * quaternion.w;
		const float zw = quaternion.z * quaternion.w;
		const float xSquared = quaternion.x * quaternion.x;
		const float ySquared = quaternion.y * quaternion.y;
		const float zSquared = quaternion.z * quaternion.z;
		mat4 matrix;
		matrix.m00 = 1 - 2 * (ySquared + zSquared);
		matrix.m01 = 2 * (xy - zw);
		matrix.m02 = 2 * (xz + yw);
		matrix.m03 = 0;
		matrix.m10 = 2 * (xy + zw);
		matrix.m11 = 1 - 2 * (xSquared + zSquared);
		matrix.m12 = 2 * (yz - xw);
		matrix.m13 = 0;
		matrix.m20 = 2 * (xz - yw);
		matrix.m21 = 2 * (yz + xw);
		matrix.m22 = 1 - 2 * (xSquared + ySquared);
		matrix.m23 = 0;
		matrix.m30 = 0;
		matrix.m31 = 0;
		matrix.m32 = 0;
		matrix.m33 = 1;
		return matrix;
	}

	//====================== Type Functions =================================

	float mat4::determinant() const{
		float f =
			m00
			* ((m11 * m22 * m33 + m12 * m23 * m31 + m13 * m21 * m32)
				- m13 * m22 * m31
				- m11 * m23 * m32
				- m12 * m21 * m33);
		f -= m01
			* ((m10 * m22 * m33 + m12 * m23 * m30 + m13 * m20 * m32)
				- m13 * m22 * m30
				- m10 * m23 * m32
				- m12 * m20 * m33);
		f += m02
			* ((m10 * m21 * m33 + m11 * m23 * m30 + m13 * m20 * m31)
				- m13 * m21 * m30
				- m10 * m23 * m31
				- m11 * m20 * m33);
		f -= m03
			* ((m10 * m21 * m32 + m11 * m22 * m30 + m12 * m20 * m31)
				- m12 * m21 * m30
				- m10 * m22 * m31
				- m11 * m20 * m32);
		return f;
	}

	mat4 mat4::translate(const vec3 & vec){
		return translate(vec, this);
	}
	mat4 mat4::translate(const vec3 & vec, mat4 * dest){
		return glmath::translate(vec, this, dest);
	}

	mat4 mat4::scale(const vec3 &vec) {
		return scale(vec, this);
	}
	mat4 mat4::scale(const vec3 &vec, mat4 * dest){
		return glmath::scale(vec, this, dest);
	}

	mat4 mat4::rotate(float angle, const vec3 &vec) {
		return rotate(angle, vec, this);
	}
	mat4 mat4::rotate(float angle, const vec3 &vec, mat4 * dest) {
		return glmath::rotate(angle, vec, this, dest);
	}

	mat4 mat4::transpose() {
		return transpose(this);
	}
	mat4 mat4::transpose(mat4 * dest) { 
		return glmath::transpose(this, dest);
	}

	mat4 mat4::inverse() {
		return inverse(this);
	}
	mat4 mat4::inverse(mat4 * dest) {
		return glmath::inverse(this, dest);
	}

	mat4 mat4::identity() {
		memcpy_s(this, sizeof(mat4), &glmath::Mat4Identity, sizeof(mat4));
		return *this;
	}
	mat4 mat4::zero() {
		memcpy_s(this, sizeof(mat4), &glmath::Mat4Zero, sizeof(mat4));
		return *this;
	}

}