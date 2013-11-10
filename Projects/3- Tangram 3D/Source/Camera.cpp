#include "Camera.h"
/*
const Matrix I = {
  1.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, 0.0f,
  0.0f, 0.0f, 0.0f, 1.0f
};

const Matrix ModelMatrix = {
  1.0f, 0.0f, 0.0f, 0.0f,
  0.0f, 1.0f, 0.0f, 0.0f,
  0.0f, 0.0f, 1.0f, 0.0f,
  -0.5f, -0.5f, -0.5f, 1.0f
}; // Column Major

// Eye(5,5,5) Center(0,0,0) Up(0,1,0)
const Matrix ViewMatrix1 = {
  0.70f, -0.41f, 0.58f, 0.00f,
  0.00f, 0.82f, 0.58f, 0.00f,
  -0.70f, -0.41f, 0.58f, 0.00f,
  0.00f, 0.00f, -8.70f, 1.00f
}; // Column Major

// Eye(-5,-5,-5) Center(0,0,0) Up(0,1,0)
const Matrix ViewMatrix2 = {
  -0.70f, -0.41f, -0.58f, 0.00f,
  0.00f, 0.82f, -0.58f, 0.00f,
  0.70f, -0.41f, -0.58f, 0.00f,
  0.00f, 0.00f, -8.70f, 1.00f
}; // Column Major

// Orthographic LeftRight(-2,2) TopBottom(-2,2) NearFar(1,10)
const Matrix ProjectionMatrix1 = {
  0.50f, 0.00f, 0.00f, 0.00f,
  0.00f, 0.50f, 0.00f, 0.00f,
  0.00f, 0.00f, -0.22f, 0.00f,
  0.00f, 0.00f, -1.22f, 1.00f
}; // Column Major

// Perspective Fovy(30) Aspect(640/480) NearZ(1) FarZ(10)
const Matrix ProjectionMatrix2 = {
  2.79f, 0.00f, 0.00f, 0.00f,
  0.00f, 3.73f, 0.00f, 0.00f,
  0.00f, 0.00f, -1.22f, -1.00f,
  0.00f, 0.00f, -2.22f, 0.00f
}; // Column Major

*/
#define radiansToDegrees 57.2957795131f
#define degreesToRadians 0.01745329251f

Camera::Camera(GLfloat* vm, GLfloat* om, GLfloat* pm){
    top = 2;
    bottom = -2;
    left = -2;
    right = 2;
    nearO = 1;
    farO = 10;
    nearP = 1;
    farP = 10;
    fovy = 30;
    aspect = 640.0f / 480.0f;

    viewMatrix = vm;
    orthographicMatrix = om;
    perspectiveMatrix = pm;

    radius = sqrtf(5 * 5 * 3);
    theta = acosf(5 / radius);
    phi = atanf(5 / 5) ;

 
    eye[0] = 5;
    eye[1] = 5;
    eye[2] = 5;

    center[0] = 0;
    center[1] = 0;
    center[2] = 0;

    up[0] = 0;
    up[1] = 0;
    up[2] = 1;

  }

  void Camera::CreateBuffers(){
    glGenBuffers(1, &SharedMatricesBuffer);

    glBindBuffer(GL_UNIFORM_BUFFER, SharedMatricesBuffer);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(Matrix) * 2, 0, GL_STREAM_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, SharedMatricesBuffer);

    glBindBuffer(GL_UNIFORM_BUFFER, SharedMatricesBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix), viewMatrix);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix), sizeof(Matrix), orthographicMatrix);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
  }

  void Camera::ChangeViewMatrix(){

    glBindBuffer(GL_UNIFORM_BUFFER, SharedMatricesBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Matrix), viewMatrix);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

  }

  void Camera::PerspProjection(){

    glBindBuffer(GL_UNIFORM_BUFFER, SharedMatricesBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix), sizeof(Matrix), perspectiveMatrix);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

  }

  void Camera::OrthoProjection(){

    glBindBuffer(GL_UNIFORM_BUFFER, SharedMatricesBuffer);
    glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Matrix), sizeof(Matrix), orthographicMatrix);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);

  }

  Camera::~Camera()
  {

  }
