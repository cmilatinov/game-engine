#pragma once

#include <functional>

#include "../math/GLVector.h"
#include "../input/Mouse.h"
#include "../input/Keyboard.h"
#include "Camera.h"

#pragma once
class CameraFPS : public Camera {

	private:
		/**
		 * @brief The camera's speed in units per second.
		 * 
		 */
		float speed = 10.0f;

		/**
		 * @brief The mouse input object used to rotate the camera.
		 * 
		 */
		Mouse * mouse;
		
		/**
		 * @brief The keyboard input object used to move the camera.
		 * 
		 */
		Keyboard * keyboard;

	public:
		/**
		 * @brief Constructs a new first person camera object using given parameters.
		 * 
		 * @param num The aspect ratio numerator.
		 * @param den The aspect ratio denominator.
		 * @param fov The camera's FOV in degrees.
		 * @param mouse The mouse input object used to rotate the camera.
		 * @param keyboard The keyboard input object used to move the camera.
		 */
		CameraFPS(int num, int den, float fov, Mouse * mouse, Keyboard * keyboard);

		/**
		 * @brief Destroys the first person camera object.
		 * 
		 */
		~CameraFPS();

		/**
		 * @brief This method is called before every frame with the time elapsed since the last frame as a parameter in order to implement the camera's logic. 
		 * 
		 * @param delta The number of seconds that have passed since the last drawn frame.
		 */
		void update(double delta) override;

};

