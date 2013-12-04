#include "Matrix.h"
#include <iostream>


engine::Mat4::Mat4(GLfloat m[16]){

	for (int i = 0; i < 16; i++){
		matrix[i] = m[i];
	}

}


engine::Mat4::Mat4(){
	for (int i = 0; i < 16; i++){
		matrix[i] = 0;
	}
}


void engine::Mat4::Transpose(){
	GLfloat transpose[16];

	transpose[0] = matrix[0];
	transpose[1] = matrix[4];
	transpose[2] = matrix[8];
	transpose[3] = matrix[12];
	transpose[4] = matrix[1];
	transpose[5] = matrix[5];
	transpose[6] = matrix[9];
	transpose[7] = matrix[13];
	transpose[8] = matrix[2];
	transpose[9] = matrix[6];
	transpose[10] = matrix[10];
	transpose[11] = matrix[14];
	transpose[12] = matrix[3];
	transpose[13] = matrix[7];
	transpose[14] = matrix[11];
	transpose[15] = matrix[15];

	for (int i = 0; i< 16; i++)
		matrix[i] = transpose[i];
}


engine::Mat4 engine::Mat4::operator* (Mat4 other){

	Mat4 m;

	for (int i = 0; i < 4; i++){
		//first row
		for (int j = 0; j < 4; j++){
			m.matrix[i] += matrix[j] * other.matrix[(j * 4) + i];
		}
	}

	for (int i = 0; i < 4; i++){
		//second row
		for (int j = 0; j < 4; j++){
			m.matrix[4 + i] += matrix[4 + j] * other.matrix[(j * 4) + i];
		}
	}

	for (int i = 0; i < 4; i++){
		//third row
		for (int j = 0; j < 4; j++){
			m.matrix[8 + i] += matrix[8 + j] * other.matrix[(j * 4) + i];
		}
	}

	for (int i = 0; i < 4; i++){
		//forth row
		for (int j = 0; j < 4; j++){
			m.matrix[12 + i] += matrix[12 + j] * other.matrix[(j * 4) + i];
		}
	}

	return m;

}


void engine::Mat4::operator= (Mat4 other){
	for (int i = 0; i < 16; i++){
		matrix[i] = other.matrix[i];
	}

}

bool engine::Mat4::operator== (Mat4 other){
	for (int i = 0; i < 16; i++){
		if (matrix[i] != other.matrix[i])
			return false;
	}

	return true;

}
bool engine::Mat4::operator!= (Mat4 other){
	return !(*this == other);
}



engine::Vec4 engine::Mat4::operator* (engine::Vec4 v){
	engine::Vec4 result(0.0f, 0.0f, 0.0f, 0.0f);


	result.x += matrix[0] * v.x;
	result.x += matrix[1] * v.y;
	result.x += matrix[2] * v.z;
	result.x += matrix[3] * v.w;

	result.y += matrix[4] * v.x;
	result.y += matrix[5] * v.y;
	result.y += matrix[6] * v.z;
	result.y += matrix[7] * v.w;

	result.z += matrix[8] * v.x;
	result.z += matrix[9] * v.y;
	result.z += matrix[10] * v.z;
	result.z += matrix[11] * v.w;

	result.w += matrix[12] * v.x;
	result.w += matrix[13] * v.y;
	result.w += matrix[14] * v.z;
	result.w += matrix[15] * v.w;


	return result;
}


void engine::Mat4::Clean(){
	for (int i = 0; i < 16; i++){
		if (fabs(matrix[i]) < engine::mThreshold) matrix[i] = 0.0f;
	}
}


engine::Mat4 engine::GetIdentity(){
	GLfloat values[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};// Row Major

	engine::Mat4 m(values);
	m.Transpose();

	return m;
}


engine::Mat4 engine::GetTranslation(float x, float y, float z){
	GLfloat values[16] = {
		1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1.0f
	};// Row Major

	engine::Mat4 m(values);
	m.Transpose();

	return m;
}


engine::Mat4 engine::GetTranslation(engine::Vec3 v){
	return GetTranslation(v.x, v.y, v.z);

}


engine::Mat4 engine::GetScale(float x, float y, float z) {
	GLfloat values[16] = {
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};// Row Major

	engine::Mat4 m(values);
	m.Transpose();

	return m;
}

engine::Mat4 engine::GetScale(float a) {
	GLfloat values[16] = {
		a, 0.0f, 0.0f, 0.0f,
		0.0f, a, 0.0f, 0.0f,
		0.0f, 0.0f, a, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};// Row Major

	engine::Mat4 m(values);
	m.Transpose();

	return m;
}


