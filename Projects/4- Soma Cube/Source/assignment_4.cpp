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

#include "OpenGLErrors.h"

#include "Manager.h"
#include "Pieces.h"
#include "Mirror.h"
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

int LastMousePositionX;
int LastMousePositionY;
float RotationAngleY = 0.0f;
float RotationAngleX = 0.0f;
float CameraScale = 1;
float smoothScale = 1.01f;

Quaternion editRotation;
Vec3 editTranslation;

bool _x = true, _y = false, _z = false;
std::string filename;
int selectedPiece = 1;

ShaderProgram *normalShader = new ShaderProgram();

Mirror mirror1 = Mirror();
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
	normalShader->destroyShaderProgram();

	checkOpenGLError("ERROR: Could not destroy shaders.");
}

//////////////////////////////////////////////////////////////////////// VBOs VAOs

Entity entity;
Manager manager;

void createBufferObjects(){

	manager.createPieces(UBO_BP);
	//entity.createBufferObject(PieceCube, UBO_BP);

	checkOpenGLError("ERROR: Could not create VAOs VBOs");
}

void destroyBufferObject(){

	//entity.destroyBufferObject();
	manager.destroyPieces();
	checkOpenGLError("ERROR: Could not destroy VAOs VBOs");
}

void draw(){

	manager.setCamera(RotationAngleX, RotationAngleY);
	RotationAngleY = RotationAngleX = 0;

	manager.drawPieces(normalShader, UniformId, selectedPiece, editTranslation, editRotation);
	editTranslation = Vec3(0.0f);
	editRotation = Quaternion(0.0f,X_AXIS);

	checkOpenGLError("ERROR: Could not draw");
}
/////////////////////////////////////////////////////////////////////// KEYS

void processNormalKeys(unsigned char key, int x, int y) {

	Quaternion qx = Quaternion(90.0f, X_AXIS); 
	Quaternion qxn = Quaternion(-90.0f, X_AXIS);

	Quaternion qz = Quaternion(90.0f, Z_AXIS);
	Quaternion qzn = Quaternion(-90.0f, Z_AXIS);

	Quaternion qy = Quaternion(90.0f, Y_AXIS);
	Quaternion qyn = Quaternion(-90.0f, Y_AXIS);

	if (key == 'z') { _z = true; _y = false; _x = false;} //changes z axis/coords
	if (key == 'x') { _z = false; _y = false; _x = true;} //changes x axis/coords
	if (key == 'c') { _z = false; _y = true; _x = false;} //changes y axis/coords

	if (key == 'a' && _z) editTranslation.x = 1.0f;
	if (key == 'd' && _z) editTranslation.x = - 1.0;
	if (key == 'w' && _z) editTranslation.y =  1.0;
	if (key == 's' && _z) editTranslation.y = - 1.0;
	if (key == 'q' && _z) editRotation = qz;
	if (key == 'e' && _z) editRotation = qzn;

	if (key == 'a' && _y) editTranslation.x =  1.0;
	if (key == 'd' && _y) editTranslation.x = - 1.0;
	if (key == 'w' && _y) editTranslation.z =  1.0;
	if (key == 's' && _y) editTranslation.z = - 1.0;
	if (key == 'q' && _y) editRotation = qy;
	if (key == 'e' && _y) editRotation = qyn;

	if (key == 'a' && _x) editTranslation.y =  1.0;
	if (key == 'd' && _x) editTranslation.y = - 1.0;
	if (key == 'w' && _x) editTranslation.z =  1.0;
	if (key == 's' && _x) editTranslation.z = - 1.0;
	if (key == 'q' && _x) editRotation = qx;
	if (key == 'e' && _x) editRotation = qxn;


	if (key == '1' ) selectedPiece = 1;
	if (key == '2' ) selectedPiece = 2;
	if (key == '3' ) selectedPiece = 3;
	if (key == '4' ) selectedPiece = 4;
	if (key == '5' ) selectedPiece = 5;
	if (key == '6' ) selectedPiece = 6;
	if (key == '7' ) selectedPiece = 7;

	if (key == 'n'){
		std::cout << "Please enter filename to save: ";
		std::cin >> filename;
		//manager.saveCurrent(filename);
		std::cout << "Filename saved: " << "xml/" << filename << ".xml" << std::endl;
	}

	if (key == 'm'){
		std::cout << "Please enter filename to load: ";
		std::cin >> filename;
		//manager.loadCurrent(filename);
		std::cout << "Filename loaded: " << "xml/" << filename << ".xml" << std::endl;
	}

}

/////////////////////////////////////////////////////////////////////// CALLBACKS

void cleanup()
{
	destroyShaderProgram();
	destroyBufferObject();
}

void frameTimer(int value){
	glutPostRedisplay();

}

void display()
{
	++FrameCount;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Draw something
	draw();

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
	//Entity a = Entity(SmallLPiece,0);

}

void processMouse(int button, int state, int x, int y){
	LastMousePositionX = x;
	LastMousePositionY = y;		

	if (button == 3) // scroll up
	{
		CameraScale *= smoothScale;
	}

	if (button == 4){ //scroll down
		CameraScale /= smoothScale;
	}

}

void processMouseMove(int x, int y){
	RotationAngleY += (x - LastMousePositionX);
	LastMousePositionX = x;

	RotationAngleX += (y - LastMousePositionY);
	LastMousePositionY = y;
}

/////////////////////////////////////////////////////////////////////// SETUP

void setupCallbacks() 
{
	glutCloseFunc(cleanup);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

	glutMouseFunc(processMouse);
	glutMotionFunc(processMouseMove);

	glutKeyboardFunc(processNormalKeys);

	glutTimerFunc(0,timer,0);
	glutTimerFunc(0, frameTimer, 0);
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
	createBufferObjects();
	//test();
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