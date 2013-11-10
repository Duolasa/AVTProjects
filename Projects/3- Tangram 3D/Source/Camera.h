#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <iostream>

typedef GLfloat Matrix[16];

class Camera
{
public:
  GLuint SharedMatricesBuffer;
  GLint SharedMatricesId;
  GLfloat* viewMatrix, * orthographicMatrix, * perspectiveMatrix;
  float eye[3], center[3], up[3];

  static const GLuint UBO_BP = 0;
  float top, bottom, left, right, nearO, farO, nearP, farP, fovy, aspect, radius, theta, phi;

  Camera(GLfloat* vm, GLfloat* om, GLfloat* pm);
  void CreateBuffers();
  void Camera::ChangeViewMatrix();
  void Camera::PerspProjection();
  void Camera::OrthoProjection();
  ~Camera();
};

