///////////////////////////////////////////////////////////////////////
//
// Assignment 3 consists in the following:
//
// - Create the following changes to your scene, making it fully 3D:
//   - Extrude your TANs into the 3rd dimension. The TANs should have
//     slightly different "heights".
//   - The new faces of each TAN should share the same hue as the 
//     original top face color but have different levels of saturation 
//     and brightness (use an external app if needed).
//   - The shape is now built vertically (i.e. rather than horizontally
//     as in assignment 2) but still on top of the surface.
//   - When the TANs join to create your chosen shape, they should not 
//     be perfectly aligned in the new dimension.
//
// - Add the following functionality:
//   - Create a View Matrix from (eye, center, up) parameters.
//   - Create an Orthographic Projection Matrix from (left-right, 
//     bottom-top, near-far) parameters.
//   - Create a Perspective Projection Matrix from (fovy, aspect,
//     nearZ, farZ) parameters.
//   - Implement rotations through quaternions.
//
// - Add the following dynamics to the application:
//   - Create a spherical 3D camera controlled by the mouse allowing to 
//     visualize the scene through all its angles.
//   - Change perspective from orthographic to perspective and back as
//     a response to pressing the key 'p'.
//   - The scene starts with the 7 TANs in their original square 
//     configuration, laying flat and horizontally on the surface.
//   - Each time the 't' key is pressed, one of the TANs will move from 
//     its resting place to its position in your chosen shape, now 
//     presented vertically.
//
// Further suggestions:
//   - Use mouse interaction to select which TAN will be next moved 
//     into place or moved back to its resting position.
//   - Create an edit mode in which the user can edit the shape in
//     real-time (e.g. position, rotation, color).
//   - Allow to load and save the TANGRAM shapes from external files.
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
#include "Camera.h"

#define CAPTION "Hello New World"
#define radiansToDegrees 57.2957795131f
#define degreesToRadians 0.01745329251f
#define PI 3.14159265359f

int perspectiveMode = 1; // 0- Orthographic ; 1 - Perspective
int WinX = 640, WinY = 480;
int WindowHandle = 0;
bool RMBdown = false;
unsigned int FrameCount = 0;
float eye [] = { 5, 5, 5 };
float center [] = { 0, 0, 1 };
float up [] = { 0, 0, 1 };
int mouseX, mouseY, elapsedTime;
static TangramManipulator* tangramManipulator = new TangramManipulator;
static ShaderManipulator* shaderManipulator = new ShaderManipulator;
MatrixManip* matrixManipulator = new MatrixManip();
int lastMovedPiece = 0;

static Camera* camera = new Camera(matrixManipulator->GetView(eye, center, up),
                                     matrixManipulator->GetOrthoProjection(2,-2,-2,2,1,20),
                                     matrixManipulator->GetPerspProjection(30, 640.0f / 480.0f, 1, 20));

GLuint VertexShaderId, FragmentShaderId, ProgramId, SharedMatricesBuffer;
GLint ModelMatrixId, SilhouetteId, SharedMatricesId;
const GLuint UBO_BP = 0;


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
  VertexShaderId = shaderManipulator->LoadVertexShader("../3- Tangram 3D/Source/Shaders/VertexShader.txt");

  FragmentShaderId = shaderManipulator->LoadFragmentShader("../3- Tangram 3D/Source/Shaders/FragmentShader.txt");


	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);

	glBindAttribLocation(ProgramId, VERTICES, "in_Position");
	glBindAttribLocation(ProgramId, COLORS, "in_Color");
	glLinkProgram(ProgramId);

  glUseProgram(ProgramId);

	ModelMatrixId = glGetUniformLocation(ProgramId, "ModelMatrix");
  SilhouetteId = glGetUniformLocation(ProgramId, "Silhouette");

  SharedMatricesId = glGetUniformBlockIndex(ProgramId, "SharedMatrices");
  glUniformBlockBinding(ProgramId, SharedMatricesId, UBO_BP);

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
  camera->CreateBuffers();

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

	checkOpenGLError("ERROR: Could not destroy VAOs and VBOs.");
}

/////////////////////////////////////////////////////////////////////// SCENE

typedef GLfloat Matrix[16];

void drawScene()
{
  glUseProgram(ProgramId);


  tangramManipulator->DrawPieces(ModelMatrixId);
  

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
//  elapsedTime = glutGet(GLUT_ELAPSED_TIME);
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


void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
  {
    mouseX = x;
    mouseY = y;
    RMBdown = true;
  //  xdiff = x - yrot;
  //  ydiff = -y + xrot;
  }
  else  if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
  {
    RMBdown = false;

  }

}

void moveCamera(int x, int y){
 // int timeDiff = glutGet(GLUT_ELAPSED_TIME) - elapsedTime;
 // std::cout << timeDiff << std::endl;

  float xMovement = (float) x / 200;
  float yMovement = (float) y / 200;
  GLfloat *aux;
  float theta = camera->theta + yMovement;
  float phi = camera->phi + xMovement;
  float radius = camera->radius;

  if (theta > PI - 0.1f){
    theta = PI -0.1f;
  }
  else if (theta < 0.1f){
    theta = 0.1f;
  }

  if (phi > PI * 2){
    phi = 0;
  }
  else if (phi < 0){
    phi = PI * 2;
  }

  camera->theta = theta;
  camera->phi = phi;

  float newEye [] = { radius*sinf(theta ) * cosf(phi ),
                      radius*sinf(theta ) * sinf(phi ),
                      radius * cosf(theta ) };
  float newCenter [] = { 0.0f, 0.0f, 1.0f };


  aux = matrixManipulator->GetView(newEye, newCenter, camera->up);

  free(camera->viewMatrix);
  camera->viewMatrix = aux;
  camera->ChangeViewMatrix();

  glutPostRedisplay();

}


void processKeys(unsigned char key, int x, int y){


  switch (key){
  case 'r':
          tangramManipulator->ResetPieces();
          glUseProgram(ProgramId);
          glUniform1i(SilhouetteId, 0);
          glUseProgram(0);
          lastMovedPiece = 0;
          break;

  case 't':
      tangramManipulator->FillWithPresetPosition( lastMovedPiece++);
      
      break;

  case 'p':
    if (perspectiveMode == 0){
      perspectiveMode++;
      camera->OrthoProjection();
    }
    else{
      perspectiveMode = 0;
      camera->PerspProjection();

    }
    break;

  }

}

void mouseMotion(int x, int y)
{
  int diffX = mouseX - x;
  int diffY = mouseY - y;
  mouseX = x;
  mouseY = y;
  if (RMBdown)
  {
   
    moveCamera(diffX, diffY);
 
  }
}

void animate(int i){

  tangramManipulator->animatePieces();
  glutTimerFunc(25, animate, 0);

}


void setupCallbacks() 
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
  glutTimerFunc(25, animate, 0);
  glutKeyboardFunc(processKeys);
  glutMouseFunc(mouse);
  glutMotionFunc(mouseMotion);
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
  tangramManipulator->CreatePieces();
}


int main(int argc, char* argv[])
{
	init(argc, argv);
	glutMainLoop();	
	exit(EXIT_SUCCESS);
}

///////////////////////////////////////////////////////////////////////