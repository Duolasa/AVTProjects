#include "Matrix.h"


Matrix::Matrix(GLfloat m[16]){

	for (int i = 0; i < 16; i++){
		matrix[i] = m[i];
	}

}


Matrix Matrix::GetIdentity(){
	GLfloat values[16] = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};// Row Major

		Matrix m(values);
		m.Transpose();
	
		return m;
}



Matrix Matrix::GetTranslation(float x, float y, float z){
	GLfloat values[16] = {
		1.0f, 0.0f, 0.0f, x,
		0.0f, 1.0f, 0.0f, y,
		0.0f, 0.0f, 1.0f, z,
		0.0f, 0.0f, 0.0f, 1.0f
	};// Row Major

	Matrix m(values);
	m.Transpose();

	return m;
}


Matrix Matrix::GetTranslation(Vector::vec3 v){
	return GetTranslation(v.x, v.y, v.z);

}

Matrix Matrix::GetRotation(float x, float y, float z, float angle){   //TODO - mudar para quaternions
	float cosine = cos(angle * 3.141592f / 180.0f);
	float sine = sin(angle * 3.141592f / 180.0f);

	GLfloat values[16] = {
		cosine + x*x*(1 - cosine), x*y*(1 - cosine) - z*sine, x*z*(1 - cosine) + y*sine, 0.0f,
		y*x*(1 - cosine) + z*sine, cosine + y*y*(1 - cosine), y*z*(1 - cosine) + x*sine, 0.0f,
		z*x*(1 - cosine) + y*sine, z*y*(1 - cosine) - x*sine, cosine + z*z*(1 - cosine), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};// Row Major

	Matrix m(values);
	m.Transpose();

	return m;
}



Matrix Matrix::GetRotation(Vector::vec3 v, float angle){
	return GetRotation(v.x, v.y, v.z, angle);
}

Matrix Matrix::GetScale(float x, float y, float z) {
	GLfloat values[16] = {
		x, 0.0f, 0.0f, 0.0f,
		0.0f, y, 0.0f, 0.0f,
		0.0f, 0.0f, z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};// Row Major

	Matrix m(values);
	m.Transpose();

	return m;
}


Matrix Matrix::GetScale(Vector::vec3 v){
	return GetScale(v.x, v.y, v.z);
}








void Matrix::Transpose(){
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

	for (int i = 0; i < 16; i++){
		matrix[i] = transpose[i];
	}
}


Matrix Matrix::operator* (Matrix m){
}

Matrix Matrix::operator= (Matrix m){
}

