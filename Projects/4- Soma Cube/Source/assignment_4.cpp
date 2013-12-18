///////////////////////////////////////////////////////////////////////
//
// Assignment 4/5 consists in the following:
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

#include "Piece.h"
#include "SomaPiece.h"
#include "Board.h"

#include "Manager.h"
#include "Mirror.h"

#include "OpenGLErrors.h"

using namespace engine;

#define CAPTION "Hello Blank World"


int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;
bool hasReshape = false;

Mirror mirror = Mirror();

GLint UboId, UniformId;
const GLuint UBO_BP = 0;
GLuint VBOID;

int LastMousePositionX;
int LastMousePositionY;
float RotationAngleY = 0.0f;
float RotationAngleX = 0.0f;
float CameraScale = 0.0f;

int mouse_x;
int mouse_y;

bool persp = true;

bool mouseView = false;
int identifier = 0;
std::string axis = "X_AXIS";

double cam_xmin, cam_xmax, cam_ymin, cam_ymax;

Position position;

ShaderProgram *normalShader;
Shader vertS = Shader(GL_VERTEX_SHADER);
Shader fragS = Shader(GL_FRAGMENT_SHADER);

ShaderProgram *blackShader;
Shader vertSb = Shader(GL_VERTEX_SHADER);
Shader fragSb = Shader(GL_FRAGMENT_SHADER);

ShaderProgram *whiteShader;
Shader vertSw = Shader(GL_VERTEX_SHADER);
Shader fragSw = Shader(GL_FRAGMENT_SHADER);
/////////////////////////////////////////////////////////////////////// SHADERs
Manager manager;

void createShaderProgram()
{
	/** /
	vertS.loadShader("shaders/vert_normals.shader");
	fragS.loadShader("shaders/frag_normals.shader");
	normalShader = new ShaderProgram(vertS,fragS);
	normalShader->bindAttribute(VERTICES, "in_Position");
	normalShader->bindAttribute(COLORS, "in_Color");
	normalShader->bindAttribute(NORMALS, "in_Normal");
	normalShader->linkProg();
	UniformId = normalShader->getUniformLocation("ModelMatrix");
	UboId = normalShader->getUniformBlockIndex("SharedMatrices", UBO_BP);

	////////////////////////////////////////////////////////////////////////
	vertSb.loadShader("shaders/vert.shader");
	fragSb.loadShader("shaders/fragb.shader");
	blackShader = new ShaderProgram(vertSb,fragSb);
	blackShader->bindAttribute(VERTICES, "in_Position");
	blackShader->bindAttribute(COLORS, "in_Color");
	blackShader->linkProg();
	UniformId = blackShader->getUniformLocation("ModelMatrix");
	UboId = blackShader->getUniformBlockIndex("SharedMatrices", UBO_BP);

	////////////////////////////////////////////////////////////////////////
	vertSw.loadShader("shaders/vert.shader");
	fragSw.loadShader("shaders/fragw.shader");
	whiteShader = new ShaderProgram(vertSw,fragSw);
	whiteShader->bindAttribute(VERTICES, "in_Position");
	whiteShader->bindAttribute(COLORS, "in_Color");
	whiteShader->linkProg();
	UniformId = whiteShader->getUniformLocation("ModelMatrix");
	UboId = whiteShader->getUniformBlockIndex("SharedMatrices", UBO_BP);
	
	SHADER_PROGRAM_LIST::instance()->add("normal", normalShader);
	SHADER_PROGRAM_LIST::instance()->add("black", blackShader);
	SHADER_PROGRAM_LIST::instance()->add("white", whiteShader);
	/**/
	manager.createShaderPrograms();

	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	/** /
	normalShader->destroyShaderProgram();
	vertS.deleteShader();
	fragS.deleteShader();
	/////////////////////////////////////////////////
	blackShader->destroyShaderProgram();
	vertSb.deleteShader();
	fragSb.deleteShader();

	/////////////////////////////////////////////////
	whiteShader->destroyShaderProgram();
	vertSw.deleteShader();
	fragSw.deleteShader();
	/**/

	manager.destroyShadersPrograms();
	checkOpenGLError("ERROR: Could not destroy shaders.");
}

//////////////////////////////////////////////////////////////////////// VBOs VAOs
Mesh cubeMesh;
Entity entityMesh;
Entity entityCube;
Line line;
Board board = Board(9);

BigLPiece bigLPiece = BigLPiece();
SmallLPiece smallLPiece = SmallLPiece();

Camera camera;

