#include <vector>

#include <GLAD/glad.h>

#include "Display.h"

using namespace std;

#pragma once
class FBO {

	public:
		/**
		 * @brief Class representing a singular FBO attachment in OpenGL.
		 * 
		 */
		class Attachment {

			friend class FBO;

			public:
				/**
				 * @brief Texture ID or renderbuffer ID depending on whether the attachment is a texture attachment or renderbuffer attachment.
				 * 
				 */
				unsigned int id;

				/**
				 * @brief The GL_ATTACHMENT type and/or number for this specific attachment. 
				 * (GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_DEPTH_ATTACHMENT, etc...)
				 * 
				 */
				const GLenum glAttachment;

				/**
				 * @brief Indicates whether or not this attachment is a texture attachment.
				 * 
				 */
				const bool texture;

			private:
				/**
				 * @brief Constructs a single-sampled framebuffer attachment.
				 * 
				 * @param width The width in pixels of the attachment.
				 * @param height The height in pixels of the attachment.
				 * @param internalFormat The base internal format of the attachment. (GL_DEPTH_COMPONENT, GL_RGB, GL_RGBA, etc...)
				 * @param pixelFormat [** TEXTURE ATTACHMENTS ONLY **] The specific pixel format of the attachment. 
				 * (GL_DEPTH_COMPONENT32, GL_DEPTH24_STENCIL8 GL_RGB8, GL_RGBA8, etc...)
				 * @param dataType [** TEXTURE ATTACHMENTS ONLY **] The pixel data type. (GL_FLOAT, GL_UNSIGNED_INT, etc...)
				 * @param glAttachment The GL_ATTACHMENT type and/or number for this specific attachment.
				 * @param texture Whether or not this attachment is a texture attachment.
				 */
				Attachment(int width, int height, GLenum internalFormat, GLenum pixelFormat, GLenum dataType, GLenum glAttachment, bool texture);

				/**
				 * @brief Constructs a multisampled framebuffer attachment.
				 * 
				 * @param width The width in pixels of the attachment.
				 * @param height The height in pixels of the attachment.
				 * @param internalFormat The base internal format of the attachment. (GL_DEPTH_COMPONENT, GL_RGB, GL_RGBA, etc...)
				 * @param pixelFormat [** TEXTURE ATTACHMENTS ONLY **] The specific pixel format of the attachment. 
				 * (GL_DEPTH_COMPONENT32, GL_DEPTH24_STENCIL8 GL_RGB8, GL_RGBA8, etc...) 
				 * @param dataType [** TEXTURE ATTACHMENTS ONLY **] The pixel data type. (GL_FLOAT, GL_UNSIGNED_INT, etc...)
				 * @param glAttachment The GL_ATTACHMENT type and/or number for this specific attachment.
				 * @param samples The number of samples per pixel. (2, 4, or 8)
				 * @param texture Whether or not this attachment is a texture attachment.
				 */
				Attachment(int width, int height, GLenum internalFormat, GLenum pixelFormat, GLenum dataType, GLenum glAttachment, int samples, bool texture);

			public:
				/**
				 * @brief Destroys the framebuffer attachment.
				 * 
				 */
				~Attachment();

		};


	private:
		/**
		 * @brief This framebuffer's ID.
		 * 
		 */
		unsigned int id;

		/**
		 * @brief This framebuffer's width in pixels.
		 * 
		 */
		const int width;

		/**
		 * @brief This framebuffer's height in pixels.
		 * 
		 */
		const int height;

		/**
		 * @brief This framebuffer's number of samples per pixel.
		 * 
		 */
		const int samples = 1;

		/**
		 * @brief This framebuffer's list of attachments.
		 * 
		 */
		vector<Attachment*> attachments;

		/**
		 * @brief The list of draw buffers for this framebuffer. (GL_COLOR_ATTACHMENTX)
		 * 
		 */
		vector<GLenum> drawBuffers;

