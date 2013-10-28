#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <math.h> 

typedef GLfloat Matrix[16];


class MatrixManip
{
public:
  MatrixManip();
  GLfloat* getIdentity();
  GLfloat* getTranslation(float x, float y, float z);
  GLfloat* getRotation(float a[3], float angle);
  GLfloat* getScale(float x, float y, float z);
  GLfloat* multiply(Matrix A, Matrix B);
  void MatrixManip::fillWithIdentity(GLfloat* piecesMatrices []);
  void MatrixManip::fillWithPresetPosition(GLfloat* piecesMatrices []);
};

