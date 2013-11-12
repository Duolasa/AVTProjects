#include "MatrixManip.h"
#include <iostream>
#include <sstream>
#include <string>

MatrixManip::MatrixManip()
{
}


GLfloat* MatrixManip::GetIdentity(){
    Matrix aux = {
      1.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 1.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    };// Row Major

    GLfloat *identity = new GLfloat[16];
    for (int i = 0; i < 16; i++){
      identity[i] = aux[i];
    }


    return identity;
  }

GLfloat* MatrixManip::GetTranslation(float x, float y, float z){
    Matrix aux = {
      1.0f, 0.0f, 0.0f, x,
      0.0f, 1.0f, 0.0f, y,
      0.0f, 0.0f, 1.0f, z,
      0.0f, 0.0f, 0.0f, 1.0f
    };// Row Major

    GLfloat *translation = new GLfloat[16];
    for (int i = 0; i < 16; i++){
      translation[i] = aux[i];
    }

    return translation;
  }

GLfloat* MatrixManip::GetRotation(float a[3], float angle){
    float x = a[0];
    float y = a[1];
    float z = a[2];
    float cosine = cos(angle * 3.141592f  / 180.0f);
    float sine = sin(angle * 3.141592f / 180.0f);

    Matrix aux = {
      cosine + x*x*(1 - cosine), x*y*(1 - cosine) - z*sine, x*z*(1 - cosine) + y*sine, 0.0f,
      y*x*(1 - cosine) + z*sine, cosine + y*y*(1 - cosine), y*z*(1 - cosine) + x*sine, 0.0f,
      z*x*(1 - cosine) + y*sine, z*y*(1 - cosine) - x*sine, cosine + z*z*(1 - cosine), 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    };// Row Major

    std::cout << "-----------------" << std::endl;

    GLfloat *rotation = new GLfloat[16];
    for (int i = 0; i < 16; i++){
      rotation[i] = aux[i];
      std::cout << aux[i] << "  ";
    }
    std::cout << std::endl;
    return rotation;
  }


GLfloat* MatrixManip::GetScale(float x, float y, float z){
    Matrix aux = {
      x, 0.0f, 0.0f, 0.0f,
      0.0f, y, 0.0f, 0.0f,
      0.0f, 0.0f, z, 0.0f,
      0.0f, 0.0f, 0.0f, 1.0f
    };// Row Major

    GLfloat *scale = new GLfloat[16];
    for (int i = 0; i < 16; i++){
      scale[i] = aux[i];
    }

    return scale;
  }

GLfloat* MatrixManip::Multiply(Matrix A, Matrix B){
  GLfloat *result = new GLfloat[16] {0};

  for (int i = 0; i < 4; i++){
    //first row
    for (int j = 0;  j < 4; j++){
      result[i] += A[j] * B[(j * 4) + i];
    }
  }

  for (int i = 0; i < 4; i++){
    //second row
    for (int j = 0; j < 4; j++){
      result[4 + i] += A[4 + j] * B[(j * 4) + i];
    }
  }

  for (int i = 0; i < 4; i++){
    //third row
    for (int j = 0; j < 4; j++){
      result[8 + i] += A[8 + j] * B[(j * 4) + i];
    }
  }

  for (int i = 0; i < 4; i++){
    //forth row
    for (int j = 0; j < 4; j++){
      result[12 + i] += A[12 + j] * B[(j * 4) + i];
    }
  }

  return result;
}

float MatrixManip::CalculateNorm(float v[3]){

  return sqrtf((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]));
}

float* MatrixManip::CrossProduct(float a[3], float b[3]){
  float *result = new float[3];

  result[0] = (a[1] * b[2]) - (a[2] * b[1]);
  result[1] = (a[2] * b[0]) - (a[0] * b[2]);
  result[2] = (a[0] * b[1]) - (a[1] * b[0]);

return result;
}

float MatrixManip::DotProduct(float a[3], float b[3]){
  return (a[0] * b[0]) +
         (a[1] * b[1]) +
         (a[2] * b[2]);
}

GLfloat* MatrixManip::GetView(float eye[3], float center[3], float up[3]){    //COLUMN MAJOR 
  GLfloat *result = new GLfloat[16] {0};
  if ((eye[0] == center[0]) && (eye[1] == center[1]) && (eye[2] == center[2])){
    std::cout << "GetView Function: Eye and center can't be the same" << std::endl;
    return result;
  }

  float view [] = { center[0] - eye[0], center[1] - eye[1], center[2] - eye[2] };
  float normView = CalculateNorm(view);
  float v [] = { view[0] / normView, view[1] / normView, view[2] / normView };

  float* side = CrossProduct(v, up);

  float normSide = CalculateNorm(side);
  float s [] = { side[0] / normSide, side[1] / normSide, side[2] / normSide };

  float* u = CrossProduct(s, v);



  result[0] = s[0];
  result[1] = u[0];
  result[2] = -v[0];
  result[3] = 0;
  result[4] = s[1];
  result[5] = u[1];
  result[6] = -v[1];
  result[7] = 0;
  result[8] = s[2];
  result[9] = u[2];
  result[10] = -v[2];
  result[11] = 0;
  result[12] = -DotProduct(s, eye);
  result[13] = -DotProduct(u, eye);
  result[14] = DotProduct(v, eye);
  result[15] = 1; 


  return result;

}
GLfloat* MatrixManip::GetOrthoProjection(float top, float bottom, float left, float right, float nearZ, float farZ){    //COLUMN MAJOR
  GLfloat *result = new GLfloat[16] {0};

  float lmr = left - right;
  float rml = right - left;

  float bmt = bottom - top;
  float tmb = top - bottom;

  float nmf = nearZ - farZ;

  if ((lmr != 0) && (bmt != 0) && (nmf != 0) && (rml != 0) && (tmb != 0)){
    result[0] = 2 / rml;
    result[5] = 2 / tmb;
    result[10] = 2 / nmf;
    result[12] = (left + right) / lmr;
    result[13] = (top + bottom) / bmt;
    result[14] = (nearZ + farZ) / nmf;
    result[15] = 1;
  }
  else{
    std::cout << "returning 0...0 Matrix from GetOrthoPorjection, please check input" << std::endl;
  }

  return result;

}

GLfloat* MatrixManip::GetPerspProjection(float fovy, float aspect, float nearZ, float farZ){    //COLUMN MAJOR
  GLfloat *result = new GLfloat[16] {0};
  float angle = fovy / 2;
  float tan = tanf(angle * 3.141592f / 180.0f);
  float nmf = nearZ - farZ;

  if ((tan == 0) || (aspect == 0) || (nmf == 0)){
    std::cout << "returning 0...0 Matrix from etPerspProjection, please check input" << std::endl;
    return result;
  }
  float d = 1 / tan;
  
  result[0] = d / aspect;
  result[5] = d;
  result[10] = (farZ + nearZ) / nmf;
  result[11] = -1;
  result[14] = (2 * farZ * nearZ) / nmf;

  return result;
}



