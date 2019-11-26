#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Loader.h"

Loader::Loader() {};
Loader::~Loader() {};

void Loader::normalizeWeights(vector<vertexJointWeight>* weights, int numVertices, int numWeightsPerVertex, unsigned int * dstJointIDs, float * dstWeights) {

	// Loop over all vertices.
	for (unsigned int i = 0; i < numVertices; i++) {
		
		// Add padding joint weights to vertices with less than numWeightsPerVertex weights.
		while (weights[i].size() < numWeightsPerVertex)
			weights[i].push_back({ UINT32_MAX, 0.0f });

		// Sum the weights.
		float sum = 0;
		for (vertexJointWeight jw : weights[i])
			sum += jw.weight;

		// Write the joint id and normalized weights to the output arrays.
		for (unsigned int j = 0; j < weights[i].size(); j++) {
			vertexJointWeight jw = weights[i][j];
			
			dstJointIDs[(i * numWeightsPerVertex) + j] = jw.jointID;
			dstWeights[(i * numWeightsPerVertex) + j] = jw.weight / sum;
		}

 	}

}

Joint * Loader::loadJointHierarchy(aiNode * scene, aiMesh * mesh) {

	// Find the root node of the skeleton.
	aiNode * root = findSkeletonRoot(scene, mesh);
	if (root == nullptr)
		return nullptr;

	// Find the corresponding bone.
	aiBone* bone = nullptr;
	for (unsigned int i = 0; i < mesh->mNumBones; i++)
		if (string(mesh->mBones[i]->mName.C_Str()) == string(root->mName.C_Str())) {
			bone = mesh->mBones[i];
			break;
		}

	// Create the root joint.
	Joint * rootJoint = new Joint;
	rootJoint->name = root->mName.C_Str();
	memcpy_s(&rootJoint->offset, sizeof(mat4), &bone->mOffsetMatrix, sizeof(aiMatrix4x4));

	// Load its children.
	loadJointChildren(root, rootJoint, mesh);

	// Return it.
	return rootJoint;
}
void Loader::loadJointChildren(aiNode * current, Joint * parent, aiMesh * mesh){

	// Loop for all children nodes of the root node. 
	// The base condition of the function is stumbling upon a joint with no children.
	// The function would then simply return without further recursion.
	for (unsigned int i = 0; i < current->mNumChildren; i++) {
		
		aiNode * node = current->mChildren[i];
		Joint * child = nullptr;

		// Attempt to find the matching bone.
		for (unsigned int j = 0; j < mesh->mNumBones; j++) {

			aiBone * bone = mesh->mBones[j];

			// Create and add the joint as a child joint of its parent.
			if (string(bone->mName.C_Str()) == string(node->mName.C_Str())) {
				
				// Create the new joint.
				Joint * tbi = new Joint;
				tbi->index = j;
				tbi->name = node->mName.C_Str();
				memcpy_s(&tbi->offset, sizeof(mat4), &bone->mOffsetMatrix, sizeof(aiMatrix4x4));
				child = tbi;
				cout << "Created joint " << tbi->name << " with parent " << parent->name << endl;

				// Add it to the parent joint.
				if (parent != nullptr)
					parent->children.push_back(tbi);
				
				break;
			}

		}

		// If a child joint was created and added, create and load its children joints.
		if(child != nullptr)
			loadJointChildren(node, child, mesh);

	}
}

aiNode * Loader::findSkeletonRoot(aiNode * root, aiMesh * mesh) {
	for (unsigned int i = 0; i < mesh->mNumBones; i++)
		if (string(root->mName.C_Str()) == (mesh->mBones[i]->mName.C_Str()))
			return root;
	
	return _findSkeletonRoot(root, mesh);
}
aiNode * Loader::_findSkeletonRoot(aiNode * node, aiMesh * mesh) {

	// Loop for all children of the node.
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		
		aiNode * child = node->mChildren[i];

		// Check if the node is a bone of the mesh.
		for (unsigned int j = 0; j < mesh->mNumBones; j++) {

			aiBone * bone = mesh->mBones[j];
			
			// If it is, return the current node.
			if (string(bone->mName.C_Str()) == string(child->mName.C_Str()))
				return child;
		}

		// If not, search the children of this child node.
		return _findSkeletonRoot(child, mesh);
	}

	return nullptr;
}

