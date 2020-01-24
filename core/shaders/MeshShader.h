#include <string>

#include "Shader.h"

using namespace glmath;
using std::string;

#pragma once
class MeshShader: public Shader {

	private:
		/**
		 * @brief The file name for this shader program's vertex shader.
		 * 
		 */
		static const char * VERTEX_FILE;

		/**
		 * @brief The file name for this shader program's fragment shader.
		 * 
		 */
		static const char * FRAGMENT_FILE;

		/**
		 * @brief The maximum number of joints a skeleton can have.
		 *
		 */
		static const int MAX_JOINTS = 50;

		/**
		 * @brief The location of the 2D texture sampler.
		 * 
		 */
		unsigned int location_tex = 0;

		/**
		 * @brief The location of projection view matrix.
		 * 
		 */
		unsigned int location_projViewMatrix = 0;

		/**
		 * @brief The location of model matrix.
		 * 
		 */
		unsigned int location_modelMatrix = 0;

		/**
		 * @brief The location of the joint transformations.
		 *
		 */
		unsigned int location_jointTransforms;

		/**
		 * @brief The location of the boolean indicating whether or not the model is animated.
		 *
		 */
		unsigned int location_animated = 0;

	public:
		/**
		 * @brief Constructs a new mesh shader program.
		 * 
		 */
		MeshShader();
		~MeshShader();

		/**
		 * @brief Binds this shader's attribute lists to the correct variables.
		 * 
		 */
		void bindAttributes() override;

		/**
		 * @brief Retrieves this shader's uniform variable locations.
		 * 
		 */
		void getUniformLocations() override; 

		/**
		 * @brief Loads a projection view matrix into the shader program.
		 * 
		 * @param matrix The matrix to load as a projection view matrix.
		 */
		inline void loadProjViewMatrix(const mat4 & matrix) { 
			loadMatrix(location_projViewMatrix, &matrix); 
		};

		/**
		 * @brief Loads a model matrix into the shader program.
		 * 
		 * @param matrix The matrix to load as a model matrix.
		 */
		inline void loadModelMatrix(const mat4 & matrix) {
			loadMatrix(location_modelMatrix, &matrix);
		}

		/**
		 * @brief Loads the texture unit into the shader program.
		 * 
		 * @param unit The texture unit to use.
		 */
		inline void loadTextureUnit(int unit) {
			loadInt(location_tex, unit);
		}

		/**
		 * @brief Loads the joint transformations used for animation into the shader program.
		 *
		 * @param jointTransforms A pointer to the matrix array of transformations.
		 * @param size The number of transformations to load.
		 */
		inline void loadJointTransforms(mat4 * jointTransforms, unsigned int size) {
			glUniformMatrix4fv(location_jointTransforms, size, false, reinterpret_cast<float*>(jointTransforms));
		}

		/**
		 * @brief Loads the animated boolean into the shader program.
		 *
		 * @param animated Whether or not the mesh to render is animated.
		 */
		inline void loadAnimated(bool animated) {
			loadBoolean(location_animated, animated);
		}
};

