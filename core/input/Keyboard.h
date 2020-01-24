#include <map>
#include <functional>

#include <glfw/glfw3.h>

using namespace std;

#pragma once
class Keyboard {

	private:
		/**
		 * @brief Pointer to GLFW window instance.
		 * 
		 */
		GLFWwindow * window;
		
		/**
		 * @brief Hash maps mapping keycodes to function handlers.
		 * 
		 */
		map<int, function<void(void)>> keyPressed, keyReleased;

		/**
		 * @brief Hash map mapping window instances to keyboard instances.
		 * 
		 */
		static map<GLFWwindow*, Keyboard*> inputMap;

	public:
		/**
		 * @brief Constructs a keyboard input object using the specified window to retrieve inputs.
		 * 
		 */
		Keyboard(GLFWwindow *);

		/**
		 * @brief Destroys the keyboard input object.
		 * 
		 */
		~Keyboard();

		/**
		 * @brief Key event callback function.
		 * 
		 * @param window The window that received the event.
		 * @param key The keyboard key that was pressed or released.
		 * @param scancode The system specific scan code of the key.
		 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
		 * @param mods Bit field describing which modifier keys were held down.
		 */
		static void invoke(GLFWwindow * window, int key, int scancode, int action, int mods);

		/**
		 * @brief Returns whether a key is currently being held down or not.
		 * 
		 * @param key The key to check.
		 * @return true The key is being held down.
		 * @return false The key is not being pressed.
		 */
		bool isKeyDown(int key);

		/**
		 * @brief Set a callback function to fire at a certain key release.
		 * 
		 * @param key The to which to bind the key release callback.
		 * @param callback The callback function.
		 */
		void registerKeyUp(int key, function<void(void)> callback);

		/**
		 * @brief Set a callback function to fire at a certain key press.
		 * 
		 * @param key The to which to bind the key press callback.
		 * @param callback The callback function.
		 */
		void registerKeyDown(int key, function<void(void)> callback);

};

