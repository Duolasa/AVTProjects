///////////////////////////////////////////////////////////////////////
//
// Assignment 4 consists in the following:
//
// - Access to different pieces of SomaCube.
// - Snap pieces.
// - Manipulation of pieces.
// - Construct object with pieces.
// - Basic graph scene.
//
// (c)2013	by Ruben Rebelo		nº55419
//			by Élvio Abreu		nº74100
//			by Rui Dias			nº67079
//			by Pedro Lousada	nº68582
//
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <string>


#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Engine.h"
#include "Pieces.h"

using namespace engine;

#define CAPTION "Hello Blank World"

#define VERTICES 0
#define COLORS 1

int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;
bool hasReshape = false;

GLint UboId, UniformId;
const GLuint UBO_BP = 0;

ShaderProgram *normalShader = new ShaderProgram();
/////////////////////////////////////////////////////////////////////// SHADERs


void createShaderProgram()
{
	//normalShader->loadShaders("shaders/vert.shader", "shaders/frag.shader");
	Shader vertS = Shader(GL_VERTEX_SHADER, "shaders/vert.shader");
	Shader fragS = Shader(GL_FRAGMENT_SHADER, "shaders/frag.shader");
	normalShader->loadShaders(vertS,fragS);
	normalShader->bindAttribute(VERTICES, "in_Position");
	normalShader->bindAttribute(COLORS, "in_Color");
	normalShader->linkProg();
	UniformId = normalShader->getUniformLocation("ModelMatrix");
	UboId = normalShader->getUniformBlockIndex("SharedMatrices", UBO_BP);

	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	normalShader->~ShaderProgram();

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	destroyShaderProgram();
}

void frameTimer(int value){
	glutPostRedisplay();
	
}

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Draw something
	glutSwapBuffers();

	glutTimerFunc(static_cast<int>(ceil(1000/60.0)), frameTimer, 0);
}

void idle()
{
	//glutPostRedisplay();
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

///////////////////////////////////////////////////////////////////////

void test(){
	Entity a = Entity(vertices,0);
}



/////////////////////////////////////////////////////////////////////// SETUP

void setupCallbacks() 
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glutTimerFunc(0,timer,0);
	glutTimerFunc(0, frameTimer, 0);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
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
	
	glutInitContextVersion(3, 3); //Opengl 4.3 max
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
	test();
	setupCallbacks();
}

int main(int argc, char* argv[])
{
	/**/
	init(argc, argv);
	glutMainLoop();	
	exit(EXIT_SUCCESS);
	/**/

	//SHADER_LIST::instance()->add("normal",normalShader);


}

///////////////////////////////////////////////////////////////////////