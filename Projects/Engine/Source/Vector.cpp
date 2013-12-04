#include "Vector.h"

// Vec3 #######################################################################

// --- Inlines ----------------------------------------------------------------

// Constructors
engine::Vec3::Vec3(){
	x = 0; y = 0; z = 0;
}

engine::Vec3::Vec3(float a){
	x = a; y = a; z = a;
}

engine::Vec3::Vec3(float a, float b, float c){
	x = a; y = b; z = c;
}

engine::Vec3::Vec3(const engine::Vec3 &v){
	x = v.x; y = v.y; z = v.z; 
}


// Assignment operators
engine::Vec3 &engine::Vec3::operator=(const engine::Vec3 &a){
	x = a.x; y = a.y; z = a.z;
	return (SELF);
}

engine::Vec3 &engine::Vec3::operator+=(const engine::Vec3 &a){
	x += a.x; y += a.y; z += a.z;
	return (SELF);
}

engine::Vec3 &engine::Vec3::operator-=(const engine::Vec3 &a){
	x -= a.x; y -= a.y; z -= a.z;
	return (SELF);
}

engine::Vec3 &engine::Vec3::operator*=(const engine::Vec3 &a){
	x *= a.x; y *= a.y; z *= a.z;
	return (SELF);
}

engine::Vec3 &engine::Vec3::operator*=(float s){
	x *= s; y *= s; z *= s;
	return (SELF);
}

engine::Vec3 &engine::Vec3::operator/=(const engine::Vec3 &a){
	x /= a.x; y /= a.y; z /= a.z;
	return (SELF);
}

engine::Vec3 &engine::Vec3::operator/=(float s){
	x /= s; y /= s; z /= s;
	return (SELF);
}

// Comparison operators
bool engine::Vec3::operator==(const engine::Vec3 &a) const{  // v == a?
	return (x == a.x && y == a.y && z == a.z);
}

bool engine::Vec3::operator!=(const engine::Vec3 &a) const{  // v != a?
	return (x != a.x || y != a.y || z != a.z);
}

bool engine::Vec3::operator<(const engine::Vec3 &a) const{ // v <  a?
	return (x < a.x && y < a.y && z < a.z);
}

bool engine::Vec3::operator>=(const engine::Vec3 &a) const{ // v >= a?
	return (x >= a.x && y >= a.y && z >= a.z);
}

// Arithmetic operators

engine::Vec3 engine::Vec3::operator+(const engine::Vec3 &a) const{   // v + a
	engine::Vec3 v;
	v.x = x + a.x;
	v.y = y + a.y;
	v.z = z + a.z;
	return v;
}

engine::Vec3 engine::Vec3::operator-(const Vec3 &a) const{			// v - a
	engine::Vec3 v;
	v.x = x - a.x;
	v.y = y - a.y;
	v.z = z - a.z;
	return v;
}

engine::Vec3 engine::Vec3::operator-() const{						// -v
	engine::Vec3 v;
	v.x = -x;
	v.y = -y;
	v.z = -z;
	return v;
}

engine::Vec3 engine::Vec3::operator*(const Vec3 &a) const{		   // v * a (vx * ax, ...)
	engine::Vec3 v;
	v.x = x * a.x;
	v.y = y * a.y;
	v.z = z * a.z;
	return v;
}

engine::Vec3 engine::Vec3::operator*(float s) const{		          // v * s
	engine::Vec3 v;
	v.x = x * s;
	v.y = y * s;
	v.z = z * s;
	return v;
}

engine::Vec3 engine::Vec3::operator/(const Vec3 &a) const{		  // v / a (vx / ax, ...)
	engine::Vec3 v;
	v.x = x / a.x;
	v.y = y / a.y;
	v.z = z / a.z;
	return v;
}

engine::Vec3 engine::Vec3::operator/(float s) const{		          // v / s
	engine::Vec3 v;
	v.x = x / s;
	v.y = y / s;
	v.z = z / s;
	return v;
}

// --- Vec3 operators ----------------------------------------------------------

engine::Vec3 engine::operator*(float s, const engine::Vec3 &v){	  // s * v
	return (v * s);
}

