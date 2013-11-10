#include "TangramPiece.h"


TangramPiece::TangramPiece()
{
}

void TangramPiece::createBuffers(){
  glGenVertexArrays(1, &VaoId);
  glBindVertexArray(VaoId);
  glGenBuffers(2, VboId);

  glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(TangramPiece::Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(VERTICES);
  glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
  glEnableVertexAttribArray(COLORS);
  glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) sizeof(vertices[0].XYZW));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VboId[1]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * indices.size(), &indices[0], GL_STATIC_DRAW);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glDisableVertexAttribArray(VERTICES);
  glDisableVertexAttribArray(COLORS);

}

void TangramPiece::draw(GLint UniformId){

  glBindVertexArray(VaoId);
  glUniformMatrix4fv(UniformId, 1, GL_TRUE, transformationMatrix);
//  glDrawArrays(GL_TRIANGLES, 0, indices.size());
 glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, (GLvoid*) 0);

  glBindVertexArray(0);

}


TangramPiece::~TangramPiece()
{
}
