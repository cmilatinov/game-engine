#include "../display/Display.h"
#include "Mouse.h"

// Static hashmap linking window instances to MouseInput instances.
map<GLFWwindow *, Mouse *> Mouse::instances;

Mouse::Mouse(Display * display){
	this->display = display;
	instances[display->window] = this;

	double x, y;
	glfwGetCursorPos(display->window, &x, &y);
	this->lastPosX = x;
	this->lastPosY = y;

	glfwSetCursorPosCallback(display->window, mouseMoveCallback);
}
Mouse::~Mouse(){
	glfwSetCursorPosCallback(display->window, NULL);
}

Mouse * Mouse::resetMouse(){
	ignoreNext = true;
	vec2 center = display->getCenterPoint();
	glfwSetCursorPos(display->window, center.x, center.y);
	return this;
}

void Mouse::mouseMoveCallback(GLFWwindow * window, double x, double y){

	Mouse * self = instances.find(window)->second;

	if (self->ignoreNext) {
		self->lastPosX = x;
		self->lastPosY = y;
		self->ignoreNext = false;
		return;
	}

	if (self->callback != nullptr)
		self->callback(
			self->sensitivity * (x - self->lastPosX), 
			self->sensitivity * (y - self->lastPosY)
		);

	self->lastPosX = x;
	self->lastPosY = y;

	if (self->display->isGrabbed())
		self->resetMouse();
	
}
