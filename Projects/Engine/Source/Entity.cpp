#include "Entity.h"

#include <iostream>

engine::Entity::Entity(){ }
engine::Entity::~Entity(){ }


void engine::Entity::destroyBufferObject(){
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(2, VboId);
	glDeleteVertexArrays(1, &VaoId);
}
void engine::Entity::draw(ShaderProgram *progShader, GLint UniformId, Mat4 m){
	glBindVertexArray(VaoId);
	glUseProgram(progShader->getId());

	glUniformMatrix4fv(UniformId, 1, GL_FALSE, m.matrix);	
	glDrawArrays(GL_TRIANGLES,0,size);
			
	glUseProgram(0);
	glBindVertexArray(0);
	//checkOpenGLError("ERROR: Could not draw scene.");
}

GLuint engine::Entity::getVboId(){
	return VboId[1];
}