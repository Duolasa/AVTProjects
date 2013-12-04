#include "Quaternion.h"

// Constructors
engine::Quaternion::Quaternion(){
	t = 0.0f; x = 0.0f; y = 0.0f; z = 0.0f;
}

engine::Quaternion::Quaternion(float tt, float xx, float yy, float zz){
	t = tt; x = xx; y = yy; z = zz;
}

engine::Quaternion::Quaternion(float theta, engine::Vec4 axis){
	engine::Vec4 axisn = axis.Normalise();

	engine::Quaternion q;
	float a = theta * (float)DEGREES_TO_RADIANS;
	q.t = cos(a / 2.0f);
	float s = sin(a / 2.0f);
	q.x = axisn.x * s;
	q.y = axisn.y * s;
	q.z = axisn.z * s;

	q.Clean();
	q.Normalize();

	t = q.t;
	x = q.x;
	y = q.y;
	z = q.z;
}

//Functions
void engine::Quaternion::ToAngleAxis(float& theta, engine::Vec4& axis){
	engine::Quaternion q = engine::Quaternion::Quaternion(t, x, y, z);
	engine::Quaternion qn = q.Normalize();
	theta = 2.0f * acos(qn.t) * (float)RADIANS_TO_DEGREES;
	float s = sqrt(1.0f - qn.t*qn.t);
	if (s < qThreshold) {
		axis.x = 1.0f;
		axis.y = 0.0f;
		axis.z = 0.0f;
		axis.w = 1.0f;
	}
	else {
		axis.x = qn.x / s;
		axis.y = qn.y / s;
		axis.z = qn.z / s;
		axis.w = 1.0f;
	}
}

void engine::Quaternion::Clean(){
	if (fabs(t) < qThreshold) t = 0.0f;
	if (fabs(x) < qThreshold) x = 0.0f;
	if (fabs(y) < qThreshold) y = 0.0f;
	if (fabs(z) < qThreshold) z = 0.0f;
}

float engine::Quaternion::Quadrance(){
	return t*t + x*x + y*y + z*z;
}

float engine::Quaternion::Norm(){
	engine::Quaternion q = engine::Quaternion::Quaternion(t, x, y, z);
	return sqrt(q.Quadrance());
}

engine::Quaternion engine::Quaternion::Normalize(){
	engine::Quaternion q = engine::Quaternion::Quaternion(t, x, y, z);
	float s = 1 / q.Norm();
	return q * s;
}

engine::Quaternion engine::Quaternion::Conjugate(){
	engine::Quaternion qconj = engine::Quaternion::Quaternion(t, -x, -y, -z);
	return qconj;
}

engine::Quaternion engine::Quaternion::Inverse(){
	engine::Quaternion q = engine::Quaternion::Quaternion(t, x, y, z);
	return q.Conjugate() * (1.0f / q.Quadrance());
}

engine::Quaternion	&engine::Quaternion::operator=(const engine::Quaternion &q){
	x = q.x; y = q.y; z = q.z; t = q.t;
	return (SELF);
}

engine::Quaternion engine::Quaternion::operator+(const engine::Quaternion &q) const {
	engine::Quaternion q0 = engine::Quaternion::Quaternion(t, x, y, z);
	engine::Quaternion qf;
	qf.t = q0.t + q.t;
	qf.x = q0.x + q.x;
	qf.y = q0.y + q.y;
	qf.z = q0.z + q.z;
	return q;
}

engine::Quaternion engine::Quaternion::operator-(const engine::Quaternion &q) const {
	engine::Quaternion q0 = engine::Quaternion::Quaternion(t, x, y, z);
	engine::Quaternion qf;
	qf.t = q0.t - q.t;
	qf.x = q0.x - q.x;
	qf.y = q0.y - q.y;
	qf.z = q0.z - q.z;
	return q;
}

