#include "CameraFPS.h"

CameraFPS::CameraFPS(int num, int den, float fov, Mouse * mouse, Keyboard * keyboard) :
	Camera(num, den, fov){
	this->mouse = mouse;
	this->keyboard = keyboard;

	this->mouse->setOnMove([this](float x, float y) {
		this->rotate(vec3(y, x, 0));
	});
}

CameraFPS::~CameraFPS(){

}

void CameraFPS::update(double delta){
	if (keyboard->isKeyDown(GLFW_KEY_W))
		pos += delta * speed * forward();

	if (keyboard->isKeyDown(GLFW_KEY_S))
		pos -= delta * speed * forward();

	if (keyboard->isKeyDown(GLFW_KEY_A))
		pos -= delta * speed * right();

	if (keyboard->isKeyDown(GLFW_KEY_D))
		pos += delta * speed * right();

	if (keyboard->isKeyDown(GLFW_KEY_LEFT_SHIFT))
		pos += delta * speed * vec3(0, -1, 0);

	if (keyboard->isKeyDown(GLFW_KEY_SPACE))
		pos += delta * speed * vec3(0, 1, 0);
}