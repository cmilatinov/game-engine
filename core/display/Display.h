#include <map>

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include "../math/GLVector.h"
#include "../utils/EngineDef.h"
#include "../input/Keyboard.h"

class Mouse;

using namespace glmath;
using std::map;

#pragma once
class Display {

	public:
		/**
		 * @brief A pointer to the GLFW window object.
		 * 
		 */
		GLFWwindow * window = nullptr;

		/**
		 * @brief A pointer to the mouse input object associated to this display.
		 * 
		 */
		Mouse * mouse = nullptr;

		/**
		 * @brief A pointer to the keyboard input object associated to this display.
		 * 
		 */
		Keyboard * keyboard = nullptr;

	private:
		/**
		 * @brief Indicates whether or not the mouse should be grabbed when the window is in focus.
		 * 
		 */
		bool grab = false;

		/**
		 * @brief Indicates whether or not the display should be created in fullscreen mode.
		 * 
		 */
		bool fullscreen = false;

		/**
		 * @brief Indicates whether or not the display can be resized.
		 * 
		 */
		bool resize = false;

		/**
		 * @brief Indicates whether or not the display is in focus.
		 * 
		 */
		bool inFocus = false;

		/**
		 * @brief Indicates the width of the display in pixels.
		 * 
		 */
		int width; 

		/**
		 * @brief Indicates the height of the display in pixels.
		 * 
		 */
		int height;

		/**
		 * @brief Holds the width of the primary monitor in pixels.
		 * 
		 */
		static int SCREEN_WIDTH;

		/**
		 * @brief Holds the height of the primary monitor in pixels.
		 * 
		 */
		static int SCREEN_HEIGHT;

		/**
		 * @brief Maps indivual display instances to GLFW window pointers.
		 * 
		 */
		static map<GLFWwindow*, Display*> instances;

	public:
		/**
		 * @brief Constructs a new display with a default size of 1600 by 900 pixels. 
		 * The window associated to this display must still be created using the `createDisplay` method. 
		 * 
		 */
		Display();

		/**
		 * @brief Destroys the Display object.
		 * 
		 */
		~Display();

		/**
		 * @brief Polls any pending input events and swaps the display buffers.
		 * 
		 */
		void update();

		/**
		 * @brief Sets whether or not the display can be resized by the user. 
		 * This method has no effect after the display has been created.
		 * 
		 * @param resize Whether or not the display should be resizable by the user.
		 * @return [Display *] This same display instance in order to allow for method chaining.
		 */
		inline Display * setResizable(bool resize) {
			this->resize = resize;
			return this;
		}

		/**
		 * @brief Sets whether or not the display should appear in fullscreen mode. 
		 * This method has no effect after the display has been created.
		 * 
		 * @param fullscreen Whether or not the display should be created in fullscreen mode.
		 * @return [Display *] This same display instance in order to allow for method chaining.
		 */
		inline Display * setFullscreen(bool fullscreen) {
			this->fullscreen = fullscreen;
			return this;
		}

		/**
		 * @brief Sets the display's size in pixels. 
		 * This method has no effect after the display has been created.
		 * 
		 * @param width The desired display width in pixels.
		 * @param height The desired display height in pixels.
		 * @return [Display *] This same display instance in order to allow for method chaining.
		 */
		inline Display * setSize(int width, int height) {
			this->width = width;
			this->height = height;
			return this;
		}

		/**
		 * @brief Sets whether or not the mouse cursor should be grabbed by the display. 
		 * This method has no effect after the display has been created.
		 * 
		 * @param grab Whether or not the display should grab the mouse cursor. 
		 * If set to true the cursor will be hidden and the user will be prevented from dragging the mouse out of the window's bounds.
		 * @return [Display *] This same display instance in order to allow for method chaining.
		 */
		inline Display * setGrabMouse(bool grab) {
			this->grab = grab;
			return this;
		}

		/**
		 * @brief Returns the display's center point in pixel coordinates.
		 * 
		 * @return [vec2] The center point of the display in pixel coordinates where (0, 0) is the top left corner.
		 */
		inline vec2 getCenterPoint() {
			return vec2(width / 2.0f, height / 2.0f);
		}

		/**
		 * @brief Returns the display's size in pixel bounds.
		 * 
		 * @return [vec2] The display's size in pixels.
		 */
		inline vec2 getDisplaySize() {
			return vec2(width, height);
		}
		/**
		 * @brief Returns whether or not the display is in focus.
		 * 
		 * @return true The display is currently in focus.
		 * @return false The display is currently out of focus.
		 */
		inline bool isInFocus() {
			return inFocus;
		}
		/**
		 * @brief Returns whether or not the display is grabbing the mouse cursor.
		 * 
		 * @return true The display is hiding the mouse cursor and preventing the user from moving it outside its bounds.
		 * @return false The display is not grabbing the mouse cursor.
		 */
		inline bool isGrabbed() {
			return grab;
		}
		/**
		 * @brief Returns whether or not the display should be closed.
		 * 
		 * @return true The display must be closed as the user has attempted to close the window.
		 * @return false The display should stay open.
		 */
		inline bool shouldClose() {
			return glfwWindowShouldClose(window);
		}

		/**
		 * @brief Creates the display's window with the given title.
		 * 
		 * @param title The title to show on the display window.
		 * @return [int] Zero if the creation was successful, ERR_DISPLAY_NOT_CREATED otherwise.
		 */
		int createDisplay(const char * title);

		/**
		 * @brief Returns the primary monitor's size in pixel bounds.
		 * 
		 * @return [vec2] The size of the primary computer monitor in pixels.
		 */
		static vec2 getMainScreenSize();

		/**
		 * @brief Called when the user resizes the diplay window.
		 * 
		 * @param window The window that was resized.
		 * @param width The new width of the window in pixels.
		 * @param height The new height of the window in pixels.
		 */
		static void resizeCallback(GLFWwindow * window, int width, int height);

		/**
		 * @brief Called when the display window changes focus state.
		 * 
		 * @param window The window whose focus has changed.
		 * @param focus The new focus state of the window.
		 */
		static void focusCallback(GLFWwindow * window, int focus);

};

