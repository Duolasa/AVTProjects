#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "MatrixManip.h"
#include <iostream>
#include <vector>
#include "QuaternionManipulator.h"
#include "MatrixManip.h"

#define VERTICES 0
#define COLORS 1


class TangramPiece
{
public:
  typedef struct {
    GLfloat XYZW[4];
    GLfloat RGBA[4];
  } Vertex;


public:
  QuaternionManipulator quaternionManipulator;
  MatrixManip matrixManipulator;
  GLuint VaoId, VboId[2];
  std::vector<Vertex>vertices;
  std::vector<GLubyte> indices;
  bool dirtyMatrix, beingAnimated;
  GLfloat* transformationMatrix;
  GLfloat* intermediateMatrix;
  Quaternion Rotation;
  Vector Translation;

public:
  TangramPiece();
  ~TangramPiece();
  void fillUniform(GLint UniformId);
  void draw(GLint UniformId);
  void createBuffers();
  void rotate(float theta, Vector axis);
  void move(float movement[3]);
  void recalculateMatrix();
  void changeIntermediateMatrix(float frame);
  void resetPiece();
};

