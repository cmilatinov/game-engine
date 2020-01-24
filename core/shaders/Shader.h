#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>

#include <glad\glad.h>
#include <GLFW/glfw3.h>

#include "../utils/EngineDef.h"
#include "../math/GLVector.h"
#include "../math/GLMatrix.h"

using namespace glmath;
using std::ifstream;
using std::string;
using std::stringstream;
using std::cout;
using std::endl;

#pragma once
class Shader {

	protected:

		/**
		 * @brief This shader program's OpenGL ID number.
		 * 
		 */
		unsigned int id;

		/**
		 * @brief This shader program's vertex shader ID number.
		 * 
		 */
		unsigned int vertex;

		/**
		 * @brief This shader program's fragment shader ID number.
		 * 
		 */ 
		unsigned int fragment;

		/**
		 * @brief This shader program's geometry shader ID number.
		 * 
		 */ 
		unsigned int geometry;

	public:
		/**
		 * @brief Constructs a new shader program with the specified vertex and fragment shaders.
		 * 
		 * @param vertexPath Relative path to the program's vertex shader.
		 * @param fragmentPath Relative path to the program's fragment shader.
		 */
		Shader(const char * vertexPath, const char * fragmentPath);

		/**
		 * @brief Constructs a new shader program with the specified vertex, fragment, and geometry shaders.
		 * 
		 * @param vertexPath Relative path to the program's vertex shader.
		 * @param fragmentPath Relative path to the program's fragment shader.
		 * @param geometryPath Relative path to the program's geometry shader.
		 */
		Shader(const char * vertexPath, const char * fragmentPath, const char * geometryPath);

		/**
		 * @brief Destroys the shader program.
		 * 
		 */
		~Shader();

		/**
		 * @brief Sets this shader program as the current shader used for rendering.
		 * 
		 */
		virtual inline void use() final;

		/**
		 * @brief Stops the shader program from being used for rendering.
		 * 
		 */
		virtual inline void stop() final;
		
	private:
		/**
		 * @brief Checks for compilation errors for individual shaders as well as for linking errors for the shader program.
		 * 
		 * @param shader The shader or shader program ID to check.
		 * @param type The type of shader. (VERTEX, FRAGMENT, GEOMETRY, or PROGRAM)
		 * @return true The shader has no compilation or linking errors.
		 * @return false The shader contains linking or compilation that should be resolved.
		 */
		static bool checkCompileErrors(unsigned int shader, string type);

		/**
		 * @brief The shader source folder.
		 *
		 */
		static const char * SHADER_SOURCE;

	protected:
		/**
		 * @brief Loads a boolean into a shader uniform location.
		 * 
		 * @param location The variable location in the shader.
		 * @param value The boolean to load.
		 */
		virtual inline void loadBoolean(unsigned int location, bool value) final;

		/**
		 * @brief Loads a integer into a shader uniform location.
		 * 
		 * @param location The variable location in the shader.
		 * @param value The integer to load.
		 */
		virtual inline void loadInt(unsigned int location, int value) final;

		/**
		 * @brief Loads a floating-point number into a shader uniform location.
		 * 
		 * @param location The variable location in the shader.
		 * @param value The floating-point number to load.
		 */
		virtual inline void loadFloat(unsigned int location, float value) final;

		/**
		 * @brief Loads a double precision floating-point number into a shader uniform location.
		 * 
		 * @param location The variable location in the shader.
		 * @param value The double precision floating-point number to load.
		 */
		virtual inline void loadDouble(unsigned int location, double value) final;

		/**
		 * @brief Loads a three dimensional vector into a shader uniform location.
		 * 
		 * @param location The variable location in the shader.
		 * @param value The three dimensional vector to load.
		 */
		virtual inline void loadVector(unsigned int location, const vec3* vec) final;

		/**
		 * @brief Loads a four dimensional vector into a shader uniform location.
		 * 
		 * @param location The variable location in the shader.
		 * @param value The four dimensional vector to load.
		 */
		virtual inline void loadVector(unsigned int location, const vec4* vec) final;

		/**
		 * @brief Loads a four by four matrix into a shader uniform location.
		 * 
		 * @param location The variable location in the shader.
		 * @param value The four by four matrix to load.
		 */
		virtual inline void loadMatrix(unsigned int location, const mat4* mat) final;


		/**
		 * @brief Binds an attribute list index to a vertex shader input variable.
		 * 
		 * @param attribute The attribute list index.
		 * @param varName The variable name as specified in the shader.
		 */
		virtual inline void bindAttribute(int attribute, const char* varName) final;

		/**
		 * @brief Returns a uniform variable's location in the shader program.
		 * 
		 * @param name The variable name as specified in the shader.
		 */
		virtual inline unsigned int getUniformLocation(const char* name) final;

		/**
		 * @brief Binds this shader's attribute lists to the correct variables.
		 * This method should be implemented in all Shader-derived classes.
		 * 
		 */
		virtual void bindAttributes() = 0;

		/**
		 * @brief Retrieves this shader's uniform variable locations. 
		 * This method should be implemented in all Shader-derived classes.
		 * 
		 */
		virtual void getUniformLocations() = 0;

		/**
		 * @brief Links and validates the shader program. 
		 * This method should be called in all Shader-derived classes.
		 * 
		 */
		virtual void validate() final;
		
};