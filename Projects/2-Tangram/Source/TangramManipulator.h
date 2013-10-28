#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "MatrixManip.h"

#define VERTICES 0
#define COLORS 1


class TangramManipulator
{
public:
  typedef struct {
    GLfloat XYZW[4];
    GLfloat RGBA[4];
  } Vertex;

public:
  void fillVertexBuffer(GLuint VboId[]);
  TangramManipulator();
  ~TangramManipulator();
};

