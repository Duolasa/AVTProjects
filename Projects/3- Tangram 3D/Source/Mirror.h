#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "MatrixManip.h"

class Mirror
{
public:
  int width, height;
  GLuint FBOid, DRBid, Textureid, SamplerId;
  Mirror();
  void CreateFrameBuffer(int w, int h);
  void CreateTexture(int w, int h);
  void AddDepthBuffer();
  void Bind();
  void Unbind();
  ~Mirror();
};

