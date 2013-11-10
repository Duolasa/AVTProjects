#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "MatrixManip.h"
#include <iostream>
#include <vector>



#define VERTICES 0
#define COLORS 1


class TangramPiece
{
public:
  typedef struct {
    GLfloat XYZW[4];
    GLfloat RGBA[4];
  } Vertex;

public:
  GLuint VaoId, VboId[2];
  std::vector<Vertex>vertices;
  std::vector<GLubyte> indices;
  GLfloat* transformationMatrix;

public:
  TangramPiece();
  ~TangramPiece();
  void draw(GLint UniformId);
  void createBuffers();

};

