///////////////////////////////////////////////////////////////////////
//
// Assignment 2 consists in the following:
//
// - Rewrite the program using C++ classes for:
//   - Matrix manipulation;
//   - Shader manipulation;
//   - Managing drawable entities.
//
// - Provide an UML diagram of your solution.
//
// - Add the following functionality:
//   - Read shader code from external files;
//   - Check shader compilation and linkage for error messages.
// 
// - Draw the following scene, minimizing the number of vertices on the GPU:
//   - A set of 7 TANs (i.e. TANGRAM shapes) of different colors;
//   - A flat surface on which the TANs will be placed (with an appropriate contrasting color).
//
// - Alternate between the following dispositions when the user presses the 't' key;
//   - The 7 TANs in their original square configuration;
//   - The 7 TANs put together to form a shape of your choice (6500 to choose from!);
//   - The silhouette of the shape of your choice on the flat surface.
//
// Further suggestions to verify your understanding of the concepts explored:
//
// - Use linear interpolation to create a transition between the two TAN configurations.
// - Parse geometrical information from external XML files.
//
// (c) 2013 by Carlos Martinho
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>

#include "GL/glew.h"
#include "GL/freeglut.h"
#include "MatrixManip.h"
#include "TangramManipulator.h"
#include "ShaderManipulator.h"

#define CAPTION "Hello New World"

int presentationMode = 0; // 0 - normal ; 1 - arranged, 2- silhouette
int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;

TangramManipulator* tangramManipulator = new TangramManipulator;
ShaderManipulator* shaderManipulator = new ShaderManipulator;


GLuint VaoId, VboId[2];
GLuint VertexShaderId, FragmentShaderId, ProgramId;
GLint UniformId, SilhouetteId;

/////////////////////////////////////////////////////////////////////// ERRORS

bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}

void checkOpenGLError(std::string error)
{
	if(isOpenGLError()) {
		std::cerr << error << std::endl;
    system("pause");
		exit(EXIT_FAILURE);
	}
}

/////////////////////////////////////////////////////////////////////// SHADERs


void createShaderProgram()
{
  VertexShaderId = shaderManipulator->LoadVertexShader("../2-Tangram/Source/Shaders/VertexShader.txt");

  FragmentShaderId = shaderManipulator->LoadFragmentShader("../2-Tangram/Source/Shaders/FragmentShader.txt");


	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glBindAttribLocation(ProgramId, VERTICES, "in_Position");
	glBindAttribLocation(ProgramId, COLORS, "in_Color");
	glLinkProgram(ProgramId);

  glUseProgram(ProgramId);

	UniformId = glGetUniformLocation(ProgramId, "Matrix");
  SilhouetteId = glGetUniformLocation(ProgramId, "Silhouette");



	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	glUseProgram(0);

  shaderManipulator->DestroyShader(ProgramId, VertexShaderId);
  shaderManipulator->DestroyShader(ProgramId, FragmentShaderId);

	glDeleteProgram(ProgramId);

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

/////////////////////////////////////////////////////////////////////// VAOs & VBOs

void createBufferObjects()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(2, VboId);

  tangramManipulator->fillVertexBuffer(VboId);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);

	checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
}

void destroyBufferObjects()
{
	glDisableVertexAttribArray(VERTICES);
	glDisableVertexAttribArray(COLORS);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glDeleteBuffers(2, VboId);
	glDeleteVertexArrays(1, &VaoId);
	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

/////////////////////////////////////////////////////////////////////// SCENE

typedef GLfloat Matrix[16];

MatrixManip* matrixManipulator = new MatrixManip();

GLfloat* piecesMatrices[8];

bool useSilhouette = false;

void drawScene()
{
  glBindVertexArray(VaoId);
  glUseProgram(ProgramId);
  glUniform1i(SilhouetteId, 0);

  glUniformMatrix4fv(UniformId, 1, GL_TRUE, piecesMatrices[7]);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*) 27);


  if (useSilhouette){
    glUniform1i(SilhouetteId, 1);
  }



  for (int i = 0; i < 5; i++){
    glUniformMatrix4fv(UniformId, 1, GL_TRUE, piecesMatrices[i]);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, (GLvoid*) (i*3));

  }

  for (int i = 0; i < 2; i++){
    glUniformMatrix4fv(UniformId, 1, GL_TRUE, piecesMatrices[5+i]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (GLvoid*) (15 + (i * 6)));

  }



	glUseProgram(0);
	glBindVertexArray(0);


  checkOpenGLError("ERROR: Could not draw scene.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	destroyShaderProgram();
	destroyBufferObjects();
}

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	drawScene();
	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	WinX = w;
	WinY = h;
	glViewport(0, 0, WinX, WinY);
}

void timer(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
    FrameCount = 0;
    glutTimerFunc(1000, timer, 0);
}

void processKeys(unsigned char key, int x, int y){
  if (presentationMode > 2){
    presentationMode = 0;
  }

  switch (key){
  case 't': 
    switch (presentationMode){
    case 0: matrixManipulator->fillWithIdentity(piecesMatrices);     
            useSilhouette = false;
            presentationMode++;
            break;
    case 1: matrixManipulator->fillWithPresetPosition(piecesMatrices);
             presentationMode++;
            break;
    case 2:useSilhouette = true;
           presentationMode++;
           break;
    }
  }

}
/////////////////////////////////////////////////////////////////////// SETUP


void setupCallbacks() 
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
  glutKeyboardFunc(processKeys);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);
}

void setupGLEW() {
	glewExperimental = GL_TRUE;
	GLenum result = glewInit() ; 
	if (result != GLEW_OK) { 
		std::cerr << "ERROR glewInit: " << glewGetString(result) << std::endl;
		exit(EXIT_FAILURE);
	} 
	GLenum err_code = glGetError();
}

void setupGLUT(int argc, char* argv[])
{
	glutInit(&argc, argv);
	
	glutInitContextVersion(3, 3);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	
	glutInitWindowSize(WinX, WinY);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	WindowHandle = glutCreateWindow(CAPTION);
	if(WindowHandle < 1) {
		std::cerr << "ERROR: Could not create a new rendering window." << std::endl;
		exit(EXIT_FAILURE);
	}
}

void init(int argc, char* argv[])
{
	setupGLUT(argc, argv);
	setupGLEW();
	setupOpenGL();
	createShaderProgram();
	createBufferObjects();
	setupCallbacks();
  matrixManipulator->fillWithIdentity(piecesMatrices);
}

int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();	
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////