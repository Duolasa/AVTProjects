#include "Entity.h"

#include <iostream>

engine::Entity::Entity(){
	transfM = GetIdentity();
	translation = Vec3(0.0f);
	rotation = Quaternion(0.0f, X_AXIS);
}

engine::Entity::Entity(Vec3 pos, Quaternion q){
	transfM = GetIdentity();
	translation = pos;
	rotation = q;
}

engine::Entity::~Entity(){ }


void engine::Entity::destroyBufferObject(){
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(2, VboId);
	glDeleteVertexArrays(1, &VaoId);
}
void engine::Entity::draw(ShaderProgram *progShader, GLint UniformId){
	
	transfM = rotation.getMatrix() * GetTranslation(translation);

	glBindVertexArray(VaoId);
	glUseProgram(progShader->getId());

	glUniformMatrix4fv(UniformId, 1, GL_FALSE, transfM.matrix);	
	glDrawArrays(GL_TRIANGLES,0,size);
			
	glUseProgram(0);
	glBindVertexArray(0);
	//checkOpenGLError("ERROR: Could not draw scene.");
}

GLuint engine::Entity::getVboId(){
	return VboId[1];
}

void engine::Entity::addTranslation(Vec3 newTranslation){
	translation = translation + newTranslation;
}
void engine::Entity::addRotation(Quaternion newRotation){
	rotation = newRotation * rotation;
}
