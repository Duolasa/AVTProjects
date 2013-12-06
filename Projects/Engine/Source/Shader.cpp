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

/////////////////////////////////////////////////////////////////////// SHADER

engine::Shader::Shader(){}

engine::Shader::Shader(GLenum type, const char *File){ 
	shaderId = loadShader(type, File);
	shaderType = type;
}

engine::Shader::~Shader(){
	glDeleteShader(shaderId);
}

void engine::Shader::delShader(){
	glDeleteShader(shaderId);
}

GLuint engine::Shader::loadShader(GLenum type, const char *File){

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

void engine::Shader::loadVertexShader(const char *vsFile){
	shaderId = loadShader(GL_VERTEX_SHADER, vsFile);
	shaderType = GL_VERTEX_SHADER;
}

void engine::Shader::loadFragmentShader(const char *fsFile){
	shaderId = loadShader(GL_FRAGMENT_SHADER, fsFile);
	shaderType = GL_FRAGMENT_SHADER;
}

GLuint engine::Shader::getId(){
	return shaderId;
}

GLuint engine::Shader::getshaderType (){
	return shaderType;
}

/////////////////////////////////////////////////////////////////////// PROGRAM SHADER

engine::ShaderProgram::ShaderProgram(){}

engine::ShaderProgram::ShaderProgram(engine::Shader vertex, engine::Shader fragment){
	vertexShader = vertex;
	fragmentShader = fragment;

	setProgram();
}
engine::ShaderProgram::~ShaderProgram(){}

void engine::ShaderProgram::destroyShaderProgram(){
	glUseProgram(0);
	glDetachShader(ProgramId, vertexShader.getId());
	glDetachShader(ProgramId, fragmentShader.getId());
	//glDeleteShader(fragmentShader.getId());
	//glDeleteShader(vertexShader.getId());
	glDeleteProgram(ProgramId);
}

void engine::ShaderProgram::loadShaders(const char *vsFile, const char *fsFile){
	vertexShader.loadVertexShader(vsFile);
	fragmentShader.loadFragmentShader(fsFile);

	setProgram();
}

void engine::ShaderProgram::loadShaders(engine::Shader vertex, engine::Shader fragment){
	vertexShader = vertex;
	fragmentShader = fragment;
	vs = vertex.getId();
	fs = fragment.getId();
	setProgram();
}

void engine::ShaderProgram::bindProg(){
	glUseProgram(ProgramId);
}

void engine::ShaderProgram::unbindProg(){
	glUseProgram(0);
}

void engine::ShaderProgram::bindAttribute(GLuint index, GLchar *name){
	glBindAttribLocation(ProgramId, index, name);
}

GLint engine::ShaderProgram::getUniformLocation(const GLchar* uniform_name){
	return glGetUniformLocation(ProgramId, uniform_name);
}

GLint engine::ShaderProgram::getUniformBlockIndex(const GLchar *name, const GLuint UBO){
	GLint UboId = glGetUniformBlockIndex(ProgramId, name);
	glUniformBlockBinding(ProgramId, UboId, UBO);
	return UboId;
}

void engine::ShaderProgram::linkProg(){
	glLinkProgram(ProgramId);
	validateProgram(ProgramId);
	
}

GLuint engine::ShaderProgram::getId(){
	return ProgramId;
}

void engine::ShaderProgram::setProgram(){
	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, vertexShader.getId()); 
	glAttachShader(ProgramId, fragmentShader.getId()); 
	
}