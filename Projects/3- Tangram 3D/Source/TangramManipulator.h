#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "MatrixManip.h"
#include "TangramPiece.h"


#define VERTICES 0
#define COLORS 1


class TangramManipulator
{
public:
  GLuint VaoId;
  TangramPiece pieces[8];
  MatrixManip matrixGenerator;

public:
  void CreatePieces();
  void FillWithIdentity();
  void FillWithPresetPosition();
  void DrawPieces(GLint UniformId);
  TangramManipulator();
  ~TangramManipulator();
};

