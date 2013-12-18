#ifndef SHADER_H
#define SHADER_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "ListManager.h"


namespace engine {


	// type == GL_VERTEX_SHADER || GL_FRAGMENT_SHADER
	class Shader {

	private:
		GLuint shaderId;
		GLenum shaderType;


		static std::string textFileRead(const char *fileName) {
			std::string fileString = std::string();
			std::string line = std::string(); 

			std::ifstream file(fileName);
			if(file.is_open()) { 
					while(!file.eof()) {
							getline(file, line); 
							fileString.append(line); 
							fileString.append("\n"); 
					}
					file.close(); 
			}

			return fileString; 
		}

		static void validateShader(GLuint shader, const char* file = 0) {
			const unsigned int BUFFER_SIZE = 512;
			char buffer[BUFFER_SIZE];
			memset(buffer, 0, BUFFER_SIZE);
			GLsizei length = 0;
    
			glGetShaderiv(shader,GL_COMPILE_STATUS,&length);
			if (GL_FALSE == length){ 
				glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer); 
				std::cerr << "Shader " << shader << " (" << (file?file:"") << ") compile error: " << buffer << std::endl;
			}
		}

		GLuint loadShader(GLenum type, const char *File){
			GLuint shader = glCreateShader(type); 

			std::string sText = textFileRead(File);
			const char *shaderText = sText.c_str();

			if (shaderText == NULL){
				if(type == GL_VERTEX_SHADER){
					std::cerr << "Vertex shader file not found." << std::endl; 
				}else{
					std::cerr << "Fragment shader file not found." << std::endl; 
				}
				return shaderId;
			}

			glShaderSource(shader, 1, &shaderText, 0); 
			glCompileShader(shader); 
			validateShader(shader, File);
			return shader;
		}

	public:

		Shader(){}

		Shader(GLenum type){
			shaderType = type; 
			shaderId = 0;
		}


		Shader(GLenum type, const char *File){
			shaderId = loadShader(type, File);
			shaderType = type;
		}

		~Shader(){
			//glDeleteShader(shaderId);
			//delete this;
		}

		void loadShader(const char *sFile){
			shaderId = loadShader(shaderType, sFile);
		}
		
		GLuint getShaderId(){
			return shaderId;
		}

		GLenum getshaderType(){
			return shaderType;
		}

		void deleteShader(){
			glDeleteShader(shaderId);
		}

	};

	class ShaderProgram {
	private:
		Shader vertexShader;
		Shader fragmentShader;
		GLuint ProgramId;

		static void validateProgram(GLuint program) {
			const unsigned int BUFFER_SIZE = 512;
			char buffer[BUFFER_SIZE];
			memset(buffer, 0, BUFFER_SIZE);
			GLsizei length = 0;
    
			glValidateProgram(program); 
			GLint status;
			glGetProgramiv(program, GL_VALIDATE_STATUS, &status); 
			if (status == GL_FALSE){ 
				std::cerr << "Error validating shader " << program << std::endl; 
				glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer); 
				std::cerr << "Program " << program << " link error: " << buffer << std::endl; 
			}
		}

	public:

		ShaderProgram(){
			vertexShader = Shader(GL_VERTEX_SHADER);
			fragmentShader = Shader(GL_FRAGMENT_SHADER);
		}

		ShaderProgram(Shader vertex, Shader fragment){
			loadShaders(vertex, fragment);
		}


		~ShaderProgram(){
			//destroyShaderProgram();
			//delete this;
		}

		void destroyShaderProgram(){
			glUseProgram(0);
			glDetachShader(ProgramId, vertexShader.getShaderId());
			glDetachShader(ProgramId, fragmentShader.getShaderId());

			glDeleteProgram(ProgramId);
		}

		void destroyAllShaderProgram(){
			glUseProgram(0);
			glDetachShader(ProgramId, vertexShader.getShaderId());
			glDetachShader(ProgramId, fragmentShader.getShaderId());

			vertexShader.deleteShader();
			fragmentShader.deleteShader();

			glDeleteProgram(ProgramId);
		}

		void loadShaders(const char *vsFile, const char *fsFile){
			ProgramId = glCreateProgram();

			vertexShader.loadShader(vsFile);
			fragmentShader.loadShader(fsFile);

			glAttachShader(ProgramId, vertexShader.getShaderId()); 
			glAttachShader(ProgramId, fragmentShader.getShaderId()); 
		}

		void loadShaders(Shader vertex, Shader fragment){
			ProgramId = glCreateProgram();
			vertexShader = vertex;
			fragmentShader = fragment;

			glAttachShader(ProgramId, vertexShader.getShaderId()); 
			glAttachShader(ProgramId, fragmentShader.getShaderId());
		}

		void bindAttribute(GLuint index, GLchar *name){
			glBindAttribLocation(ProgramId, index, name);
		}


		GLint getUniformLocation(const GLchar* uniform_name){
			return glGetUniformLocation(ProgramId, uniform_name);
		}

		GLint getUniformBlockIndex(const GLchar *name, const GLuint UBO){
			GLint UboId = glGetUniformBlockIndex(ProgramId, name);
			glUniformBlockBinding(ProgramId, UboId, UBO);
			return UboId;
		}

		void linkProg(){
			glLinkProgram(ProgramId);
			validateProgram(ProgramId);
		}

		GLuint getProgramId(){
			return ProgramId;
		}
	};

	typedef ListManager<ShaderProgram> SHADER_PROGRAM_LIST;
	ListManager<ShaderProgram>* ListManager<ShaderProgram>::_instance = 0;
}

#endif //SHADER_H
