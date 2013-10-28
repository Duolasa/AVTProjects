#include "MatrixManip.h"
#include <iostream>
#include <sstream>
#include <string>

MatrixManip::MatrixManip()
{
}


GLfloat* MatrixManip::getIdentity(){
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

GLfloat* MatrixManip::getTranslation(float x, float y, float z){
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

GLfloat* MatrixManip::getRotation(float a[3], float angle){
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

    GLfloat *rotation = new GLfloat[16];
    for (int i = 0; i < 16; i++){
      rotation[i] = aux[i];
    }

    return rotation;
  }


GLfloat* MatrixManip::getScale(float x, float y, float z){
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

GLfloat* MatrixManip::multiply(Matrix A, Matrix B){
    GLfloat *result = new GLfloat[16] {0};

    for (int i = 0; i < 4; i++){//first row
      for (int j = 0;  j < 4; j++){
        result[i] += A[j] * B[(j * 4) + i];
      }
    }

    for (int i = 0; i < 4; i++){//second row
      for (int j = 0; j < 4; j++){
        result[4 + i] += A[4 + j] * B[(j * 4) + i];
      }
    }

    for (int i = 0; i < 4; i++){//third row
      for (int j = 0; j < 4; j++){
        result[8 + i] += A[8 + j] * B[(j * 4) + i];
      }
    }

    for (int i = 0; i < 4; i++){//forth row
      for (int j = 0; j < 4; j++){
        result[12 + i] += A[12 + j] * B[(j * 4) + i];
      }
    }

    return result;
  }

void MatrixManip::fillWithIdentity(GLfloat* piecesMatrices []){
  for (int i = 0; i < 8; i++){
    free(piecesMatrices[i]);
    piecesMatrices[i] = getIdentity();
  }




}

void MatrixManip::fillWithPresetPosition(GLfloat* piecesMatrices []){
  for (int i = 0; i < 8; i++){
    free(piecesMatrices[i]);
  }

  float z [] = { 0.0f, 0.0f, 1.0f };

  GLfloat* rotation = getRotation(z, 90.0f);
  GLfloat* translation = getTranslation(-0.527f, 0.0f, 0.0f);
  piecesMatrices[0] = multiply(translation, rotation);
  free(rotation);
  free(translation);


  rotation = getRotation(z, 180.0f);
  translation = getTranslation(0.527f, 0.0f, 0.0f);
  piecesMatrices[1] = multiply(translation, rotation);
  free(rotation);
  free(translation);


  rotation = getRotation(z, 90.0f);
  translation = getTranslation(-0.29f, -0.2625f, 0.0f);
  piecesMatrices[2] = multiply(translation, rotation);
  free(rotation);
  free(translation);


  rotation = getRotation(z, -45.0f);
  translation = getTranslation(0.53f, -0.75f, 0.0f);
  piecesMatrices[3] = multiply(translation, rotation);
  free(rotation);
  free(translation);


  rotation = getRotation(z, 90.0f);
  translation = getTranslation(0.0f, -0.52f, 0.0f);
  piecesMatrices[4] = multiply(translation, rotation);
  free(rotation);
  free(translation);


  rotation = getRotation(z, 00.0f);
  translation = getTranslation(-0.54f, 0.0f, 0.0f);
  piecesMatrices[5] = multiply(translation, rotation);
  free(rotation);
  free(translation);


  rotation = getRotation(z, -90.0f);
  translation = getTranslation(0.69f, -0.91f, 0.0f);
  piecesMatrices[6] = multiply(translation, rotation);
  free(rotation);
  free(translation);


  piecesMatrices[7] = getIdentity();


}

