#include "Camera.h"

Camera::Camera(int num, int den, float fov){
	this->aspectNum = num;
	this->aspectDen = den;
	this->fov = fov;

	this->rot = vec3(0);
	this->pos = vec3(0);

	updateProjMatrix();
}
Camera::~Camera(){}

Camera * Camera::lookAt(const vec3 & pos) {
	vec3 dir = pos - this->pos;

	float pitch = atan(dir.y / vec2(dir.x, dir.z).length() * 180.0 / PI);
	float yaw = dir.z < 0 ? 
			atan(dir.x / dir.z) * 180.0 / PI : 
			atan(dir.x / dir.z) * 180.0 / PI + 180.0;
	float roll = PI;

	rot = vec3(-pitch, -yaw, 0.0f);

	return this;
}

vec3 Camera::forward() {
	mat4 transform;

	transform.rotate(rot.x * PI / 180.0, vec3(1, 0, 0));
	transform.rotate(rot.y * PI / 180.0, vec3(0, 1, 0));

	vec4 vec = transform * vec4(0, 0, -1, 1);

	return vec3(vec.x, vec.y, vec.z) / vec.w;
}
vec3 Camera::right() {
	return glmath::cross(forward(), vec3(0, 1, 0));
}

mat4 Camera::createProjectionViewMatrix() {
	
	mat4 view;

	view.rotate(rot.x * PI / 180, vec3(1, 0, 0));
	view.rotate(rot.y * PI / 180, vec3(0, 1, 0));
	view.rotate(rot.z * PI / 180, vec3(0, 0, 1));

	view.translate(-1 * pos);

	return proj * view;
}