#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <math.h>
#include "QuaternionManipulator.h"

typedef GLfloat Matrix[16];

class MatrixManip
{
public:
  QuaternionManipulator quaternionManipulator;


  MatrixManip();
  GLfloat* GetIdentity();
  GLfloat* GetTranslation(float x, float y, float z);
  GLfloat* GetRotation(float a[3], float angle);
  GLfloat* GetScale(float x, float y, float z);
  GLfloat* Multiply(Matrix A, Matrix B);
  float CalculateNorm(float v[3]);
  float* CrossProduct(float a[3], float b[3]);
  float DotProduct(float a[3], float b[3]);
  GLfloat* GetView(float eye[3], float center[3], float up[3]);
  GLfloat* GetOrthoProjection(float top, float bottom, float left, float right, float nearZ, float farZ);
  GLfloat* GetPerspProjection(float fovy, float aspect, float nearZ, float farZ);
};

