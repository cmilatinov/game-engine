#include "Shader.h"

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
};

