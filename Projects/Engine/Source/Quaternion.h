#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vector.h"
#include "Matrix.h"
#include <iostream>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

#define X_AXIS Vec4(1, 0, 0, 1);
#define Y_AXIS Vec4(0, 1, 0, 1);
#define Z_AXIS Vec4(0, 0, 1, 1);

namespace engine {

	const float qThreshold = (float)1.0e-5;

	struct Quaternion{
		float t, x, y, z;

		// Constructors
					Quaternion();
					Quaternion(float tt, float xx, float yy, float zz);
					Quaternion(float theta, Vec4 axis);

		//Functions
		void		ToAngleAxis(float& theta, Vec4& axis);
		void		Clean();
		float		Quadrance();
		float		Norm();
		Quaternion	Normalize();
		Quaternion  Conjugate();
		Quaternion	Inverse();

		Quaternion	&operator=(const Quaternion &q);
		Quaternion  operator+(const Quaternion &q) const;
		Quaternion  operator-(const Quaternion &q) const;
		Quaternion  operator*(const Quaternion &q) const;
		Quaternion  operator*(float s) const;	

		Mat4		getMatrix();
	};

	// --- Quaternion operators ----------------------------------------------------------
	Quaternion		Slerp(const Quaternion& q0, const Quaternion& q1, float k);
	Quaternion		Lerp(const Quaternion& q0, const Quaternion& q1, float k);
	void			PrintAngleAxis(const std::string& s, Quaternion& q);

	Mat4 GetRotation(Quaternion& q);

	std::ostream &operator<<(std::ostream &s, const Quaternion &q);


}

#endif //QUATERNION_H