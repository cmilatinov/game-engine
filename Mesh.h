#include "VAO.h"

class Loader;

#pragma once
class Mesh {

	friend class Loader;
	
	private:
		/**
		 * @brief An instance of the vertex array object corresponding to this mesh.
		 * 
		 */
		VAO * vao;

		/**
		 * @brief The number of vertices composing the mesh.
		 * 
		 */
		unsigned int vertexCount;

		/**
		 * @brief Constructs a new mesh object.
		 * 
		 * @param vao The vertex array object in which the mesh data is found.
		 * @param vertexCount The number of vertices composing the mesh.
		 */
		Mesh(VAO * vao, unsigned int vertexCount);

	public:
		/**
		 * @brief Destroys the mesh object.
		 * 
		 */
		~Mesh();

		/**
		 * @brief Returns this mesh's vertex array object.
		 * 
		 * @return [VAO *] The vertex array object in which the mesh's data is found. 
		 */
		inline VAO * getVAO() {
			return vao;
		}

		/**
		 * @brief Returns this mesh's vertex count.
		 * 
		 * @return [unsigned int] The number of vertices composing the mesh.
		 */
		inline unsigned int getVertexCount() {
			return vertexCount;
		}

};

