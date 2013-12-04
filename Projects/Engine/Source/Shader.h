#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "ListManager.h"

namespace engine {

	class Shader {

	private:
		GLuint VertexShaderId;
		GLuint FragmentShaderId;
		GLuint ProgramId;

		GLuint loadShader(GLenum type, const char *File);
		//static void validateProgram(GLuint program);
		//static void validateShader(GLuint shader, const char* file = 0);
		//static std::string textFileRead(const char *fileName);

	public:
		Shader();
		~Shader();
		void loadShaders(const char *vsFile, const char *fsFile);
		void loadVertexShader(const char *vsFile);
		void loadFragmentShader(const char *fsFile);
		void bindProg();
		void unbindProg(); 
		void bindAttribute(GLuint index, GLchar *name);
		GLint getUniformLocation(const GLchar* uniform_name);
		GLint getUniformBlockIndex(const GLchar *name, const GLuint UBO);
		void linkProg();
		void setProgram();
		unsigned int id();
	};

	typedef ListManager<Shader> SHADER_LIST;
	ListManager<Shader>* ListManager<Shader>::_instance = 0;
}

#endif //SHADER_H
