#include <functional>
#include <map>

#include <glfw/glfw3.h>

#include "GLVector.h"
#include "Display.h"

using namespace glmath;
using std::function;
using std::map;

#pragma once
class Mouse {

	private:
		/**
		 * @brief A pointer to a display object.
		 * 
		 */
		Display * display;

		/**
		 * @brief The mouse's relative sensitivity.
		 * 
		 */
		float sensitivity = 0.2f;

		/**
		 * @brief The mouse's last position's X coordinate.
		 * 
		 */
		int lastPosX; 

		/**
		 * @brief The mouse's last position's Y coordinate.
		 * 
		 */
		int lastPosY;

		/**
		 * @brief Indicates whether or not to ignore the next mouse move event. 
		 * Used to move the mouse without triggering its callback.
		 * 
		 */
		bool ignoreNext = false;

		/**
		 * @brief A mouse move callback handler function with parameters dx and dy 
		 * where dx and dy represent the distance moved since the last callback.
		 * 
		 */
		function<void(float, float)> callback;
		
		/**
		 * @brief Hash map mapping window instances to mouse input objects.
		 * 
		 */
		static map<GLFWwindow*, Mouse*> instances;

	public:
		/**
		 * @brief Constructs a mouse object using the specified display to poll for events.
		 * 
		 * @param display 
		 */
		Mouse(Display * display);
		
		/**
		 * @brief Destroys the mouse input object.
		 * 
		 */
		~Mouse();

		/**
		 * @brief Set the mouse's relative sensitivity.
		 * 
		 * @param sensitivity The new mouse sensitivity.
		 * @return [Mouse *] This same mouse input instance in order to allow for method chaining.
		 */
		inline Mouse * setSensitivity(float sensitivity) {
			this->sensitivity = sensitivity;
			return this;
		}

		/**
		 * @brief Set this mouse input's move event handler callback function.
		 * 
		 * @param callback The function to call when the mouse is moved.
		 * @return [Mouse *] This same mouse input instance in order to allow for method chaining.
		 */
		inline Mouse * setOnMove(function<void(float, float)> callback) {
			this->callback = callback;
			return this;
		}

		/**
		 * @brief Returns whether or not the specified mouse button is being held down or not.
		 * 
		 * @param button The mouse button to query (GLFW_MOUSE_BUTTON_X).
		 * @return true The mouse button is being pressed.
		 * @return false The mouse button is not being held down.
		 */
		inline bool isMouseDown(int button) {
			return glfwGetMouseButton(display->window, button);
		}

		/**
		 * @brief Returns this mouse input's relative sensitivity.
		 * 
		 * @return [float] The mouse sensitivity.
		 */
		inline float getSensitivity() {
			return sensitivity;
		}

		/**
		 * @brief Resets the mouse in the middle of its display.
		 * 
		 * @return [Mouse *] This same mouse input instance in order to allow for method chaining.
		 */
		Mouse * resetMouse();

		/**
		 * @brief The mouse move callback function handling move events.
		 * 
		 * @param window The window that received the event.
		 * @param x The new cursor x-coordinate, relative to the left edge of the content area.
		 * @param y The new cursor y-coordinate, relative to the top edge of the content area.
		 */
		static void mouseMoveCallback(GLFWwindow * window, double x, double y);

};

