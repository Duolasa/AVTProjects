#ifndef OPENGL_ERRORS_H
#define OPENGL_ERRORS_H

#include <iostream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"


/////////////////////////////////////////////////////////////////////// ERRORS

namespace engine {

	bool isOpenGLError() {
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

	void checkOpenGLError(std::string error)
	{
		if(isOpenGLError()) {
			std::cerr << error << std::endl;
			exit(EXIT_FAILURE);
		}
	}

}
#endif // OPENGLERRORS_H