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
  TangramPiece pieces[9];
  MatrixManip matrixGenerator;

public:
  void CreatePieces();
  void ResetPieces();
  void FillWithPresetPosition(int pieceID);
  void DrawPieces(GLint UniformId);
  TangramManipulator();
  ~TangramManipulator();
};

