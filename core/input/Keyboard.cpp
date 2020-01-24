#include "Keyboard.h"

// Static hashmap linking window instances to KeyboardInput instances.
map<GLFWwindow*, Keyboard*> Keyboard::inputMap;

Keyboard::Keyboard(GLFWwindow * window){
	this->window = window;
	inputMap.insert(std::make_pair(window, this));
	glfwSetKeyCallback(window, invoke);
}

Keyboard::~Keyboard(){
	glfwSetKeyCallback(window, NULL);
}

bool Keyboard::isKeyDown(int key){
	return glfwGetKey(window, key);
}

void Keyboard::registerKeyUp(int key, function<void(void)> callback){
	this->keyReleased[key] = callback;
}

void Keyboard::registerKeyDown(int key, function<void(void)> callback){
	this->keyPressed[key] = callback;
}

void Keyboard::invoke(GLFWwindow * window, int key, int scancode, int action, int mods) {
	Keyboard * instance = inputMap.find(window)->second;

	if (action == GLFW_RELEASE) {
		if (instance->keyReleased.find(key) != instance->keyReleased.end())
			instance->keyReleased.find(key)->second();
	}
	else {
		if (instance->keyPressed.find(key) != instance->keyPressed.end())
			instance->keyPressed.find(key)->second();
	}
}