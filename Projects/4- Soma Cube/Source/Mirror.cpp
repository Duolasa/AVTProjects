#include "Mirror.h"
#include <iostream>

Mirror::Mirror()
{
}


bool Mirror::isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void Mirror::checkOpenGLError()
{
	if (isOpenGLError()) {
		std::cerr << "error" << std::endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
}



void Mirror::CreateFrameBuffer(int w, int h) {

	glGenFramebuffers(1, &FBOid);
	glBindFramebuffer(GL_FRAMEBUFFER, FBOid);
	CreateTexture(w, h);
	width = w;
	height = h;


	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Failed to create framebuffer: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;
}

void Mirror::CreateTexture(int w, int h) {  //creates an empty texture
	glGenTextures(1, &Textureid);
	glBindTexture(GL_TEXTURE_2D, Textureid);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, 0);

	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Textureid, 0);


}

void Mirror::AddDepthBuffer(){
	glBindFramebuffer(GL_FRAMEBUFFER, FBOid);
	glGenRenderbuffers(1, &DRBid);
	glBindRenderbuffer(GL_RENDERBUFFER, DRBid);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DRBid);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Failed to create depth buffer: " << glCheckFramebufferStatus(GL_FRAMEBUFFER) << std::endl;

}
void Mirror::Bind(){

	glBindRenderbuffer(GL_RENDERBUFFER, DRBid);

	glBindFramebuffer(GL_FRAMEBUFFER, FBOid);

	glActiveTexture(GL_TEXTURE0);

	glBindTexture(GL_TEXTURE_2D, Textureid);


}
void Mirror::Unbind(){

	glBindFramebuffer(GL_FRAMEBUFFER, NULL);
	glBindRenderbuffer(GL_RENDERBUFFER, NULL);

	glBindSampler(0, NULL);


}


Mirror::~Mirror()
{
}