		/**
		 * @brief Constructs a new framebuffer object with the specified attributes.
		 * 
		 * @param id The framebuffer's ID.
		 * @param width The framebuffer's width in pixels.
		 * @param height The framebuffer's height in pixels.
		 * @param samples The framebuffer's number of samples per pixel. (1, 2, 4, or 8)
		 */
		FBO(unsigned int id, int width, int height, int samples);

	public:
		
		/**
		 * @brief Destroys the framebuffer object.
		 * 
		 */
		~FBO();

		/**
		 * @brief Adds an attachment to the framebuffer.
		 * 
		 * @param internalFormat The base internal format of the attachment. (GL_DEPTH_COMPONENT, GL_RGB, GL_RGBA, etc...)
		 * @param pixelFormat [** TEXTURE ATTACHMENTS ONLY **] The specific pixel format of the attachment. 
		 * (GL_DEPTH_COMPONENT32, GL_DEPTH24_STENCIL8 GL_RGB8, GL_RGBA8, etc...)
		 * @param dataType [** TEXTURE ATTACHMENTS ONLY **] The pixel data type. (GL_FLOAT, GL_UNSIGNED_INT, etc...)
		 * @param glAttachment The GL_ATTACHMENT type and/or number for this specific attachment.
		 * @param texture Whether or not this attachment is a texture attachment.
		 * @return [FBO *] This same framebuffer instance in order to allow for method chaining.
		 */
		FBO * addAttachment(GLenum internalFormat, GLenum pixelFormat, GLenum dataType, GLenum glAttachment, bool texture);

		/**
		 * @brief Binds the correct draw buffers for the framebuffer's current set of attachments.
		 * This method should be called only once after having added all the desired framebuffer
		 * attachments and before unbinding the framebuffer.
		 * 
		 * @return [FBO *] This same framebuffer instance in order to allow for method chaining.
		 */
		FBO * bindAttachments();

		/**
		 * @brief Binds the framebuffer as the current framebuffer allowing its use for rendering.
		 * 
		 * @return [FBO *] This same framebuffer instance in order to allow for method chaining.
		 */
		FBO * bind();

		/**
		 * @brief Unbinds the framebuffer, returning to the default display framebuffer for rendering.
		 * 
		 * @return [FBO *] This same framebuffer instance in order to allow for method chaining.
		 */
		FBO * unbind();

		/**
		 * @brief Copies this framebuffer's contents to another framebuffer.
		 * 
		 * @param dest The destination framebuffer.
		 * @param srcAttachment The source color attachment from which to copy from.
		 * @param destAttachment The destination color attachment to which to copy to.
		 * @return [FBO *] This same framebuffer instance in order to allow for method chaining.
		 */
		FBO * resolve(FBO * dest, GLenum srcAttachment, GLenum destAttachment);

		/**
		 * @brief Copies this framebuffer's contents to a display.
		 * 
		 * @param display The display to resolve to.
		 * @param srcAttachment The source color attachment from which to copy from.
		 * @return [FBO *] This same framebuffer instance in order to allow for method chaining.
		 */
		FBO * resolveToDisplay(Display * display, GLenum srcAttachment);

		/**
		 * @brief Returns whether or not this frambuffer is functional and ready for use.
		 * 
		 * @return true The framebuffer is correctly bound and complete.
		 * @return false The framebuffer is not complete or has conflicting attachments.
		 */
		bool checkFunctional();

		/**
		 * @brief Returns this framebuffer's list of attachments.
		 * 
		 * @return [vector<Attachment*>] The list of framebuffer attachments bound to this framebuffer.
		 */
		vector<Attachment*> getAttachments();

		/**
		 * @brief Creates a new framebuffer object.
		 * 
		 * @param id The framebuffer's ID.
		 * @param width The framebuffer's width in pixels.
		 * @param height The framebuffer's height in pixels.
		 * @param samples The framebuffer's number of samples per pixel. (1, 2, 4, or 8)
		 * @return [FBO *] The resulting framebuffer. 
		 */
		static FBO * create(int width, int height, int samples = 1);
};