void createBufferObjects(){
	/** /
	camera.setPerspProjection(30, 640/480.0f, 1, 100);
	camera.setOrthoProjection(-2,2,-2,2,1,15);
	camera.setLookAt(Vec3(0,0,30),Vec3(0,0,0),Vec3(0,1,0));

	line.createBufferObject(UBO_BP);

	cubeMesh = Mesh("models/bevelCube.obj");
	entityCube = cubeMesh.getMeshEntity(UBO_BP);

	smallLPiece.setInitPosition(Vec3(0));
	smallLPiece.createBufferObject(UBO_BP);
	//bigLPiece.createBufferObject(UBO_BP);

	VBOID = smallLPiece.getVboId();

	position.translation = Vec3(0);
	position.rotation = Quaternion();

	board.setPiece(smallLPiece.getPiecePositions(), smallLPiece.getSize(),smallLPiece.getStencilId());
	/**/
	manager.setCamera();
	manager.createBufferObjects();

	position.translation = Vec3(0);
	position.rotation = Quaternion();

	checkOpenGLError("ERROR: Could not create VAOs VBOs");
}

void destroyBufferObject(){
	/** /
	entityCube.destroyBufferObject();
	line.destroyBufferObject();
	smallLPiece.destroyBufferObject();
	//bigLPiece.destroyBufferObject();
	/**/
	manager.destroyBufferObjects();
	checkOpenGLError("ERROR: Could not destroy VAOs VBOs");
}

void setupBoard(){
	manager.setupBoard();
}

Quaternion qx = Quaternion();

