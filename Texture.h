#include <glad/glad.h>

class Loader;

#pragma once
class Texture {

	friend class Loader;

	private:
		/**
		 * @brief This texture's OpenGL ID.
		 * 
		 */
		const unsigned int id;

		/**
		 * @brief This texture's number of samples per pixel.
		 * 
		 */
		const unsigned int samples;

		/**
		 * @brief This texture's type. (GL_TEXTURE_2D, GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_CUBE_MAP, etc...)
		 * 
		 */
		GLenum type;

		/**
		 * @brief Constructs a new texture object with the specified properties.
		 * 
		 * @param type The texture's type.
		 * @param id The texture's OpenGL ID.
		 * @param samples The texture's number of samples per pixel.
		 */
		Texture(GLenum type, unsigned int id, unsigned int samples = 1);
	
	public:
		/**
		 * @brief Deletes the texture from memory and destroys the texture object.
		 * 
		 */
		~Texture();

		/**
		 * @brief Returns this texture's type.
		 * 
		 * @return [GLenum] The OpenGL texture type corresponding to this texture instance.
		 */
		inline GLenum getType() { return type; };

		/**
		 * @brief Returns this texture's ID.
		 * 
		 * @return [GLenum] The OpenGL texture ID corresponding to this texture instance.
		 */
		inline unsigned int getID() { return id; };

		/**
		 * @brief Returns this texture's number of samples per pixel.
		 * 
		 * @return [GLenum] This texture instance's number of samples per pixel.
		 */
		inline unsigned int getNumSamples() { return samples; };
		
		/**
		 * @brief Returns whether or not this texture is multisampled or not. (samples > 1)
		 * 
		 * @return true The texture is multisampled.
		 * @return false The texture is single-sampled.
		 */
		inline bool isMultisampled() { return samples > 1; };
		
};

