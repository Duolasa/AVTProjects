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
	//normalShader.destroyShaderProgram();

	glUseProgram(0);

	//std::cerr << glIsShader(normalShader.vertexShader.id()) << std::endl;

	unsigned int  vs = normalShader->vertexShader.getId();
	unsigned int  fs = normalShader->fragmentShader.getId();
	unsigned int  ps = normalShader->getId();
	glDetachShader(ps, vs);
	glDetachShader(ps, fs);
	
	
	//std::cerr << normalShader.vertexShader.id() << std::endl;
	
	//glDeleteShader(fs);
	//normalShader->fragmentShader.delShader();
	checkOpenGLError("ERROR: ...");
	//glDeleteShader(vs);
	glDeleteProgram(ps);
	
	checkOpenGLError("ERROR: Could not destroy shaders.");
}

//////////////////////////////////////////////////////////////////////// VBOs VAOs

Entity entity;
Manager manager;

void createBufferObjects(){

	manager.createPieces(UBO_BP);
	entity.createBufferObject(PieceCube, UBO_BP);

	checkOpenGLError("ERROR: Could not create VAOs VBOs");
}

void destroyBufferObject(){
	
	entity.destroyBufferObject();
	manager.destroyPieces();
	checkOpenGLError("ERROR: Could not destroy VAOs VBOs");
}






Quaternion qx = Quaternion(0.0f, Z_AXIS);

void draw(){
	/**/
	Mat4 projectionMatrix = GetPerspProjection(30,640/480.0f,1,15);
	Mat4 viewMatrixx = GetView(Vec3(0,0,10),Vec3(0,0,0),Vec3(0,1,0));

	
	Quaternion qX = Quaternion(RotationAngleY*.5f, Y_AXIS);
	Quaternion qY = Quaternion(RotationAngleX*.5f, X_AXIS);
	RotationAngleY = RotationAngleX = 0;

	Quaternion qv = qX * qY;

	qx = qv * qx;
	//qx = qMultiply(qZ,qY);
	//aux = rotY * rotZ;

	//qPrint("qx", qx);
	Mat4 m = qx.getMatrix();
	//m.Transpose();
	viewMatrixx =   m * viewMatrixx ;

	viewMatrixx = GetScale(CameraScale) * viewMatrixx;

	glBindBuffer(GL_UNIFORM_BUFFER, entity.getVboId());
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4), viewMatrixx.matrix);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Mat4), sizeof(Mat4), projectionMatrix.matrix);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	/**/
	
	//entity.draw(normalShader,UniformId,GetIdentity().matrix);
	manager.drawPieces(normalShader, UniformId);

	checkOpenGLError("ERROR: Could not draw");
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