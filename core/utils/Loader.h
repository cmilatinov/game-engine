#include <string>
#include <iostream>

#pragma warning(push, 0)
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#pragma warning(pop)

#include "../math/GLVector.h"
#include "../objects/Texture.h"
#include "../objects/SkeletalMesh.h"
#include "../animation/Animation.h"

using namespace Assimp;
using glmath::vec2;
using glmath::vec3;
using std::cout;
using std::endl;
using std::string;

#pragma once
class Loader {

	private:

		struct vertexJointWeight {
			unsigned int jointID;
			float weight;
		};

		/**
		 * @brief An ASSIMP scene importer object used to load file data into skeletons, meshes, and skeletal animations.
		 * 
		 */
		Importer importer;
		
		/**
		 * @brief Normalizes the joint weights for each vertex ensuring each vertex has numWeightsPerVertex weights or fewer and that their sum is equal to 1.
		 *
		 */
		void normalizeWeights(
			vector<vertexJointWeight> * weights, /* Array of joint weight vectors, each corresponding to a single vertex */
			unsigned int numVertices, /* Total number of vertices */
			unsigned int numWeightsPerVertex, /* Maximum number of weights per vertex */
			unsigned int * dstJointIDs, /* Resulting array of joint IDs */
			float * dstWeights); /* Resulting array of joint weights */

		/**
		 * @brief Creates the joint hierarchy of a mesh and returns its root joint.
		 *
		 */
		Joint * loadJointHierarchy(aiNode * scene, aiMesh* mesh);

		/**
		 * @brief Creates and adds a joint's children joints.
		 *
		 */
		void loadJointChildren(aiNode * current, Joint * parent, aiMesh * mesh, mat4 & gInverse);

		/**
		 * @brief Creates an animation instance from the raw animation data.
		 *
		 */
		Animation * loadAnimation(aiAnimation * anim);

		/**
		 * @brief Finds the root joint node of the given mesh's skeleton.
		 *
		 */
		aiNode * findSkeletonRoot(aiNode * root, aiMesh * mesh);
		aiNode * _findSkeletonRoot(aiNode * node, aiMesh * mesh);

		/**
		 * @brief Copies an assimp matrix into a glmath mat4 struct.
		 *
		 */
		static void copy(aiMatrix4x4 * src, mat4 * dest);

	public:
		/**
		 * @brief Constructs a new loader object.
		 * 
		 */
		Loader();

		/**
		 * @brief Destroys the loader object.
		 * 
		 */
		~Loader();

		/**
		 * @brief Parses the first mesh found in the input file to OpenGL memory and returns an instance of it.
		 * This method returns a null pointer if the parsing process fails.
		 * 
		 * @param file The file to parse from.
		 * @return [Mesh *] The resulting mesh instance.
		 */
		Mesh * loadMesh(const char * file);

		/**
		 * @brief Loads a two dimensional texture from the input file into OpenGL memory and returns an instance of it.
		 * This method returns a null pointer if the loading process fails.
		 * 
		 * @param file The texture file to load.
		 * @param textureFilter The type for filtering to use for interpolation. (GL_NEAREST, GL_LINEAR, etc...)
		 * @return [Texture *] The resulting texture instance.
		 */
		Texture * loadTexture2D(const char* file, GLenum textureFilter);

};

