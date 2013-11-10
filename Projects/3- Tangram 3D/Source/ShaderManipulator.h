#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>


class ShaderManipulator
{

public:
  GLuint LoadVertexShader(char* path);
  GLuint LoadFragmentShader(char* path);
  GLuint CreateProgram(GLuint VertexShaderId, GLuint FragmentShaderId);
  void DestroyShader(GLuint ProgramId, GLuint ShaderId);
  ShaderManipulator();
  ~ShaderManipulator();
};

