
#ifndef MATRIX_H
#define MATRIX_H

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "Vector.h"


namespace engine{

	const float mThreshold = (float)1.0e-5;

	struct Mat4{
		GLfloat matrix[16];

		Mat4(GLfloat m[16]);
		Mat4();

		void Transpose();

		Mat4 Mat4::operator* (Mat4 other);
		void Mat4::operator= (Mat4 other);
		bool Mat4::operator== (Mat4 other);
		bool Mat4::operator!= (Mat4 other);

		engine::Vec4 Mat4::operator* (engine::Vec4 v);

		void Clean();
	};

	std::ostream& operator<<(std::ostream& os, const Mat4& m);

	Mat4 GetIdentity();
	Mat4 GetTranslation(float x, float y, float z);
	Mat4 GetTranslation(engine::Vec3 v);
	Mat4 GetScale(float x, float y, float z);
	Mat4 GetScale(float a);
	Mat4 GetScale(engine::Vec3 v);
	Mat4 GetView(engine::Vec3 eye, engine::Vec3 center, engine::Vec3 up);
	Mat4 GetOrthoProjection(float top, float bottom, float left, float right, float nearZ, float farZ);
	Mat4 GetPerspProjection(float fovy, float aspect, float nearZ, float farZ);

	

}

#endif // MATRIX_H