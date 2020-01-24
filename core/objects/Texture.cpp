#include "Texture.h"

Texture::Texture(GLenum type, unsigned int id, unsigned int samples) :
	type(type), id(id), samples(samples) {}

Texture::~Texture() {
	glDeleteTextures(1, &id);
}