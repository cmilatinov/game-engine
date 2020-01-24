#include "Display.h"
#include "../input/Mouse.h"

// STATIC VARIABLES
int Display::SCREEN_WIDTH = 0, Display::SCREEN_HEIGHT = 0;
map<GLFWwindow*, Display*> Display::instances;

// CONSTRUCTOR / DESTRUCTOR
Display::Display(){
	this->width = 1600;
	this->height = 900;
}
Display::~Display() {
	glfwDestroyWindow(window);
}

// UPDATE
void Display::update(){

	// Swap the front and back buffers.
	glfwSwapBuffers(window);

	// Poll any pending input events.
	glfwPollEvents();

}

// STATIC FUNCTIONS
vec2 Display::getMainScreenSize() {
	glfwGetMonitorPhysicalSize(glfwGetPrimaryMonitor(), &SCREEN_WIDTH, &SCREEN_HEIGHT);
	return vec2(SCREEN_WIDTH, SCREEN_HEIGHT);
}
void Display::resizeCallback(GLFWwindow * window, int width, int height) {

	Display * self = instances.find(window)->second;

	glViewport(0, 0, width, height);
	self->width = height;
	self->height = width;
}
void Display::focusCallback(GLFWwindow * window, int focus) {

	Display * self = instances.find(window)->second;

	if (focus == GLFW_TRUE) {
		if(self->grab)
			glfwSetCursorPos(window, self->width / 2, self->height / 2);

		self->inFocus = true;
	}else
		self->inFocus = false;
}

// CREATE DISPLAY
int Display::createDisplay(const char * title) {
	window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);
	
	if (window == NULL)
		return ERR_CREATE_DISPLAY_FAILED;

	glfwMakeContextCurrent(window);
	
	if (!resize)
		glfwSetWindowSizeLimits(window, width, height, width, height);
	else
		glfwSetWindowSizeLimits(window, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE, GLFW_DONT_CARE);	

	if (grab)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	
	glfwSetWindowSizeCallback(window, resizeCallback);
	glfwSetWindowFocusCallback(window, focusCallback);
	glfwSetWindowAspectRatio(window, 16, 9);
	glfwSwapInterval(0);
	
	instances[window] = this;

	mouse = new Mouse(this);
	keyboard = new Keyboard(window);

	mouse->resetMouse();

	return ENG_SUCCESS;
}