engine::Quaternion engine::Quaternion::operator*(const engine::Quaternion &q) const {
	engine::Quaternion q0 = engine::Quaternion::Quaternion(t, x, y, z);
	engine::Quaternion qf;
	qf.t = q0.t * q.t - q0.x * q.x - q0.y * q.y - q0.z * q.z;
	qf.x = q0.t * q.x + q0.x * q.t + q0.y * q.z - q0.z * q.y;
	qf.y = q0.t * q.y + q0.y * q.t + q0.z * q.x - q0.x * q.z;
	qf.z = q0.t * q.z + q0.z * q.t + q0.x * q.y - q0.y * q.x;
	return qf;
}

engine::Quaternion engine::Quaternion::operator*(float s) const {
	Quaternion sq;
	sq.t = s * t;
	sq.x = s * x;
	sq.y = s * y;
	sq.z = s * z;
	return sq;
}

engine::Mat4 engine::Quaternion::getMatrix(){
	engine::Quaternion q = engine::Quaternion::Quaternion(t, x, y, z);
	engine::Quaternion qn = q.Normalize();

	Mat4 mat = Mat4();

	float xx = qn.x * qn.x;
	float xy = qn.x * qn.y;
	float xz = qn.x * qn.z;
	float xt = qn.x * qn.t;
	float yy = qn.y * qn.y;
	float yz = qn.y * qn.z;
	float yt = qn.y * qn.t;
	float zz = qn.z * qn.z;
	float zt = qn.z * qn.t;

	mat.matrix[0] = 1.0f - 2.0f * (yy + zz);
	mat.matrix[1] = 2.0f * (xy + zt);
	mat.matrix[2] = 2.0f * (xz - yt);
	mat.matrix[3] = 0.0f;

	mat.matrix[4] = 2.0f * (xy - zt);
	mat.matrix[5] = 1.0f - 2.0f * (xx + zz);
	mat.matrix[6] = 2.0f * (yz + xt);
	mat.matrix[7] = 0.0f;

	mat.matrix[8] = 2.0f * (xz + yt);
	mat.matrix[9] = 2.0f * (yz - xt);
	mat.matrix[10] = 1.0f - 2.0f * (xx + yy);
	mat.matrix[11] = 0.0f;

	mat.matrix[12] = 0.0f;
	mat.matrix[13] = 0.0f;
	mat.matrix[14] = 0.0f;
	mat.matrix[15] = 1.0f;

	mat.Clean();

	return mat;
}

// --- Quaternion operators ----------------------------------------------------------

engine::Quaternion engine::Slerp(const engine::Quaternion& q0, const engine::Quaternion& q1, float k){
	float angle = acos(q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t);
	float k0 = sin((1 - k)*angle) / sin(angle);
	float k1 = sin(k*angle) / sin(angle);
	return (q0 *k0) + (q1 * k1);
}

engine::Quaternion engine::Lerp(const engine::Quaternion& q0, const engine::Quaternion& q1, float k){
	float cos_angle = q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.t*q1.t;
	float k0 = 1.0f - k;
	float k1 = (cos_angle > 0) ? k : -k;
	return (q0 * k0) + (q1 * k1);
}

const void vPrint(const std::string s, const engine::Vec4& v)
{
	std::cerr << s << " = (" << v.x << ", " << v.y << ", " << v.z << ", " << v.w << ")" << std::endl;
}

void engine::PrintAngleAxis(const std::string& s, engine::Quaternion& q){
	std::cerr << s << " = ";

	float thetaf;
	engine::Vec4 axis_f;
	q.ToAngleAxis(thetaf, axis_f);
	std::cerr << "angle = " << thetaf << " ";
	vPrint("axis", axis_f);
}

engine::Mat4 engine::GetRotation(engine::Quaternion& q){
	return q.getMatrix();
}

std::ostream &operator<<(std::ostream &s, const engine::Quaternion &q){
	s << " = (" << q.t << ", " << q.x << ", " << q.y << ", " << q.z << ")" << std::endl;
	return s;
}