float engine::dot(const engine::Vec3 &a, const engine::Vec3 &b){   // v . a
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float engine::len(const Vec3 &v){				                  // || v ||
	return (sqrt(dot(v,v)));
}

float engine::sqrlen(const Vec3 &v){					              // v . v
	return (dot(v,v));
}

engine::Vec3 engine::norm(const Vec3 &v){		                  // v / || v ||
	assert(sqrlen(v) > 0.0);
    return(v / len(v));
}

void engine::normalise(Vec3 &v){					                  // v = norm(v)
	v /= len(v);
}

engine::Vec3 engine::cross(const engine::Vec3 &a, const engine::Vec3 &b){ // a x b
	Vec3 v;
    v.x = a.y * b.z - a.z * b.y;
    v.y = a.z * b.x - a.x * b.z;
    v.z = a.x * b.y - a.y * b.x;
    return v;
}

std::ostream &engine::operator<<(std::ostream &s, const engine::Vec3 &v){
	s << "[ " << v.x << " " << v.y << " " << v.z << "]";
	return s;
}

// Initialisers
engine::Vec3 &engine::Vec3::Normalise(){						                        // normalise vector
	assert(sqrlen(SELF) > 0.0);
    SELF /= len(SELF);
    return(SELF);
}


// Vec4 #######################################################################

// --- Inlines ----------------------------------------------------------------

// Constructors
engine::Vec4::Vec4(){
	x = 0; y = 0; z = 0; w = 4;
}

engine::Vec4::Vec4(float a){
	x = a; y = a; z = a; w = 4;
}

engine::Vec4::Vec4(float a, float b, float c, float d){
	x = a; y = b; z = c; w = d;
}

engine::Vec4::Vec4(const engine::Vec4 &v){
	x = v.x; y = v.y; z = v.z; w = v.w;
}

engine::Vec4::Vec4(const engine::Vec3 &v, float w){
	x = v.x; y = v.y; z = v.z; w = w;
}


// Assignment operators
engine::Vec4 &engine::Vec4::operator=(const engine::Vec4 &a){
	x = a.x; y = a.y; z = a.z; w = a.w;
	return (SELF);
}

engine::Vec4 &engine::Vec4::operator+=(const engine::Vec4 &a){
	x += a.x; y += a.y; z += a.z; w += a.w;
	return (SELF);
}

engine::Vec4 &engine::Vec4::operator-=(const engine::Vec4 &a){
	x -= a.x; y -= a.y; z -= a.z; w -= a.w;
	return (SELF);
}

engine::Vec4 &engine::Vec4::operator*=(const engine::Vec4 &a){
	x *= a.x; y *= a.y; z *= a.z; w *= a.w;
	return (SELF);
}

engine::Vec4 &engine::Vec4::operator*=(float s){
	x *= s; y *= s; z *= s; w *= s;
	return (SELF);
}

engine::Vec4 &engine::Vec4::operator/=(const engine::Vec4 &a){
	x /= a.x; y /= a.y; z /= a.z; w /= a.w;
	return (SELF);
}

engine::Vec4 &engine::Vec4::operator/=(float s){
	x /= s; y /= s; z /= s; w /= s;
	return (SELF);
}

// Comparison operators
bool engine::Vec4::operator==(const engine::Vec4 &a) const{  // v == a?
	return (x == a.x && y == a.y && z == a.z && w == a.w);
}

bool engine::Vec4::operator!=(const engine::Vec4 &a) const{  // v != a?
	return (x != a.x || y != a.y || z != a.z || w != a.w);
}

bool engine::Vec4::operator<(const engine::Vec4 &a) const{ // v <  a?
	return (x < a.x && y < a.y && z < a.z && w < a.w);
}

bool engine::Vec4::operator>=(const engine::Vec4 &a) const{ // v >= a?
	return (x >= a.x && y >= a.y && z >= a.z && w >= a.w);
}

// Arithmetic operators

engine::Vec4 engine::Vec4::operator+(const engine::Vec4 &a) const{   // v + a
	engine::Vec4 v;
	v.x = x + a.x;
	v.y = y + a.y;
	v.z = z + a.z;
	v.w = w + a.w;
	return v;
}

engine::Vec4 engine::Vec4::operator-(const Vec4 &a) const{			// v - a
	engine::Vec4 v;
	v.x = x - a.x;
	v.y = y - a.y;
	v.z = z - a.z;
	v.w = w - a.w;
	return v;
}

engine::Vec4 engine::Vec4::operator-() const{						// -v
	engine::Vec4 v;
	v.x = -x;
	v.y = -y;
	v.z = -z;
	v.w = -w;
	return v;
}

engine::Vec4 engine::Vec4::operator*(const Vec4 &a) const{		   // v * a (vx * ax, ...)
	engine::Vec4 v;
	v.x = x * a.x;
	v.y = y * a.y;
	v.z = z * a.z;
	v.w = w * a.w;
	return v;
}

engine::Vec4 engine::Vec4::operator*(float s) const{		          // v * s
	engine::Vec4 v;
	v.x = x * s;
	v.y = y * s;
	v.z = z * s;
	v.w = w * s;
	return v;
}

engine::Vec4 engine::Vec4::operator/(const Vec4 &a) const{		  // v / a (vx / ax, ...)
	engine::Vec4 v;
	v.x = x / a.x;
	v.y = y / a.y;
	v.z = z / a.z;
	v.w = w / a.w;
	return v;
}

engine::Vec4 engine::Vec4::operator/(float s) const{		          // v / s
	engine::Vec4 v;
	v.x = x / s;
	v.y = y / s;
	v.z = z / s;
	v.w = w / s;
	return v;
}

// --- Vec4 operators ----------------------------------------------------------

engine::Vec4 engine::operator*(float s, const engine::Vec4 &v){	  // s * v
	return (v * s);
}

float engine::dot(const engine::Vec4 &a, const engine::Vec4 &b){   // v . a
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

float engine::len(const Vec4 &v){				                  // || v ||
	return (sqrt(dot(v,v)));
}

float engine::sqrlen(const Vec4 &v){					              // v . v
	return (dot(v,v));
}

engine::Vec4 engine::norm(const Vec4 &v){							  // v / || v ||
	assert(sqrlen(v) > 0.0);
    return(v / len(v));
}

void engine::normalise(Vec4 &v){									   // v = norm(v)
	assert(sqrt(v.x*v.x + v.y*v.y + v.z*v.z) > 0.0);
	float s = 1 / sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
	v.x = v.x * s;
	v.y = v.y * s;
	v.z = v.z * s;
	v.w = v.w * s;
}

std::ostream &engine::operator<<(std::ostream &s, const engine::Vec4 &v){
	s << "[ " << v.x << " " << v.y << " " << v.z <<  " " << v.w << "]";
	return s;
}

// Initialisers
engine::Vec4 &engine::Vec4::Normalise(){						                        // normalise vector
	assert(sqrt(x*x + y*y + z*z) > 0.0);
	float s = 1 / sqrt(x*x + y*y + z*z);
	x = x * s;
	y = y * s;
	z = z * s;
	w = w * s;
    return(SELF);
}