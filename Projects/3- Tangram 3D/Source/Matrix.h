#include "GL/glew.h"
#include "GL/freeglut.h"
#include <math.h>
#include "Vector.h"



struct Matrix{
	GLfloat matrix[16];

	Matrix(GLfloat m[16]);

	Matrix GetIdentity();
	Matrix GetTranslation(float x, float y, float z);
	Matrix GetTranslation(Vector::vec3 v);
	Matrix GetRotation(float x, float y, float z, float angle);
	Matrix GetRotation(Vector::vec3 v, float angle);
	Matrix GetScale(float x, float y, float z);
	Matrix GetScale(Vector::vec3 v);
	Matrix GetView(Vector::vec3 eye, Vector::vec3 center, Vector::vec3 up);
	Matrix GetOrthoProjection(float top, float bottom, float left, float right, float nearZ, float farZ);
	Matrix GetPerspProjection(float fovy, float aspect, float nearZ, float farZ);

	void Transpose();
	Matrix Matrix::operator* (Matrix m);
	Matrix Matrix::operator= (Matrix m);


};