#ifndef MANAGER_H
#define MANAGER_H

#include "Engine.h"
#include "SomaPiece.h"
#include "Board.h"

#define VERTICES 0
#define COLORS 1
#define NORMALS 2
#define TEXTURE_COORDS 3

namespace engine {
	class Manager {
	private:

		ShaderProgram *normalShader, *blackShader, *whiteShader, *textureShader;

		Shader vertS, fragS;
		Shader vertSb, fragSb;
		Shader vertSw, fragSw;
		Shader vertSt, fragSt;

		GLint UboId, UniformId, GsamplerId;
		GLuint UBO_BP;
		GLuint VBOID;

		Line line;

		Entity entityCube; //for test only

		// board
		Board board;

		// Pieces
		Entity reflectionPlane;
    Entity reflectionPlane2;
		BigLPiece bigLPiece;
		SmallLPiece smallLPiece;
		TPiece tPiece;
		SnakePiece snakePiece;
		StrangePiece1 strangePiece1;
		StrangePiece2 strangePiece2;
		CornerPiece cornerPiece;

		//Position _position; //position to move

		//int _identifier; //identifier of selected piece

	public:
    Camera camera;

		Manager(){ UBO_BP = 0; board = Board(9); }
		~Manager(){}

		void createShaderPrograms(){

			
			vertSt = Shader(GL_VERTEX_SHADER);
			fragSt = Shader(GL_FRAGMENT_SHADER);

			vertSt.loadShader("shaders/vert_texture.shader");
			fragSt.loadShader("shaders/frag_texture.shader");
			textureShader = new ShaderProgram(vertSt, fragSt);
			textureShader->bindAttribute(VERTICES, "in_Position");
			textureShader->bindAttribute(TEXTURE_COORDS, "in_textCoord");
			textureShader->linkProg();
			UniformId = textureShader->getUniformLocation("ModelMatrix");
			UboId = textureShader->getUniformBlockIndex("SharedMatrices", UBO_BP);
			GsamplerId = textureShader->getUniformLocation("gsampler");
			
			///////////////////////////////////////////////////////////////////////
			vertS = Shader(GL_VERTEX_SHADER);
			fragS = Shader(GL_FRAGMENT_SHADER);

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
			vertSb = Shader(GL_VERTEX_SHADER);
			fragSb = Shader(GL_FRAGMENT_SHADER);

			vertSb.loadShader("shaders/vert.shader");
			fragSb.loadShader("shaders/fragb.shader");
			blackShader = new ShaderProgram(vertSb,fragSb);
			blackShader->bindAttribute(VERTICES, "in_Position");
			blackShader->bindAttribute(COLORS, "in_Color");
			blackShader->linkProg();
			UniformId = blackShader->getUniformLocation("ModelMatrix");
			UboId = blackShader->getUniformBlockIndex("SharedMatrices", UBO_BP);

			////////////////////////////////////////////////////////////////////////

			vertSw = Shader(GL_VERTEX_SHADER);
			fragSw = Shader(GL_FRAGMENT_SHADER);

			vertSw.loadShader("shaders/vert.shader");
			fragSw.loadShader("shaders/fragw.shader");
			whiteShader = new ShaderProgram(vertSw,fragSw);
			whiteShader->bindAttribute(VERTICES, "in_Position");
			whiteShader->bindAttribute(COLORS, "in_Color");
			whiteShader->linkProg();
			UniformId = whiteShader->getUniformLocation("ModelMatrix");
			UboId = whiteShader->getUniformBlockIndex("SharedMatrices", UBO_BP);
	
			///////////////////////////////////////////////////////////////////////
			SHADER_PROGRAM_LIST::instance()->add("normal", normalShader);
			SHADER_PROGRAM_LIST::instance()->add("black", blackShader);
			SHADER_PROGRAM_LIST::instance()->add("white", whiteShader);
		}

		void destroyShadersPrograms(){

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
		}

		void init(){

		}

		void setCamera(){
			camera.setPerspProjection(30, 640/480.0f, 1, 100);
		//	camera.setOrthoProjection(-2,2,-2,2,0,1500);
			camera.setOrthoProjection(20, -20, -20, 20, 0, 1000);

			camera.setLookAt(Vec3(0,0,30),Vec3(0,0,0),Vec3(0,1,0));
		}

    

