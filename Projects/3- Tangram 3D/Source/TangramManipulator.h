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
  TangramPiece mirror;
  float frame[9];
  MatrixManip matrixGenerator;

public:
  void CreatePieces();
  void ResetPieces();
  void animatePieces();
  void FillWithPresetPosition(int pieceID);
  void DrawPieces(GLint UniformId);
  void DrawMirror(GLint UniformId);
  TangramManipulator();
  ~TangramManipulator();
};

