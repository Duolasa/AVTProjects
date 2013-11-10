#include <iostream>
#include <string>
#include <cassert>

#define DEGREES_TO_RADIANS 0.01745329251994329547
#define RADIANS_TO_DEGREES 57.29577951308232185913

typedef struct {
  float x, y, z, w;
} Vector;

typedef float Matrix[16];
const float mThreshold = (float) 1.0e-5;


typedef struct {
  float t, x, y, z;
} Quaternion;

const float qThreshold = (float) 1.0e-5;
const Quaternion qFromAngleAxis(float theta, Vector axis);
const void qToAngleAxix(const Quaternion& q, float& theta, Vector& axis);
const void qClean(Quaternion& q);
const float qQuadrance(const Quaternion& q);
const float qNorm(const Quaternion& q);
const Quaternion qNormalize(const Quaternion& q);
const Quaternion qConjugate(const Quaternion& q);
const Quaternion qInverse(const Quaternion& q);
const Quaternion qMultiply(const Quaternion& q, const float s);
const Quaternion qMultiply(const Quaternion& q0, const Quaternion& q1);
const void qMatrix(const Quaternion& q, float matrix[16]);
const Quaternion qSlerp(const Quaternion& q0, const Quaternion& q1, float k);
const bool qEqual(const Quaternion& q0, const Quaternion& q1);
const void qPrint(const std::string& s, const Quaternion& q);
const void qPrintAngleAxis(const std::string& s, const Quaternion& q);


/////////////////////////////////////////////////////////////////////// VECTOR
class QuaternionManipulator
{
public:
  const Vector vNormalize(const Vector& v);
  const void vPrint(const std::string s, const Vector& v);
  const bool vEqual(const Vector& v0, const Vector& v1);
  const Vector mMultiply(Matrix m, Vector& v);
  const void mClean(Matrix m);
  const Quaternion qFromAngleAxis(float theta, Vector axis);
  const void qToAngleAxis(const Quaternion& q, float& theta, Vector& axis);
  const void qClean(Quaternion& q);
  const float qQuadrance(const Quaternion& q);
  const float qNorm(const Quaternion& q);
  const Quaternion qNormalize(const Quaternion& q);
  const Quaternion qConjugate(const Quaternion& q);
  const Quaternion qInverse(const Quaternion& q);
  const Quaternion qAdd(const Quaternion& q0, const Quaternion& q1);
  const Quaternion qMultiply(const Quaternion& q, const float s);
  const Quaternion qMultiply(const Quaternion& q0, const Quaternion& q1);
  const void qGLMatrix(const Quaternion& q, float matrix[16]);
  const Quaternion qLerp(const Quaternion& q0, const Quaternion& q1, float k);
  const Quaternion qSlerp(const Quaternion& q0, const Quaternion& q1, float k);
  const bool qEqual(const Quaternion& q0, const Quaternion& q1);
  const void qPrint(const std::string& s, const Quaternion& q);
  const void qPrintAngleAxis(const std::string& s, const Quaternion& q);
  void qtest1();
  void qtest2();
  void qtest3();
  void qtest4();
  void qtest5();
  void qtest6();

};
