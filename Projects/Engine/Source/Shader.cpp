#include "Shader.h"

#include <string>
#include <fstream>
#include <iostream>


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


engine::Shader::Shader(){ }

engine::Shader::~Shader(){
	glUseProgram(0);
	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);
	glDeleteProgram(ProgramId);
}

void engine::Shader::loadShaders(const char *vsFile, const char *fsFile){
	engine::Shader::loadVertexShader(vsFile);
	engine::Shader::loadFragmentShader(fsFile);

	setProgram();
}

GLuint engine::Shader::loadShader(GLenum type, const char *File){

	GLuint shaderId = glCreateShader(type); 

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

	glShaderSource(shaderId, 1, &shaderText, 0); 
	glCompileShader(shaderId); 
	validateShader(shaderId, File);

	return shaderId;
}

void engine::Shader::loadVertexShader(const char *vsFile){
	engine::Shader::VertexShaderId = loadShader(GL_VERTEX_SHADER, vsFile);
}

void engine::Shader::loadFragmentShader(const char *fsFile){
	engine::Shader::FragmentShaderId = loadShader(GL_FRAGMENT_SHADER, fsFile);
}

void engine::Shader::bindProg(){
	glUseProgram(ProgramId);
}

void engine::Shader::unbindProg(){
	glUseProgram(0);
}

void engine::Shader::bindAttribute(GLuint index, GLchar *name){
	glBindAttribLocation(ProgramId, index, name);
}

GLint engine::Shader::getUniformLocation(const GLchar* uniform_name){
	return glGetUniformLocation(ProgramId, uniform_name);
}

GLint engine::Shader::getUniformBlockIndex(const GLchar *name, const GLuint UBO){
	GLint UboId = glGetUniformBlockIndex(ProgramId, name);
	glUniformBlockBinding(ProgramId, UboId, UBO);
	return UboId;
}

void engine::Shader::linkProg(){
	glLinkProgram(ProgramId);
	validateProgram(ProgramId);
	
}

unsigned int engine::Shader::id(){
	return ProgramId;
}

void engine::Shader::setProgram(){
	ProgramId = glCreateProgram();
    glAttachShader(ProgramId, VertexShaderId); 
    glAttachShader(ProgramId, FragmentShaderId); 
}