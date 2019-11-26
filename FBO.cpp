#include "FBO.h"

FBO::FBO(unsigned int id, int width, int height, int samples) :
	id(id), width(width), height(height), samples(samples) {}

FBO::~FBO(){

	for (Attachment * a : attachments)
		delete a;
	
	glDeleteFramebuffers(1, &id);

}

FBO * FBO::addAttachment(GLenum internalFormat, GLenum pixelFormat, GLenum dataType, GLenum glAttachment, bool texture) {
	
	Attachment * attachment;
	
	if (samples > 1)
		attachment = new Attachment(width, height, internalFormat, pixelFormat, dataType, glAttachment, samples, texture);
	else
		attachment = new Attachment(width, height, internalFormat, pixelFormat, dataType, glAttachment, texture);

	attachments.push_back(attachment);

	return this;
}

FBO * FBO::bindAttachments() {
	drawBuffers.clear();
	for (unsigned int c = 0; c < attachments.size(); c++)
		if (attachments[c]->glAttachment >= GL_COLOR_ATTACHMENT0 && attachments[c]->glAttachment <= GL_COLOR_ATTACHMENT31)
			drawBuffers.push_back(attachments[c]->glAttachment);

	glDrawBuffers(static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());

	return this;
}

FBO * FBO::bind() {
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	glDrawBuffers(static_cast<GLsizei>(drawBuffers.size()), drawBuffers.data());
	return this;
}

FBO * FBO::unbind() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);
	return this;
}

FBO * FBO::resolve(FBO * dest, GLenum srcAttachment, GLenum destAttachment) {
	if (dest == NULL)
		return this;

	glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
	glReadBuffer(srcAttachment);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, dest != NULL ? dest->id : 0);
	glDrawBuffer(destAttachment);
	glBlitFramebuffer(0, 0, width, height, 0, 0, dest->width, dest->height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	return this;
}

FBO * FBO::resolveToDisplay(Display * dest, GLenum srcAttachment) {
	if (dest == NULL)
		return this;

	glBindFramebuffer(GL_READ_FRAMEBUFFER, id);
	glReadBuffer(srcAttachment);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glDrawBuffer(GL_BACK);
	vec2 size = dest->getDisplaySize();
	glBlitFramebuffer(0, 0, width, height, 0, 0, size.x, size.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
	return this;
}

bool FBO::checkFunctional() {
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	bool flag = glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
	unbind();
	return flag;
}

vector<FBO::Attachment*> FBO::getAttachments() {
	return attachments;
}

FBO* FBO::create(int width, int height, int samples) {
	unsigned int fbo;
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	return new FBO(fbo, width, height, samples);
}

FBO::Attachment::Attachment(int width, int height, GLenum internalFormat, GLenum pixelFormat, GLenum dataType, GLenum glAttachment, bool texture) :	glAttachment(glAttachment), texture(texture) {
	if (texture) {
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D, id);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, pixelFormat, dataType, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glFramebufferTexture2D(GL_FRAMEBUFFER, glAttachment, GL_TEXTURE_2D, id, 0);
		glBindTexture(GL_TEXTURE_2D, 0);
	} else {
		glGenRenderbuffers(1, &id);
		glBindRenderbuffer(GL_RENDERBUFFER, id);
		glRenderbufferStorage(GL_RENDERBUFFER, internalFormat, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, glAttachment, GL_RENDERBUFFER, id);
	}
}

FBO::Attachment::Attachment(int width, int height, GLenum internalFormat, GLenum pixelFormat, GLenum dataType, GLenum glAttachment, int samples, bool texture) : glAttachment(glAttachment), texture(texture) {
	if (texture){
		glGenTextures(1, &id);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, id);
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, false);
		glFramebufferTexture2D(GL_FRAMEBUFFER, glAttachment, GL_TEXTURE_2D_MULTISAMPLE, id, 0);
		glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	} else {
		glGenRenderbuffers(1, &id);
		glBindRenderbuffer(GL_RENDERBUFFER, id);
		glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalFormat, width, height);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, glAttachment, GL_RENDERBUFFER, id);
	}
}

FBO::Attachment::~Attachment() {
	if (texture)
		glDeleteTextures(1, &id);
	else
		glDeleteRenderbuffers(1, &id);
}