		void createBufferObjects(){
			//bigLPiece = BigLPiece();
			//smallLPiece = SmallLPiece();

			line.createBufferObject(UBO_BP);
			Mesh planeMesh = Mesh("models/Plane.obj");
			reflectionPlane = planeMesh.getMeshEntity(UBO_BP);
      reflectionPlane2 = planeMesh.getMeshEntity(UBO_BP);


			//for test
			Mesh cubeMesh = Mesh("models/bevelCube.obj");
			entityCube = cubeMesh.getMeshEntity(UBO_BP);

			smallLPiece.setInitPosition(Vec3(0));
			smallLPiece.createBufferObject(UBO_BP);

			bigLPiece.setInitPosition(Vec3(0));
			bigLPiece.createBufferObject(UBO_BP);

			tPiece.setInitPosition(Vec3(0));
			tPiece.createBufferObject(UBO_BP);

			strangePiece1.setInitPosition(Vec3(0));
			strangePiece1.createBufferObject(UBO_BP);

			strangePiece2.setInitPosition(Vec3(0));
			strangePiece2.createBufferObject(UBO_BP);

			cornerPiece.setInitPosition(Vec3(0));
			cornerPiece.createBufferObject(UBO_BP);

			//return VBOID of last piece created
			VBOID = cornerPiece.getVboId();
		}

		void setupBoard(){ //TODO set board
			//set board pieces
			//board.setPiece(smallLPiece.getPiecePositions(), smallLPiece.getSize(),smallLPiece.getStencilId());
			board.setPiece(bigLPiece.getPiecePositions(), bigLPiece.getSize(),bigLPiece.getStencilId());
			//board.setPiece(tPiece.getPiecePositions(), tPiece.getSize(),tPiece.getStencilId());
			//board.setPiece(strangePiece1.getPiecePositions(), strangePiece1.getSize(),strangePiece1.getStencilId());
			//board.setPiece(strangePiece2.getPiecePositions(), strangePiece2.getSize(),strangePiece2.getStencilId());
			//board.setPiece(cornerPiece.getPiecePositions(), cornerPiece.getSize(),cornerPiece.getStencilId());
		}

		void destroyBufferObjects(){
			reflectionPlane.destroyBufferObject();
      reflectionPlane2.destroyBufferObject();
			entityCube.destroyBufferObject();
			line.destroyBufferObject();
			smallLPiece.destroyBufferObject();
			bigLPiece.destroyBufferObject();
			tPiece.destroyBufferObject();
			strangePiece1.destroyBufferObject();
			strangePiece2.destroyBufferObject();
			cornerPiece.destroyBufferObject();
		}

		void drawMirror(bool persp, float RotationAngleX, float RotationAngleY, float CameraScale, Position position, GLuint id){
		//	glUniform1i(GsamplerId, 0);
      camera.draw(persp, VBOID, RotationAngleX, RotationAngleY, CameraScale);

		//	camera.draw(persp, VBOID, RotationAngleX, RotationAngleY, CameraScale);
			reflectionPlane.setScale(Vec3(2.0f, 2.0f, 2.0f));
			reflectionPlane.draw(textureShader, UniformId);
		}

		void draw(bool persp, float RotationAngleX, float RotationAngleY, float CameraScale, Position position, GLuint id){
			camera.draw(persp, VBOID, RotationAngleX, RotationAngleY, CameraScale);

			//draw all other pieces
			drawPiece(&bigLPiece, position, id);
			//drawPiece(&smallLPiece, position, id);
			//drawPiece(&tPiece, position, id);
			//drawPiece(&strangePiece1, position, id);
			//drawPiece(&strangePiece2, position, id);
			//drawPiece(&cornerPiece, position, id);

			line.draw(UniformId, "X_AXIS");
			line.draw(UniformId, "Y_AXIS");
			line.draw(UniformId, "Z_AXIS");

		}

		//piece as pointer because it doesnt work other way around
		void drawPiece(SomaPiece *piece, Position pos, GLuint id){

			// Once upon a time...
			// pointer to a function gives the same values...
			// therefore put the values in a array
			Vec3* previousPos = piece->getPiecePositions();
			Vec3 ppp[4];
			ppp[0] = previousPos[0];
			ppp[1] = previousPos[1];
			ppp[2] = previousPos[2];
			ppp[3] = previousPos[3];
			Vec3* previousPos2;
			previousPos2 = ppp;

			piece->givePosition(pos, id);

			Vec3* newPos = piece->getPiecePositions();
			Vec3 ppp2[4];
			ppp2[0] = newPos[0];
			ppp2[1] = newPos[1];
			ppp2[2] = newPos[2];
			ppp2[3] = newPos[3];
			Vec3* newPos2;
			newPos2 = ppp2;


			if(board.canMove(newPos2, piece->getSize(),piece->getStencilId())){
				board.erasePiece(previousPos2, piece->getSize());
				board.setPiece(newPos, piece->getSize(),piece->getStencilId());
				piece->setPiecePositions(newPos2);
				piece->draw(UniformId, id);
			}else{
				piece->setPiecePositions(previousPos2);
				piece->draw(UniformId, id);
			}
		}

	};
}

#endif //MANAGER_H