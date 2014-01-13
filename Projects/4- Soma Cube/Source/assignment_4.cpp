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

#include "freeimage\FreeImage.h"

#include "Engine.h"

#include "Piece.h"
#include "SomaPiece.h"
#include "Board.h"

#include "Manager.h"

#include "OpenGLErrors.h"

using namespace engine;

#define CAPTION "Hello Blank World"


int WinX = 640, WinY = 480;
int WindowHandle = 0;
unsigned int FrameCount = 0;
bool hasReshape = false;

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
int imageid = 0;

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
	manager.createShaderPrograms();

	checkOpenGLError("ERROR: Could not create shaders.");
}

void destroyShaderProgram()
{
	manager.destroyShadersPrograms();
	checkOpenGLError("ERROR: Could not destroy shaders.");
}

//////////////////////////////////////////////////////////////////////// VBOs VAOs

void createBufferObjects(){
	
	
	manager.createBufferObjects();

	position.translation = Vec3(0);
	position.rotation = Quaternion();

	checkOpenGLError("ERROR: Could not create VAOs VBOs");
}

void destroyBufferObject(){
	manager.destroyBufferObjects();
	checkOpenGLError("ERROR: Could not destroy VAOs VBOs");
}

void setupManager(){
	manager.setCamera();
	manager.setMirror(WinX, WinY);
	manager.setupBoard();
}

void draw(){

	manager.drawMirrorsAndCamera(persp, RotationAngleX, RotationAngleY, CameraScale);
	manager.draw(position, identifier);
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

	manager.setMirror(WinX, WinY);
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

void ScreenShot(){

	unsigned char* pixels = new unsigned char[3 * WinX * WinY];

	glReadPixels(0, 0, WinX, WinY, GL_BGR, GL_UNSIGNED_BYTE, pixels);

	// Convert to FreeImage format & save to file
	FIBITMAP* image = FreeImage_ConvertFromRawBits(pixels, WinX, WinY, 3 * WinX, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);  //RGB

	std::string str;
	std::cout << "Please enter name of screenshot to save: ";
	std::cin >> str;
	std::string filename = "screenshots/" + str +".bmp";

	if (FreeImage_Save(FIF_BMP, image, filename.c_str(), 0)){
		std::cout << "Screenshot Saved."<< std::endl;
	}
	else{
		std::cout << "Failed to save screenshot" << std::endl;
	}

	// Free resources
	FreeImage_Unload(image);
	delete[] pixels;

}


/////////////////////////////////////////////////////////////////////////////////////////


// Mouse
double cam_mousex, cam_mousey; // Mouse x, y pos (camunits)
                               //  Above initialized to 0., 0.
                               //  then set at first mouse event
bool dragging = false;

void processSpecialKeys(int key, int x, int y) {
	if(!dragging && identifier != 0){
		switch(key){
			case GLUT_KEY_UP:
				position.translation.z -= 1;
			break;	
			case GLUT_KEY_DOWN:
				position.translation.z += 1;
			break;
			case GLUT_KEY_LEFT:
				position.translation.x -= 1;
			break;
			case GLUT_KEY_RIGHT:
				position.translation.x += 1;
			break;
		}
	}
}

void processNormalKeys(unsigned char key, int x, int y) {
	std::string filename;

	if(key == 'a'){
		position.rotation = Quaternion(90,Z_AXIS);
	}

	if(key == 'd'){
		position.rotation = Quaternion(-90,Z_AXIS);
	}
	if(key == 'q'){
		position.rotation = Quaternion(90,Y_AXIS);
	}

	if(key == 'e'){
		position.rotation = Quaternion(-90,Y_AXIS);
	}
	if(key == 'w'){
		position.rotation = Quaternion(90,X_AXIS);
	}

	if(key == 's'){
		position.rotation = Quaternion(-90,X_AXIS);
	}

	if(key == 'p'){
		persp = !persp;
	}

	if(key == 'm'){
		std::cout << "Please enter filename to save: ";
		std::cin >> filename;

		manager.savePiece(filename);
		std::cout << "File saved" << std::endl;
	}

	if(key == 'n'){
		std::cout << "Please enter filename to load: ";
		std::cin >> filename;
		manager.loadPiece(filename);
		std::cout << "File loaded" << std::endl;
	}

	if(key == 'i'){
		std::cout << "Please enter filename to load solution: ";
		std::cin >> filename;
		manager.loadSolution(filename);
		std::cout << "Solution loaded" << std::endl;
	}

	if (key == 'h'){
		manager.useShadows = !manager.useShadows;
	}

	if(key == 'o'){
		ScreenShot();
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
			if((cam_mousex - old_mousex)*1000 > 5) valx = 1;
			if((cam_mousex - old_mousex)*1000 < -5) valx = -1;
			position.translation.y = valx;
			if((cam_mousey - old_mousey)*1000 > 5) valy = 1;
			if((cam_mousey - old_mousey)*1000 < -5) valy = -1;
			position.translation.y = valy;
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
	glutSpecialFunc(processSpecialKeys);
	glutKeyboardFunc(processNormalKeys);

	glutTimerFunc(0,timer,0);
	glutTimerFunc(0, frameTimer, 0);
}

void setupOpenGL() {
	std::cerr << "CONTEXT: OpenGL v" << glGetString(GL_VERSION) << std::endl;
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
	setupManager();
	setupCallbacks();
}

int main(int argc, char* argv[])
{
	/**/
	init(argc, argv);
	glutMainLoop();	
	exit(EXIT_SUCCESS);
	/**/

	/** /
	Quaternion vi = Quaternion(0,0,1,1);
	Quaternion q = Quaternion(90,Z_AXIS);

	Quaternion f = (q * vi) * q.Inverse();

	std::cerr << f << std::endl;
	
	/** /
	Quaternion qi = Quaternion(90,X_AXIS);
	Quaternion qf = Quaternion(180,X_AXIS);

	Quaternion f = qf * qi.Inverse();

	float angle;
	Vec4 axis;

	f.ToAngleAxis(angle,axis);

	std::cerr << f << std::endl;
	std::cerr << angle << " " << axis << std::endl;
	/**/
}

///////////////////////////////////////////////////////////////////////