void draw(){
	/** /
	camera.draw(persp, VBOID, RotationAngleX, RotationAngleY, CameraScale);
	RotationAngleY = RotationAngleX = 0;
	
	//////////////////////////////////////////////////////////
	//bigLPiece.setPosition(position);
	//bigLPiece.draw(UniformId, identifier);

	// once upon a time... 

	Vec3* previousPos = smallLPiece.getPiecePositions();
	Vec3 ppp[4];
	ppp[0] = previousPos[0];
	ppp[1] = previousPos[1];
	ppp[2] = previousPos[2];
	ppp[3] = previousPos[3];
	Vec3* previousPos2;
	previousPos2 = ppp;

	smallLPiece.givePosition(position,identifier);

	Vec3* newPos = smallLPiece.getPiecePositions();
	Vec3 ppp2[4];
	ppp2[0] = newPos[0];
	ppp2[1] = newPos[1];
	ppp2[2] = newPos[2];
	ppp2[3] = newPos[3];
	Vec3* newPos2;
	newPos2 = ppp2;


	if(board.canMove(newPos2, smallLPiece.getSize(),smallLPiece.getStencilId())){
		board.erasePiece(previousPos2, smallLPiece.getSize(),smallLPiece.getStencilId());
		board.setPiece(newPos, smallLPiece.getSize(),smallLPiece.getStencilId());
		smallLPiece.setPiecePositions(newPos2);
		smallLPiece.draw(UniformId, identifier);
	}else{
		smallLPiece.setPiecePositions(previousPos2);
		smallLPiece.draw(UniformId, identifier);
	}

	//entityCube.draw(normalShader, UniformId);

	/** /
	Position posId = bigLPiece.getPositionIdentifier();
	posId.translation = posId.translation * 1.1; //same as scale of cubes

	if(identifier != 0){
		line.setPosition(posId);
		line.draw(UniformId, axis);
	}
	/**/
	/** /
	line.draw(UniformId, "X_AXIS");
	line.draw(UniformId, "Y_AXIS");
	line.draw(UniformId, "Z_AXIS");

	position.translation = Vec3(0);
	position.rotation = Quaternion();
	/**/

	//manager.setPosition(position);
	//manager.setIdentifier(identifier);
	mirror.Bind();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	manager.draw(persp, RotationAngleX, RotationAngleY, CameraScale, position, identifier);
	RotationAngleY = RotationAngleX = 0;

	position.translation = Vec3(0);
	position.rotation = Quaternion();

	mirror.Unbind();

	manager.drawMirror(persp, RotationAngleX, RotationAngleY, CameraScale, position, identifier);


	manager.draw(persp, RotationAngleX, RotationAngleY, CameraScale, position, identifier);
	RotationAngleY = RotationAngleX = 0;

	position.translation = Vec3(0);
	position.rotation = Quaternion();


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
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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

	 if (w > h)
    {
        cam_xmin = -double(w)/h;
        cam_xmax = double(w)/h;
        cam_ymin = -1.;
        cam_ymax = 1.;
    }
    else
    {
        cam_xmin = -1.;
        cam_xmax = 1.;
        cam_ymin = -double(h)/w;
        cam_ymax = double(h)/w;
    }

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

// Mouse
double cam_mousex, cam_mousey; // Mouse x, y pos (camunits)
                               //  Above initialized to 0., 0.
                               //  then set at first mouse event
bool dragging = false;

void processNormalKeys(unsigned char key, int x, int y) {
	if (key == 'q') axis = "X_AXIS";
	if (key == 'w') axis = "Y_AXIS";
	if (key == 'e') axis = "Z_AXIS";

	if(key == 'a'){
		if(axis == "X_AXIS") position.rotation = Quaternion(90,X_AXIS);
		if(axis == "Y_AXIS") position.rotation = Quaternion(90,Y_AXIS);
		if(axis == "Z_AXIS") position.rotation = Quaternion(90,Z_AXIS);
	}

	if(key == 'd'){
		if(axis == "X_AXIS") position.rotation = Quaternion(-90,X_AXIS);
		if(axis == "Y_AXIS") position.rotation = Quaternion(-90,Y_AXIS);
		if(axis == "Z_AXIS") position.rotation = Quaternion(-90,Z_AXIS);
	}

	if(key == 'p'){
		persp = !persp;
	}
}

void saveMousePos(int x, int y)
{
    double t;  // Lirping parameter

	t = double(x)/WinX;
    cam_mousex = cam_xmin + t*(cam_xmax-cam_xmin);

    t = double(y)/WinY;
    cam_mousey = cam_ymax + t*(cam_ymin-cam_ymax);

}

void mousedy(int x, int y){
	double old_mousex = cam_mousex;
    double old_mousey = cam_mousey;
    // Compute mouse pos in camera coords & save in globals
    saveMousePos(x, y);

	int valx = 0, valy = 0;

	if(dragging && identifier != 0){
		if(axis == "X_AXIS"){
			if((cam_mousex - old_mousex)*1000 > 8) valx = 1;
			if((cam_mousex - old_mousex)*1000 < -8) valx = -1;
			position.translation.x = position.translation.x + valx;
			if((cam_mousey - old_mousey)*1000 > 8) valy = 1;
			if((cam_mousey - old_mousey)*1000 < -8) valy = -1;
			position.translation.x = position.translation.x + valy;
		}else if(axis == "Y_AXIS"){
			if((cam_mousex - old_mousex)*1000 > 8) valx = 1;
			if((cam_mousex - old_mousex)*1000 < -8) valx = -1;
			position.translation.y = position.translation.y + valx;
			if((cam_mousey - old_mousey)*1000 > 8) valy = 1;
			if((cam_mousey - old_mousey)*1000 < -8) valy = -1;
			position.translation.y = position.translation.y + valy;
		}else if(axis == "Z_AXIS"){
			if((cam_mousex - old_mousex)*1000 > 8) valx = 1;
			if((cam_mousex - old_mousex)*1000 < -8) valx = -1;
			position.translation.z = position.translation.z + valx;
			if((cam_mousey - old_mousey)*1000 > 8) valy = 1;
			if((cam_mousey - old_mousey)*1000 < -8) valy = -1;
			position.translation.z = position.translation.z + valy;
		} 

	}
	glutPostRedisplay();
	//std::cerr << (cam_mousex - old_mousex)*1000 << " " <<  (cam_mousey - old_mousey)*1000 << std::endl;
}

void processMouseMove(int x, int y){
	if(mouseView){
		RotationAngleY += (x - LastMousePositionX);
		LastMousePositionX = x;

		RotationAngleX += (y - LastMousePositionY);
		LastMousePositionY = y;
	}

	if(dragging){
		mousedy(x,y);
	}
}


void mousedw(int x, int y, int but)
 {
	mouse_x = x;
	mouse_y = y;

	unsigned int stencil[4];
	glReadPixels(mouse_x, 480 - mouse_y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, stencil);
	identifier = stencil[0];
	//std::cerr <<"id " <<identifier << std::endl;
	 
	
}

void processMouse(int button, int state, int x, int y){

	if 	((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
	{
		LastMousePositionX = x;
		LastMousePositionY = y;
		mouseView = true;
		
	}
	else
		mouseView = false;

	if 	((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)){
		dragging = true;
		mousedw(x, y, button);
		//mousedy(x,y,button);
	}else{
		dragging =false;
	}

	//mousedy(x,y,button);
	//dragging = (state == GLUT_DOWN);

	if (button == 3) // scroll up
	{
		CameraScale += .5;
	}

	if (button == 4){ //scroll down
		CameraScale -= .5;
	}

	//std::cerr << position.translation << std::endl;
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
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
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
	setupBoard();
	setupCallbacks();
}

int main(int argc, char* argv[])
{
	/**/
	init(argc, argv);

	mirror.CreateFrameBuffer(640, 480);
	mirror.AddDepthBuffer();
	mirror.Unbind();

	glutMainLoop();	
	exit(EXIT_SUCCESS);
	/**/

	/** /
	Quaternion vi = Quaternion(0,0,1,1);
	Quaternion q = Quaternion(90,Z_AXIS);

	Quaternion f = (q * vi) * q.Inverse();

	std::cerr << f << std::endl;
	
	/** /
	Quaternion qi = Quaternion(1,0,0,0);
	Quaternion qf = Quaternion(90,1,0,0);

	Quaternion f = qi * qf;
	std::cerr << f << std::endl;
	/**/
}

///////////////////////////////////////////////////////////////////////