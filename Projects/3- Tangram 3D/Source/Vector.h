#ifndef VECTOR_H
#define VECTOR_H

#include <sstream>
#include <cassert>

#define SELF (*this)

namespace engine {

	// --- Vec3 -------------------------------------------------------------
  struct Vec3{
    float x, y, z;

    // Constructors
    Vec3();
    Vec3(float a);
    Vec3(float a, float b, float c);
    Vec3(const Vec3 &v);

    // Assignment operators
    Vec3		&operator=(const Vec3 &a);
    Vec3        &operator+=(const Vec3 &a);
    Vec3        &operator-=(const Vec3 &a);
    Vec3        &operator*=(const Vec3 &a);
    Vec3        &operator*=(float s);
    Vec3        &operator/=(const Vec3 &a);
    Vec3        &operator/=(float s);

    // Comparison operators
    bool        operator==(const Vec3 &a) const;	// v == a?
    bool        operator!=(const Vec3 &a) const;	// v != a?
    bool        operator < (const Vec3 &a) const;		// v <  a?
    bool        operator>=(const Vec3 &a) const;	// v >= a?

    // Arithmetic operators

    Vec3        operator+(const Vec3 &a) const;		// v + a
    Vec3        operator-(const Vec3 &a) const;		// v - a
    Vec3        operator-() const;					// -v
    Vec3        operator*(const Vec3 &a) const;		// v * a (vx * ax, ...)
    Vec3        operator*(float s) const;			// v * s
    Vec3        operator/(const Vec3 &a) const;		// v / a (vx / ax, ...)
    Vec3        operator/(float s) const;			// v / s

    // Initialisers
    Vec3        &Normalise();                       // normalise vector
  };

	// --- Vec3 operators ----------------------------------------------------------

	Vec3     operator*(float s, const Vec3 &v);	// s * v
	float    dot(const Vec3 &a, const Vec3 &b);  // v . a
	float    len(const Vec3 &v);                 // || v ||
	float    sqrlen(const Vec3 &v);              // v . v
	Vec3     norm(const Vec3 &v);                // v / || v ||
	void     normalise(Vec3 &v);                 // v = norm(v)
	Vec3     cross(const Vec3 &a, const Vec3 &b);// a x b

	std::ostream &operator<<(std::ostream &s, const Vec3 &v);

	// --- Vec4 -------------------------------------------------------------
	struct Vec4{
		float x, y, z, w;

		// Constructors
					Vec4();
					Vec4(float a);
					Vec4(float a, float b, float c, float d);
					Vec4(const Vec3 &v, float w);
					Vec4(const Vec4 &v);

		// Assignment operators
		Vec4        &operator=(const Vec4 &a);
		Vec4        &operator+=(const Vec4 &a);
		Vec4        &operator-=(const Vec4 &a);
		Vec4        &operator*=(const Vec4 &a);
		Vec4        &operator*=(float s);
		Vec4        &operator/=(const Vec4 &a);
		Vec4        &operator/=(float s);

		// Comparison operators
		bool        operator==(const Vec4 &a) const;	// v == a?
		bool        operator!=(const Vec4 &a) const;	// v != a?
		bool        operator<(const Vec4 &a) const;		// v <  a?
		bool        operator>=(const Vec4 &a) const;	// v >= a?

		// Arithmetic operators

		Vec4        operator+(const Vec4 &a) const;		// v + a
		Vec4        operator-(const Vec4 &a) const;		// v - a
		Vec4        operator-() const;					// -v
		Vec4        operator*(const Vec4 &a) const;		// v * a (vx * ax, ...)
		Vec4        operator*(float s) const;			// v * s
		Vec4        operator/(const Vec4 &a) const;		// v / a (vx / ax, ...)
		Vec4        operator/(float s) const;			// v / s

		// Initialisers
		Vec4        &Normalise();                       // normalise vector
	};

	// --- Vec4 operators ----------------------------------------------------------

	Vec4     operator*(float s, const Vec4 &v);	// s * v
	float    dot(const Vec4 &a, const Vec4 &b);  // v . a
	float    len(const Vec4 &v);                 // || v ||
	float    sqrlen(const Vec4 &v);              // v . v
	Vec4     norm(const Vec4 &v);                // v / || v ||
	void     normalise(Vec4 &v);                 // v = norm(v)

	std::ostream &operator<<(std::ostream &s, const Vec4 &v);
}

#endif