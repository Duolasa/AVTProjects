#include "TangramPiece.h"


TangramPiece::TangramPiece()
{
  transformationMatrix = matrixManipulator.GetIdentity();
  intermediateMatrix = matrixManipulator.GetIdentity();
  resetPiece();
 

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

  if (dirtyMatrix){
    recalculateMatrix();
  }
  
  glBindVertexArray(VaoId);

  if (!beingAnimated){
    glUniformMatrix4fv(UniformId, 1, GL_TRUE, transformationMatrix);
  } else{
    glUniformMatrix4fv(UniformId, 1, GL_TRUE, intermediateMatrix);
  }

    // glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_BYTE, (GLvoid*) 0);
    glBindVertexArray(0);
  
}
 
void TangramPiece::changeIntermediateMatrix(float frame){  //could be done with lerp

  Vector axis;
  float angle;
  quaternionManipulator.qToAngleAxis(Rotation, angle, axis);
  Quaternion intermediateQuaternion = quaternionManipulator.qFromAngleAxis(angle * frame, axis);

  free(intermediateMatrix);
  intermediateMatrix = matrixManipulator.GetIdentity();
  quaternionManipulator.qGLMatrix(intermediateQuaternion, intermediateMatrix);

  intermediateMatrix[3] = transformationMatrix[3] * frame;
  intermediateMatrix[7] = transformationMatrix[7] * frame;
  intermediateMatrix[11] = transformationMatrix[11] * frame;


}


void TangramPiece::rotate(float theta, Vector axis){
  Quaternion newRotation = quaternionManipulator.qFromAngleAxis(theta, axis);
  
  Rotation = quaternionManipulator.qMultiply(newRotation, Rotation);
  dirtyMatrix = true;
}


void TangramPiece::move(float movement[3]){
  Translation.x += movement[0];
  Translation.y += movement[1];
  Translation.z += movement[2];

  dirtyMatrix = true;
}


void TangramPiece::recalculateMatrix(){
  dirtyMatrix = false;
  GLfloat multMatrix[16];
  quaternionManipulator.qGLMatrix(Rotation, multMatrix);
  GLfloat * transMatrix = matrixManipulator.Multiply(matrixManipulator.GetTranslation(Translation.x, Translation.y, Translation.z), transformationMatrix); //Ugly, change this at once
  
  free(transformationMatrix);
  transformationMatrix = matrixManipulator.Multiply(transMatrix, multMatrix);
 
  free(transMatrix);

}

void TangramPiece::resetPiece(){
  Translation.x = 0.0f;
  Translation.y = 0.0f;
  Translation.z = 0.0f;
  Translation.w = 0.0f;

  Rotation.x = 0.0f;
  Rotation.y = 0.0f;
  Rotation.z = 0.0f;
  Rotation.t = 1.0f;

  
  free(transformationMatrix);
  transformationMatrix = matrixManipulator.GetIdentity();
  dirtyMatrix = false;
  beingAnimated = false;
  
}

TangramPiece::~TangramPiece()
{
}