engine::Mat4 engine::GetScale(engine::Vec3 v){
	return GetScale(v.x, v.y, v.z);
}


engine::Mat4 engine::GetView(engine::Vec3 eye, engine::Vec3 center, engine::Vec3 up){
	engine::Mat4 m;

	if ((eye.x == center.x) && (eye.y == center.y) && (eye.z == center.z)){
		std::cout << "GetView Function: Eye and center can't be the same" << std::endl;
		return m;
	}

	engine::Vec3 view(center.x - eye.x, center.y - eye.y, center.z - eye.z);
	view.Normalise();

	engine::Vec3 side = engine::cross(view, up);

	side.Normalise();

	engine::Vec3 u = engine::cross(side, view);



	m.matrix[0] = side.x;
	m.matrix[1] = u.x;
	m.matrix[2] = -view.x;
	m.matrix[3] = 0;
	m.matrix[4] = side.y;
	m.matrix[5] = u.y;
	m.matrix[6] = -view.y;
	m.matrix[7] = 0;
	m.matrix[8] = side.z;
	m.matrix[9] = u.z;
	m.matrix[10] = -view.z;
	m.matrix[11] = 0;
	m.matrix[12] = -engine::dot(side, eye);
	m.matrix[13] = -engine::dot(u, eye);
	m.matrix[14] = engine::dot(view, eye);
	m.matrix[15] = 1;


	//truncate
	for (int i = 0; i < 16; i++){
		m.matrix[i] = floorf(m.matrix[i] * 100.0f + 0.5f) / 100.0f;
	}

	return m;

}

engine::Mat4 engine::GetOrthoProjection(float top, float bottom, float left, float right, float nearZ, float farZ){
	engine::Mat4 m;

	float lmr = left - right;
	float rml = right - left;

	float bmt = bottom - top;
	float tmb = top - bottom;

	float nmf = nearZ - farZ;

	if ((lmr != 0) && (bmt != 0) && (nmf != 0) && (rml != 0) && (tmb != 0)){
		m.matrix[0] = 2 / rml;
		m.matrix[5] = 2 / tmb;
		m.matrix[10] = 2 / nmf;
		m.matrix[12] = (left + right) / lmr;
		m.matrix[13] = (top + bottom) / bmt;
		m.matrix[14] = (nearZ + farZ) / nmf;
		m.matrix[15] = 1;
	}
	else{
		std::cout << "returning 0...0 Matrix from GetOrthoPorjection, please check input" << std::endl;
	}

	//truncate
	for (int i = 0; i < 16; i++){
		m.matrix[i] = floorf(m.matrix[i] * 100.0f + 0.5f) / 100.0f;
	}


	return m;

}
engine::Mat4 engine::GetPerspProjection(float fovy, float aspect, float nearZ, float farZ){
	engine::Mat4 m;

	float angle = fovy / 2;
	float tan = tanf(angle * 3.141592f / 180.0f);
	float nmf = nearZ - farZ;

	if ((tan == 0) || (aspect == 0) || (nmf == 0)){
		std::cout << "returning 0...0 Matrix from GetPerspProjection, please check input" << std::endl;
		return m;
	}
	float d = 1 / tan;

	m.matrix[0] = d / aspect;
	m.matrix[5] = d;
	m.matrix[10] = (farZ + nearZ) / nmf;
	m.matrix[11] = -1;
	m.matrix[14] = (2 * farZ * nearZ) / nmf;

	//truncate
	for (int i = 0; i < 16; i++){
		m.matrix[i] = floorf(m.matrix[i] * 100.0f + 0.5f) / 100.0f;
	}


	return m;
}



std::ostream& engine::operator<<(std::ostream& os, const engine::Mat4& m){
	os << "[" << m.matrix[0] << " " << m.matrix[1] << " " << m.matrix[2] << " " << m.matrix[3] << "]" << std::endl
		<< "[" << m.matrix[4] << " " << m.matrix[5] << " " << m.matrix[6] << " " << m.matrix[7] << "]" << std::endl
		<< "[" << m.matrix[8] << " " << m.matrix[9] << " " << m.matrix[10] << " " << m.matrix[11] << "]" << std::endl
		<< "[" << m.matrix[12] << " " << m.matrix[13] << " " << m.matrix[14] << " " << m.matrix[15] << "]" << std::endl;
	return os;
}