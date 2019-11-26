#include "VAO.h"

// VAO
vector<VAO*> VAO::vaos;

VAO::VAO(unsigned int id){
	this->id = id;
	vaos.push_back(this);
}
VAO::~VAO(){
	for (auto it = attributes.begin(); it != attributes.end(); it++)
		delete it->second;

	glDeleteVertexArrays(1, &id);
}

inline VAO * VAO::bind() {
	glBindVertexArray(id);
	return this;
}
VAO* VAO::bind(const list<unsigned int> & attributes) {
	bind();

	for(unsigned int attribute: attributes)
		glEnableVertexAttribArray(attribute);

	return this;
}
inline VAO * VAO::unbind() {
	glBindVertexArray(0);
	return this;
}
VAO * VAO::unbind(const list<unsigned int> & attributes) {
	for(unsigned int attribute: attributes)
		glDisableVertexAttribArray(attribute);

	unbind();

	return this;
}

VAO * VAO::storeData(unsigned int attribIndex, const void * data, unsigned int dataSize, unsigned int vectorSize, GLenum type, GLenum usage) {

	// Create the Vertex Buffer Object
	VBO * buffer = VBO::create(GL_ARRAY_BUFFER)->bind();

	// Add it to the correct Vertex Array Object attribute list
	attributes[attribIndex] = buffer;

	// Store the data in the buffer
	buffer->store(data, dataSize, usage);

	// Create a proper pointer for the data
	if (type == GL_INT || type == GL_UNSIGNED_INT)
		glVertexAttribIPointer(attribIndex, vectorSize, type, 0, NULL);
	else
		glVertexAttribPointer(attribIndex, vectorSize, type, GL_FALSE, 0, NULL);

	// Unbind the buffer.
	buffer->unbind();

	return this;
}
VAO * VAO::storeIndices(const void* data, unsigned int dataSize, GLenum usage) {
	
	// Create the index buffer and write the data to it.
	VBO * buffer = VBO::create(GL_ELEMENT_ARRAY_BUFFER)
		->bind()
		->store(data, dataSize, usage);

	// Add it to this VAO in order to make sure it will be cleaned up.
	attributes[UINT32_MAX] = buffer;

	return this;

}

inline unsigned int VAO::getID() {
	return id;
}

inline VAO * VAO::addVBO(unsigned int attribIndex, VBO * vbo) {
	attributes[attribIndex] = vbo;
	return this;
}

VAO * VAO::create() {
	unsigned int id;
	glGenVertexArrays(1, &id);
	return new VAO(id);
}

void VAO::cleanAll() {
	for(VAO * vao: vaos)
		delete vao;
}

// VBO
VBO::VBO(unsigned int id, GLenum type) {
	this->id = id;
	this->type = type;
}
VBO::~VBO() {
	glDeleteBuffers(1, &id);
}

inline VBO * VBO::bind() {
	glBindBuffer(type, id);
	return this;
}
inline VBO * VBO::unbind() {
	glBindBuffer(type, 0);
	return this;
}

inline VBO * VBO::store(const void * data, unsigned int dataSize, GLenum usage) {
	glBufferData(type, dataSize, data, usage);
	return this;
}

inline unsigned int VBO::getID() {
	return id;
}

VBO * VBO::create(GLenum type) {
	unsigned int id;
	glGenBuffers(1, &id);
	return new VBO(id, type);
}