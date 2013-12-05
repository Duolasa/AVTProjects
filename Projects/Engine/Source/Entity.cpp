#include "Entity.h"

#include <iostream>

engine::Entity::Entity(){ }
engine::Entity::~Entity(){ }


void engine::Entity::createBufferObjects(){
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(2, VboId);

	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
	glEnableVertexAttribArray(VERTICES);
	glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glEnableVertexAttribArray(COLORS);
	glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(verts[0].XYZW));

	glBindBuffer(GL_UNIFORM_BUFFER, VboId[1]);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4)*2, 0, GL_STREAM_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, VboId[1]);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);

	//checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}