#include "ShaderManipulator.h"


#define VERTICES 0
#define COLORS 1


GLuint ShaderManipulator::LoadVertexShader(char* path){
    std::ifstream fileReader(path);
    fileReader.seekg(0, std::ios::end);
    size_t size = (size_t) fileReader.tellg();
    std::string buffer(size, ' ');
    fileReader.seekg(0);
    fileReader.read(&buffer[0], size);
    const GLchar* aux = &(buffer[0]);

  GLuint VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(VertexShaderId, 1, &aux, 0);
  glCompileShader(VertexShaderId);


  GLint isCompiled = 0;  //check shader compiliation
  glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(VertexShaderId, GL_INFO_LOG_LENGTH, &maxLength);

    //The maxLength includes the NULL character
    std::vector<char> errorLog(maxLength);
    glGetShaderInfoLog(VertexShaderId, maxLength, &maxLength, &errorLog[0]);

    //Provide the infolog in whatever manor you deem best.
    //Exit with failure.
    glDeleteShader(VertexShaderId); //Don't leak the shader.
    std::cout << "Error on Vertex Shader Compiliation:  " << &errorLog << std::endl;

    return NULL;
  }

  return VertexShaderId;

}


GLuint ShaderManipulator::LoadFragmentShader(char* path){

  std::ifstream fileReader(path);
  fileReader.seekg(0, std::ios::end);
  size_t size = (size_t) fileReader.tellg();
  std::string buffer(size, ' ');
  fileReader.seekg(0);
  fileReader.read(&buffer[0], size);

  const GLchar* aux = &(buffer[0]);

  GLuint FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(FragmentShaderId, 1, &aux, 0);
  glCompileShader(FragmentShaderId);


  GLint isCompiled = 0;  //check shader compiliation
  glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &isCompiled);
  if (isCompiled == GL_FALSE)
  {
    GLint maxLength = 0;
    glGetShaderiv(FragmentShaderId, GL_INFO_LOG_LENGTH, &maxLength);

    //The maxLength includes the NULL character
    std::vector<char> errorLog(maxLength);
    glGetShaderInfoLog(FragmentShaderId, maxLength, &maxLength, &errorLog[0]);

    //Provide the infolog in whatever manor you deem best.
    //Exit with failure.
    glDeleteShader(FragmentShaderId); //Don't leak the shader.
    std::cout << "Error on Fragment Shader Compiliation:  "<< &errorLog << std::endl;
    return NULL;
  }

  return FragmentShaderId;

}



void ShaderManipulator::DestroyShader(GLuint ProgramId, GLuint ShaderId){

  glDetachShader(ProgramId,ShaderId);
  glDeleteShader(ShaderId);

}

ShaderManipulator::ShaderManipulator()
{
}

ShaderManipulator::~ShaderManipulator()
{
}
