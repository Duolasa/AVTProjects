#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "ListManager.h"


namespace engine {


	// type == GL_VERTEX_SHADER || GL_FRAGMENT_SHADER
	class Shader {

	private:
		GLuint shaderId;
		GLenum shaderType;

		GLuint loadShader(GLenum type, const char *File);

	public:
		Shader();
		Shader(GLenum type, const char *File);
		~Shader();
		void loadVertexShader(const char *vsFile);
		void loadFragmentShader(const char *fsFile);
		GLuint getId();
		GLenum getshaderType();
		void delShader();

	};

	class ShaderProgram {
	private:
		//Shader vertexShader;
		//Shader fragmentShader;
		GLuint ProgramId;

	public:
		Shader vertexShader;
		Shader fragmentShader;
		GLuint vs;
		GLuint fs;

		ShaderProgram();
		ShaderProgram(Shader vertex, Shader fragment);
		~ShaderProgram();
		void destroyShaderProgram();
		void loadShaders(const char *vsFile, const char *fsFile);
		void loadShaders(Shader vertex, Shader fragment);
		void bindAttribute(GLuint index, GLchar *name);
		GLint getUniformLocation(const GLchar* uniform_name);
		GLint getUniformBlockIndex(const GLchar *name, const GLuint UBO);
		void bindProg();
		void unbindProg();
		void linkProg();
		void setProgram();
		GLuint getId();
	};

	typedef ListManager<ShaderProgram> SHADER_PROGRAM_LIST;
	ListManager<ShaderProgram>* ListManager<ShaderProgram>::_instance = 0;
}

#endif //SHADER_H
