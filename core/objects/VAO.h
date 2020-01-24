#include <list>
#include <string>
#include <map>
#include <vector>

#include <glad/glad.h>

using namespace std;

#pragma once
class VBO {

	private:
		/** 
		 * @brief This vertex bufer object's OpenGL ID.
		 * 
		 */
		unsigned int id;

		/** 
		 * @brief This vertex bufer object's type. (GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, etc...)
		 * 
		 */
		GLenum type;

		/**
		 * @brief Constructs a new vertex buffer object.
		 * 
		 * @param id The vertex bufer object's OpenGL ID.
		 * @param type The vertex bufer object's OpenGL type.
		 */
		VBO(unsigned int id, GLenum type);

	public:
		/**
		 * @brief Deletes the vertex buffer object from memory and destroys its instance.
		 * 
		 */
		~VBO();

		/**
		 * @brief Binds this vertex buffer object to the currently bound vertex array object for manipulation.
		 * 
		 * @return [VBO *] This same vertex buffer instance in order to allow for method chaining.
		 */
		inline VBO * bind();

		/**
		 * @brief Unbinds this vertex buffer object from the currently bound vertex array object.
		 * 
		 * @return [VBO *] This same vertex buffer instance in order to allow for method chaining.
		 */
		inline VBO * unbind();

		/**
		 * @brief Buffers data into the vertex buffer object.
		 * 
		 * @param data A pointer to the data.
		 * @param dataSize The size of the data in bytes.
		 * @param usage The OpenGL usage flag for this data. (GL_STATIC_DRAW, GL_DYNAMIC_DRAW, etc...)
		 * @return [VBO *] This same vertex buffer instance in order to allow for method chaining.
		 */
		inline VBO * store(const void * data, unsigned int dataSize, GLenum usage);

		/**
		 * @brief Returns this vertex buffer's OpenGL ID.
		 * 
		 * @return unsigned int 
		 */
		inline unsigned int getID();

		/**
		 * @brief Creates a new vertex buffer object of the given type.
		 * 
		 * @param type The new vertex buffer's type. (GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, etc...)
		 * @return [VBO *] The resulting vertex buffer object instance.
		 */
		static VBO * create(GLenum type);

};

class VAO {

	private:
		/**
		 * @brief This vertex array object's OpenGL ID.
		 * 
		 */
		unsigned int id;

		/**
		 * @brief The vertex buffer objects bound to this vertex array as attribute lists.
		 * 
		 */
		map<unsigned int, VBO*> attributes;

		/**
		 * @brief A collection of all existing vertex array objects.
		 * 
		 */
		static vector<VAO*> vaos;

		/**
		 * @brief Constructs a new vertex array object.
		 * 
		 * @param id The vertex array object's OpenGL ID.
		 */
		VAO(unsigned int id);

	public:
		/**
		 * @brief Deletes the vertex array object from memory and destroys its instance.
		 * 
		 */
		~VAO();
		
		/**
		 * @brief Binds the vertex array object for manipulation.
		 * 
		 * @return [VAO *] This same vertex array instance in order to allow for method chaining.
		 */
		inline VAO * bind();

		/**
		 * @brief Binds the vertex array object for manipulation and enables the specified attribute lists.
		 * 
		 * @param attributes The attribute list indices to enable.
		 * @return [VAO *] This same vertex array instance in order to allow for method chaining.
		 */
		VAO * bind(const list<unsigned int> & attributes);

		/**
		 * @brief Unbinds the vertex array object.
		 * 
		 * @return [VAO *] This same vertex array instance in order to allow for method chaining.
		 */
		inline VAO * unbind();

		/**
		 * @brief Unbinds the vertex array object and disables the specified attribute lists.
		 * 
		 * @param attributes The attribute list indices to disable.
		 * @return [VAO *] This same vertex array instance in order to allow for method chaining.
		 */
		VAO * unbind(const list<unsigned int> & attributes);

		/**
		 * @brief Loads data into a single attribute list as a new vertex buffer object.
		 * 
		 * @param attribIndex The index of the attribute list to populate.
		 * @param data A pointer to the data.
		 * @param dataSize The data's size in bytes.
		 * @param vectorSize The vector size of the data. (1 for singular values, 2, 3 or 4 for vector values like positions or texture coordinates)
		 * @param type The type of data. (GL_FLOAT, GL_UNSIGNED_INT, etc...)
		 * @param usage The data's usage flag. (GL_STATIC_DRAW, GL_DYNAMIC_DRAW, etc...)
		 * @return [VAO *] This same vertex array instance in order to allow for method chaining.
		 */
		VAO * storeData(
			unsigned int attribIndex, 
			const void * data, 
			unsigned int dataSize, 
			unsigned int vectorSize, 
			GLenum type,
			GLenum usage);

		/**
		 * @brief Loads index data into the vertex array.
		 * 
		 * @param data A pointer to the data.
		 * @param dataSize The data's size in bytes.
		 * @param usage The data's usage flag. (GL_STATIC_DRAW, GL_DYNAMIC_DRAW, etc...)
		 * @return [VAO *] This same vertex array instance in order to allow for method chaining.
		 */
		VAO * storeIndices(
			const void * data, 
			unsigned int dataSize, 
			GLenum usage);

		/**
		 * @brief Links a vertex buffer object to this vertex array instance as if it was an attribute list.
		 * 
		 * @param attribIndex The attribute list index.
		 * @param vbo The vertex buffer object to link.
		 * @return [VAO *] This same vertex array instance in order to allow for method chaining.
		 */
		inline VAO * addVBO(unsigned int attribIndex, VBO* vbo);

		/**
		 * @brief Returns this vertex array's OpenGL ID.
		 * 
		 * @return [unsigned int] This vertex array object's OpenGL ID.
		 */
		inline unsigned int getID();

		/**
		 * @brief Creates and returns a new vertex array.
		 * 
		 * @return [VAO *] The resulting vertex array instance.
		 */
		static VAO * create();

		/**
		 * @brief Deletes all existing vertex array objects from memory. 
		 * Accessing vertex array instances after calling this method will cause errors.
		 * 
		 */
		static void cleanAll();

};