Mesh * Loader::loadMesh(const char * file) {

	static const unsigned int INDICES_PER_FACE = 3;
	static const unsigned int NUM_WEIGHTS_PER_VERTEX = 3;

	const aiScene * scene = importer.ReadFile(string("./Assets/Models/") + file,
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals);

	// Error loading file or file does not contain any meshes.
	if(!scene || !scene->HasMeshes())
		return nullptr;

	// Retrieve first mesh.
	aiMesh * mesh = scene->mMeshes[0];

	// Indices
	unsigned int * indices = new unsigned int[mesh->mNumFaces * INDICES_PER_FACE];

	// Vertices
	float * vertices = reinterpret_cast<float*>(mesh->mVertices);

	// Normals
	float * normals = reinterpret_cast<float*>(mesh->mNormals);

	// UVs
	float * uvs = new float[mesh->mNumVertices * 2];

	// Vertex joint weights and IDs
	float * weights = new float[mesh->mNumVertices * NUM_WEIGHTS_PER_VERTEX];
	unsigned int * jointIDs = new unsigned int[mesh->mNumVertices * NUM_WEIGHTS_PER_VERTEX];

	// Skeleton
	//vector<SkeletalMesh::Joint> joints;

	// If the mesh has a skeleton
	if (mesh->HasBones()) {
		vector<vertexJointWeight> * vertexWeights = new vector<vertexJointWeight>[mesh->mNumVertices];

		for (unsigned int i = 0; i < mesh->mNumBones; i++) {

			aiBone * bone = mesh->mBones[i];
			
			for (unsigned int w = 0; w < bone->mNumWeights; w++) {
				aiVertexWeight vw = bone->mWeights[w];

				if (vertexWeights[vw.mVertexId].size() >= NUM_WEIGHTS_PER_VERTEX)
					break;

				vertexJointWeight jw = {
					i, vw.mWeight
				};

				vertexWeights[vw.mVertexId].push_back(jw);
			}
		}

		// Format the weights and joint IDs
		normalizeWeights(vertexWeights, mesh->mNumVertices, NUM_WEIGHTS_PER_VERTEX, jointIDs, weights);

		// Load the skeleton
		Joint * root = loadJointHierarchy(scene->mRootNode, mesh);

		delete[] vertexWeights;
	}

	// Arrange indices in continuous array.
	for (unsigned int fNum = 0; fNum < mesh->mNumFaces; fNum++)
		memcpy_s(
			indices + (fNum * INDICES_PER_FACE),			// Copy to current face index * number of indices in a face
			INDICES_PER_FACE * sizeof(unsigned int),		// Copy number of indices * their size in bytes
			mesh->mFaces[fNum].mIndices,					// Copy from current face index array				
			INDICES_PER_FACE * sizeof(unsigned int)			// Copy number of indices * their size in bytes
		);

	// Arrange texture coordinates to two dimensional vector array.
	for (unsigned int tNum = 0; tNum < mesh->mNumVertices; tNum++)
		memcpy_s(
			uvs + tNum * 2,								// Copy to current UV index * size of UV
			sizeof(vec2),								// Copy size of UV in bytes
			mesh->mTextureCoords[0] + tNum,				// Copy from current UV
			sizeof(vec2)								// Copy size of UV in bytes
		);

	// Create the VAO representing the mesh.
	VAO * vao = VAO::create()
		->bind()
		->storeIndices(indices, mesh->mNumFaces * INDICES_PER_FACE * sizeof(unsigned int), GL_STATIC_DRAW)
		->storeData(0, vertices, mesh->mNumVertices * sizeof(vec3), 3, GL_FLOAT, GL_STATIC_DRAW)
		->storeData(1, normals, mesh->mNumVertices * sizeof(vec3), 3, GL_FLOAT, GL_STATIC_DRAW)
		->storeData(2, uvs, mesh->mNumVertices * sizeof(vec2), 2, GL_FLOAT, GL_STATIC_DRAW)
		->storeData(3, jointIDs, mesh->mNumVertices * NUM_WEIGHTS_PER_VERTEX * sizeof(unsigned int), NUM_WEIGHTS_PER_VERTEX, GL_UNSIGNED_INT, GL_STATIC_DRAW)
		->storeData(4, weights, mesh->mNumVertices * NUM_WEIGHTS_PER_VERTEX * sizeof(float), NUM_WEIGHTS_PER_VERTEX, GL_FLOAT, GL_STATIC_DRAW)
		->unbind();

	// Clean up.
	delete[] indices;
	delete[] uvs;
	delete[] weights;
	delete[] jointIDs;

	// Return the mesh.
	return new Mesh(vao, mesh->mNumFaces * INDICES_PER_FACE);
}

Texture * Loader::loadTexture2D(const char * file, GLenum textureFilter) {

	// Load the texture in RAM
	int width, height, nbChannels;
	unsigned char * data = stbi_load((string("./Assets/Textures/") + file).c_str(), &width, &height, &nbChannels, STBI_rgb_alpha);

	// Return a null pointer if the texture has not been loaded correctly 
	if (data == NULL)
		return nullptr;

	// Create texture and buffer its data in OpenGL
	unsigned int texID;
	glGenTextures(1, &texID);
	glBindTexture(GL_TEXTURE_2D, texID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, textureFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, textureFilter);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free the texture from RAM
	stbi_image_free(data);

	// Return the newly created texture object
	return new Texture(GL_TEXTURE_2D, texID);
}