#include <cmath>

#include "GLVector.h"
#include "GLMatrix.h"

using namespace glmath;

#pragma once
class Camera {

	protected:
		/**
		 * @brief The camera's position and rotation expressed as 3D vectors.
		 * 
		 */
		vec3 pos, rot;
	
	private:
		/**
		 * @brief The camera's aspect ratio, stored as a fraction of a numerator over a denominator.
		 * 
		 */
		int aspectNum = 1, aspectDen = 1;

		/**
		 * @brief The camera's FOV in degrees.
		 * 
		 */
		float fov = 0.0f;

		/**
		 * @brief The camera's projection matrix. This is used to create the illusion of perspective when rendering a 3D scene.
		 * 
		 */
		mat4 proj;

		/**
		 * @brief Recreates the camera's perspective matrix based on the last provided aspect ratio and FOV.
		 * 
		 */
		inline void updateProjMatrix() {
			proj = perspective(aspectNum, aspectDen, fov, true);
		}

	public:
		/**
		 * @brief Constructs a new Camera object using the provided aspect ratio and FOV.
		 * 
		 * @param num The aspect ratio numerator.
		 * @param den The aspect ratio denominator.
		 * @param fov The FOV value in degrees.
		 */
		Camera(int num, int den, float fov);
		
		/**
		 * @brief Destroys the camera object.
		 * 
		 */
		~Camera();
		
		/**
		 * @brief Sets the camera's aspect ratio.
		 * 
		 * @param num The new aspect ratio numerator.
		 * @param den The new aspect ratio denominator.
		 * @return [Camera *] This same camera instance in order to allow for method chaining. 
		 */
		inline Camera * setAspect(int num, int den) {
			this->aspectNum = num;
			this->aspectDen = den;
			updateProjMatrix();
			return this;
		}

		/**
		 * @brief Sets the camera's field of view (FOV).
		 * 
		 * @param fov The new FOV of the camera in degrees.
		 * @return [Camera *] This same camera instance in order to allow for method chaining. 
		 */
		inline Camera * setFOV(float fov) {
			this->fov = fov;
			updateProjMatrix();
			return this;
		}

		/**
		 * @brief Sets the camera's position in 3D space.
		 * 
		 * @param pos The new world position of the camera, where (0, 0, 0) is the world origin.
		 * @return [Camera *] This same camera instance in order to allow for method chaining.
		 */
		inline Camera * setPosition(const vec3& pos) {
			this->pos = pos;
			return this;
		}

		/**
		 * @brief Sets the camera's rotation in 3D space.
		 *  
		 * @param rot The new Euler rotation of the camera, where (0, 0, 0) means the camera is facing the negative Z direction.
		 * @return [Camera *] This same camera instance in order to allow for method chaining.
		 */
		inline Camera * setRotation(const vec3& rot) {
			this->rot = rot;
			return this;
		}

		/**
		 * @brief Translates the camera in 3D space.
		 * 
		 * @param pos The translation amount in 3D space, where (0, 0, 0) means no translation.
		 * @return [Camera *] This same camera instance in order to allow for method chaining.
		 */
		inline Camera * translate(const vec3& pos) {
			this->pos += pos;
			return this;
		}

		/**
		 * @brief Rotates the camera in 3D space.
		 * 
		 * @param pos The Euler rotation amount in 3D space, where (0, 0, 0) means no rotation.
		 * @return [Camera *] This same camera instance in order to allow for method chaining.
		 */
		inline Camera * rotate(const vec3& rot) {
			this->rot += rot;
			return this;
		}

		/**
		 * @brief Rotates the camera in order for it to face a point in 3D space. This method does not translate the camera.
		 * 
		 * @param pos The point the camera is to look at.
		 * @return [Camera *] This same camera instance in order to allow for method chaining. 
		 */
		Camera * lookAt(const vec3 & pos);

		/**
		 * @brief Returns the forward direction vector of the camera.
		 * 
		 * @return [vec3] The direction in which the camera is currently looking. 
		 */
		vec3 forward();

		/**
		 * @brief Returns the right direction vector of the camera.
		 * 
		 * @return [vec3] The direction perpendicular and to the right of the camera's current heading. This vector is always parallel to the XZ plane. 
		 */
		vec3 right();

		/**
		 * @brief Returns the camera's rotation vector in 3D space.
		 * 
		 * @return [vec3] The camera's current Euler rotation, where (0, 0, 0) means the camera is facing the negative Z direction.
		 */
		inline vec3 getRotation() {
			return rot;
		}

		/**
		 * @brief Returns the camera's position vector in 3D space.
		 * 
		 * @return [vec3] The camera's current position in 3D space, where (0, 0, 0) is the world origin.
		 */
		inline vec3 getPosition() {
			return pos;
		}

		/**
		 * @brief Creates a projection view matrix corresponding to the camera's current whereabouts and heading.
		 * 
		 * @return [mat4] The matrix created from multiplying the projection and view matrices of the camera together.
		 */
		mat4 createProjectionViewMatrix();

		/**
		 * @brief This method is called every frame and is used by derived classes to implement the camera's logic.
		 * 
		 * @param delta The number of seconds that have passed since the last drawn frame.
		 */
		virtual void update(double delta) = 0;

};

