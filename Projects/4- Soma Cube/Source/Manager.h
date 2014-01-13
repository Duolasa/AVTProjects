#ifndef MANAGER_H
#define MANAGER_H

#include "Engine.h"
#include "SomaPiece.h"
#include "Board.h"
#include "Mirror.h"

#include "ReadWritePieces.h"

#define VERTICES 0
#define COLORS 1
#define NORMALS 2
#define TEXTURE_COORDS 3

#define MAX_PIECES 30

namespace engine {
	class Manager {
	private:

		ShaderProgram *normalShader, *blackShader, *whiteShader, *textureShader, *goochShader, *textureShader2, *transparentShader;

		Shader vertS, fragS;
		Shader vertStr, fragStr;
		Shader vertSb, fragSb;
		Shader vertSw, fragSw;
		Shader vertSt, fragSt;
		Shader vertSg, fragSg;
		Shader vertSt2, fragSt2;

		GLint UboId, UniformId, GsamplerId, GsamplerId21, GsamplerId22;;
		GLuint UBO_BP;
		GLuint VBOID;

		Camera camera;
		Line line;

		Entity entityCube; //for test only
		Entity reflectionPlane[6];

		// board
		Board board;

		// Pieces
		BigLPiece bigLPiece;
		SmallLPiece smallLPiece;
		TPiece tPiece;
		SnakePiece snakePiece;
		StrangePiece1 strangePiece1;
		StrangePiece2 strangePiece2;
		CornerPiece cornerPiece;

		//Solution Positions
		PiecePosition bigLPiecePos;
		PiecePosition smallLPiecePos;
		PiecePosition tPiecePos;
		PiecePosition snakePiecePos;
		PiecePosition strangePiece1Pos;
		PiecePosition strangePiece2Pos;
		PiecePosition cornerPiecePos;


		Mirror sharedFrameBuffer, shadowBuffer[6];

		int _boardSize;

		Camera _mainCamera, _mirrorCamera[6];

		ReadWritePiece rwPiece;
		int _currentNumberPieces;		
		int _orderPieces[MAX_PIECES];	// order that the cubes are drawn
		SomaPiece *pieces[MAX_PIECES];

		Entity solutionCubes[MAX_PIECES]; //for test only

	public:

		bool useShadows;
		bool onlyonce;
		Manager(){ UBO_BP = 0; _boardSize = 9; board = Board(_boardSize); useShadows = false; onlyonce = true;}
		~Manager(){}

		

		/////////////////////////////////////////////////////////////////////////////////////// CREATE SHADERS

		void createShaderPrograms(){
			vertSt2 = Shader(GL_VERTEX_SHADER);
			fragSt2 = Shader(GL_FRAGMENT_SHADER);

			vertSt2.loadShader("shaders/vert_texture.shader");
			fragSt2.loadShader("shaders/frag_texture2.shader");
			textureShader2 = new ShaderProgram(vertSt2, fragSt2);
			textureShader2->bindAttribute(VERTICES, "in_Position");
			textureShader2->bindAttribute(TEXTURE_COORDS, "in_textCoord");
			textureShader2->linkProg();
			UniformId = textureShader2->getUniformLocation("ModelMatrix");
			UboId = textureShader2->getUniformBlockIndex("SharedMatrices", UBO_BP);
			GsamplerId21 = textureShader2->getUniformLocation("gsampler1");
			GsamplerId22 = textureShader2->getUniformLocation("gsampler2");


			///////////////////////////////////////////////////////////////////////
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

			////////////////////////////////////

			vertS = Shader(GL_VERTEX_SHADER);
			fragS = Shader(GL_FRAGMENT_SHADER);

			vertS.loadShader("shaders/vert_normals.shader");
			fragS.loadShader("shaders/frag.shader");
			normalShader = new ShaderProgram(vertS,fragS);
			normalShader->bindAttribute(VERTICES, "in_Position");
			normalShader->bindAttribute(COLORS, "in_Color");
			normalShader->bindAttribute(NORMALS, "in_Normal");
			normalShader->linkProg();
			UniformId = normalShader->getUniformLocation("ModelMatrix");
			UboId = normalShader->getUniformBlockIndex("SharedMatrices", UBO_BP);

			///////////////////////////////////
			vertSg = Shader(GL_VERTEX_SHADER);
			fragSg = Shader(GL_FRAGMENT_SHADER);

			vertSg.loadShader("shaders/vertg.shader");
			fragSg.loadShader("shaders/fragg.shader");
			goochShader = new ShaderProgram(vertSg,fragSg);
			goochShader->bindAttribute(VERTICES, "in_Position");
			goochShader->bindAttribute(COLORS, "in_Color");
			goochShader->bindAttribute(NORMALS, "in_Normal");
			goochShader->linkProg();
			UniformId = goochShader->getUniformLocation("ModelMatrix");
			goochShader->getUniformLocation("lightPosition");
			goochShader->getUniformLocation("warmColor");
			goochShader->getUniformLocation("coolColor");
			goochShader->getUniformLocation("cameraPos");
			goochShader->setParameter("lightPosition", Vec4(0,4,0,1));
			goochShader->setParameter("warmColor", Vec3(0.6, 0.6, 0.0));
			goochShader->setParameter("coolColor", Vec3(0.0, 0.0, 0.6));
			goochShader->setParameter("cameraPos", _mainCamera.cameraPoint());
			UboId = goochShader->getUniformBlockIndex("SharedMatrices", UBO_BP);

			///////////////////////////////////
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

			////////////////////////////////////

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

			////////////////////////////////////

			vertStr = Shader(GL_VERTEX_SHADER);
			fragStr = Shader(GL_FRAGMENT_SHADER);

			vertStr.loadShader("shaders/vert.shader");
			fragStr.loadShader("shaders/frag.shader");
			transparentShader = new ShaderProgram(vertStr,fragStr);
			transparentShader->bindAttribute(VERTICES, "in_Position");
			transparentShader->bindAttribute(COLORS, "in_Color");
			transparentShader->linkProg();
			UniformId = transparentShader->getUniformLocation("ModelMatrix");
			UboId = transparentShader->getUniformBlockIndex("SharedMatrices", UBO_BP);
	
			///////////////////////////////////
			SHADER_PROGRAM_LIST::instance()->add("normal", normalShader);
			SHADER_PROGRAM_LIST::instance()->add("gooch", goochShader);
			SHADER_PROGRAM_LIST::instance()->add("black", blackShader);
			SHADER_PROGRAM_LIST::instance()->add("white", whiteShader);
		}

		/////////////////////////////////////////////////////////////////////////////////////// DESTROY SHADERS
		void destroyShadersPrograms(){
			textureShader2->destroyShaderProgram();
			vertSt2.deleteShader();
			fragSt2.deleteShader();
			////////////////////////////////////
			textureShader->destroyShaderProgram();
			vertSt.deleteShader();
			fragSt.deleteShader();
			////////////////////////////////////

			goochShader->destroyShaderProgram();
			vertSg.deleteShader();
			fragSg.deleteShader();
			////////////////////////////////////

			normalShader->destroyShaderProgram();
			vertS.deleteShader();
			fragS.deleteShader();
			////////////////////////////////////
			blackShader->destroyShaderProgram();
			vertSb.deleteShader();
			fragSb.deleteShader();

			////////////////////////////////////
			whiteShader->destroyShaderProgram();
			vertSw.deleteShader();
			fragSw.deleteShader();
		}


		/////////////////////////////////////////////////////////////////////////////////////// CREATEBUFFER OBJECTS
		void createBufferObjects(){
			
			line.createBufferObject(UBO_BP);

			Mesh planeMesh = Mesh("models/Plane.obj");

			for(int i = 0; i < 6; i++){
				reflectionPlane[i] = planeMesh.getMeshEntity(UBO_BP);
			}

			//for test
			Mesh cubeMesh = Mesh("models/bevelCube.obj");
			entityCube = cubeMesh.getMeshEntity(UBO_BP);

			for(int i = 0; i < MAX_PIECES; i++){
				solutionCubes[i] = cubeMesh.getMeshEntity(UBO_BP);
			}

			smallLPiece.setInitPosition(Vec3(0));
			smallLPiece.createBufferObject(UBO_BP);

			bigLPiece.setInitPosition(Vec3(1,0,0));
			bigLPiece.createBufferObject(UBO_BP);

			tPiece.setInitPosition(Vec3(1));
			tPiece.createBufferObject(UBO_BP);

			strangePiece1.setInitPosition(Vec3(-1));
			strangePiece1.createBufferObject(UBO_BP);

			strangePiece2.setInitPosition(Vec3(-3));
			strangePiece2.createBufferObject(UBO_BP);

			cornerPiece.setInitPosition(Vec3(3));
			cornerPiece.createBufferObject(UBO_BP);

			//return VBOID of last piece created
			VBOID = cornerPiece.getVboId();
		}

		/////////////////////////////////////////////////////////////////////////////////////// DESTROYBUFFER OBJECTS

		void destroyBufferObjects(){

			for(int i = 0; i < MAX_PIECES; i++){
				solutionCubes[i].destroyBufferObject();
			}

			for(int i = 0; i < MAX_PIECES; i++){
				reflectionPlane[i].destroyBufferObject();
			}
			
			entityCube.destroyBufferObject();
			line.destroyBufferObject();
			smallLPiece.destroyBufferObject();
			bigLPiece.destroyBufferObject();
			tPiece.destroyBufferObject();
			strangePiece1.destroyBufferObject();
			strangePiece2.destroyBufferObject();
			cornerPiece.destroyBufferObject();
		}

		/////////////////////////////////////////////////////////////////////////////////////// SETUP 

		void setCamera(){
			_mainCamera.setPerspProjection(30, 640/480.0f, 1.0f, 50.0f);
		
			_mainCamera.setOrthoProjection(20, -20, -20, 20, 0, 1000);
			_mainCamera.setLookAt(Vec3(0, 0, 30), Vec3(0, 0, 0), Vec3(0, 1, 0));

			float relativeSize = _boardSize/2+2; 


			for(int i = 0;i<6;i++)
				_mirrorCamera[i].setOrthoProjection(relativeSize, -relativeSize, -relativeSize, relativeSize, 0, 25);

			SetMirrorPositions();
		}

		void setupBoard(){ 
			//set board pieces
			board.setPiece(bigLPiece.getPiecePositions(), bigLPiece.getSize(),bigLPiece.getStencilId());
			board.setPiece(smallLPiece.getPiecePositions(), smallLPiece.getSize(),smallLPiece.getStencilId());
			board.setPiece(tPiece.getPiecePositions(), tPiece.getSize(),tPiece.getStencilId());
			board.setPiece(strangePiece1.getPiecePositions(), strangePiece1.getSize(),strangePiece1.getStencilId());
			board.setPiece(strangePiece2.getPiecePositions(), strangePiece2.getSize(),strangePiece2.getStencilId());
			board.setPiece(cornerPiece.getPiecePositions(), cornerPiece.getSize(),cornerPiece.getStencilId());

			pieces[0] = &bigLPiece;
			pieces[1] = &smallLPiece;
			pieces[2] = &tPiece;
			pieces[3] = &strangePiece1;
			pieces[4] = &strangePiece2;
			pieces[5] = &cornerPiece;
			_currentNumberPieces = 6;
		}

		void drawFinalShadow(Position position, GLuint id, Camera mirrorCamera){
			/**/

			PiecePosition bLP = bigLPiece.getPiecePositions();
			PiecePosition sLP = smallLPiece.getPiecePositions();
			PiecePosition tP = tPiece.getPiecePositions();
			PiecePosition sP = snakePiece.getPiecePositions();
			PiecePosition sP1 = strangePiece1.getPiecePositions();
			PiecePosition sP2 = strangePiece2.getPiecePositions();
			PiecePosition cP = cornerPiece.getPiecePositions();

			bigLPiece.setPiecePositions(bigLPiecePos);
			bigLPiece.draw(UniformId, 0, blackShader, true, mirrorCamera.cameraPoint());

			smallLPiece.setPiecePositions(smallLPiecePos);
			smallLPiece.draw(UniformId, 0, blackShader, true, mirrorCamera.cameraPoint());

			tPiece.setPiecePositions(tPiecePos);
			tPiece.draw(UniformId, 0, blackShader, true, mirrorCamera.cameraPoint());

			snakePiece.setPiecePositions(snakePiecePos);
			snakePiece.draw(UniformId, 0, blackShader, true, mirrorCamera.cameraPoint());

			strangePiece1.setPiecePositions(strangePiece1Pos);
			strangePiece1.draw(UniformId, 0, blackShader, true, mirrorCamera.cameraPoint());

			strangePiece2.setPiecePositions(strangePiece2Pos);
			strangePiece2.draw(UniformId, 0, blackShader, true, mirrorCamera.cameraPoint());

			cornerPiece.setPiecePositions(cornerPiecePos);
			cornerPiece.draw(UniformId, 0, blackShader, true, mirrorCamera.cameraPoint());
			/**/
			board.setSolutionBoard(bigLPiecePos, 4);
			board.setSolutionBoard(smallLPiecePos, 3);
			board.setSolutionBoard(tPiecePos, 4);
			board.setSolutionBoard(strangePiece1Pos, 4);
			board.setSolutionBoard(strangePiece2Pos, 4);
			board.setSolutionBoard(cornerPiecePos, 4);

			//loadPiece("default");

			bigLPiece.setPiecePositions(bLP);
			smallLPiece.setPiecePositions(sLP);
			tPiece.setPiecePositions(tP);
			snakePiece.setPiecePositions(sP);
			strangePiece1.setPiecePositions(sP1);
			strangePiece2.setPiecePositions(sP2);
			cornerPiece.setPiecePositions(cP);
			
		}

		void drawFinalShadows(){

			Position pos;

			for(int i = 0; i<4;i++){
				shadowBuffer[i].Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			
				_mirrorCamera[i].draw(false, VBOID, 0, 0, 0);
				drawFinalShadow(pos, 0, _mirrorCamera[i]);

				shadowBuffer[i].Unbind();
			}
		}

		void SetMirrorPositions(){
			reflectionPlane[0].setTranslation(Vec3(-_boardSize / 2 - 2, 0, 0));
			reflectionPlane[0].setScale(Vec3(_boardSize / 2 + 1));
			_mirrorCamera[0].setLookAt(Vec3(-5, 0, 0), Vec3(0, 0, 0), Vec3(0, -1, 0));

			reflectionPlane[1].setRotation(Quaternion(-90, Y_AXIS));
			reflectionPlane[1].setTranslation(Vec3(0, 0, -_boardSize / 2 - 2));
			reflectionPlane[1].setScale(Vec3(_boardSize / 2 + 1));
			_mirrorCamera[1].setLookAt(Vec3(0, 0, -5), Vec3(0, 0, 0), Vec3(0, -1, 0));

			reflectionPlane[2].setRotation(Quaternion(180, Y_AXIS));
			reflectionPlane[2].setTranslation(Vec3(_boardSize / 2 + 2, 0, 0));
			reflectionPlane[2].setScale(Vec3(_boardSize / 2 + 1));
			_mirrorCamera[2].setLookAt(Vec3(5, 0, 0), Vec3(0, 0, 0), Vec3(0, -1, 0));

			reflectionPlane[3].setRotation(Quaternion(90, Y_AXIS));
			reflectionPlane[3].setTranslation(Vec3(0, 0, _boardSize / 2 + 2));
			reflectionPlane[3].setScale(Vec3(_boardSize / 2 + 1));
			_mirrorCamera[3].setLookAt(Vec3(0, 0, 5), Vec3(0, 0, 0), Vec3(0, -1, 0));
			/** /
			reflectionPlane[4].setRotation(Quaternion(-90, Z_AXIS));
			reflectionPlane[4].setTranslation(Vec3(0, _boardSize / 2 + 2, 0));
			reflectionPlane[4].setScale(Vec3(_boardSize / 2 + 1));
			_mirrorCamera[4].setLookAt(Vec3(0, -5, 0), Vec3(0, 0, 0), Vec3(0, 0, 1));
			
			reflectionPlane[5].setRotation(Quaternion(90, Z_AXIS));
			reflectionPlane[5].setTranslation(Vec3(0, -_boardSize / 2 - 2, 0));
			reflectionPlane[5].setScale(Vec3(_boardSize / 2 + 1));
			_mirrorCamera[5].setLookAt(Vec3(0, 5, 0), Vec3(0, 0, 0), Vec3(0, 0, 1));
			/**/
		}

		void setMirror(int w, int h){
			sharedFrameBuffer.CreateFrameBuffer(w, h);
			sharedFrameBuffer.AddDepthBuffer();
			sharedFrameBuffer.Unbind();

			for(int i = 0; i<4;i++){
				shadowBuffer[i].CreateFrameBuffer(w, h);
				shadowBuffer[i].AddDepthBuffer();
				shadowBuffer[i].Unbind();
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////// DRAW CAMERA & MIRRORS 


		void drawMirrorsAndCamera(bool persp, float RotationAngleX, float RotationAngleY, float CameraScale){

			
			Position pos;

			if (onlyonce){
				onlyonce = false;
				drawFinalShadows();
			}

			for(int i = 0; i<4; i++){
				sharedFrameBuffer.Bind();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				_mirrorCamera[i].draw(false, VBOID, 0, 0, 0);
				draw(pos, 0);
				sharedFrameBuffer.Unbind();
				_mainCamera.draw(persp, VBOID, RotationAngleX, RotationAngleY, CameraScale);

				if (useShadows){
					glUseProgram(textureShader2->getProgramId());

					glActiveTexture(GL_TEXTURE0);
					glBindTexture(GL_TEXTURE_2D, shadowBuffer[i].Textureid);
					glUniform1i(GsamplerId21, 0);

					glActiveTexture(GL_TEXTURE1);
					glBindTexture(GL_TEXTURE_2D, sharedFrameBuffer.Textureid);
					glUniform1i(GsamplerId22, 1);

					reflectionPlane[i].draw(textureShader2, UniformId);
				}
				else{
					reflectionPlane[i].draw(textureShader, UniformId);
				}
			}
			
		}



		/////////////////////////////////////////////////////////////////////////////////////// DRAW PIECES

		void draw(Position position, GLuint id){
			/**/
			//draw all other pieces
			Vec3 cameraPos = _mainCamera.cameraPoint();

			//order pieces that from farthest to nearest
			orderPieces();

			if(board.checkWinningCondition() && board.solutionExists)
				std::cerr << "You Win!!" << std::endl;
			
			int i=0;
			for(int j=0; j<_currentNumberPieces;j++){
				i = _orderPieces[j];
				drawPiece(pieces[i], position, id, goochShader, false, cameraPos);
			}

			
			//solutionCubes[0].setScale(Vec3(9));
			//solutionCubes[0].draw(transparentShader,UniformId);
			//line.draw(UniformId, "X_AXIS");
			//line.draw(UniformId, "Y_AXIS");
			//line.draw(UniformId, "Z_AXIS");
			/**/
		}

		//piece as pointer because it doesnt work other way around
		void drawPiece(SomaPiece *piece, Position pos, GLuint id, ShaderProgram * shader, bool useShader, Vec3 cameraPos){

			
			// pointer to a function gives the same values...
			// therefore put the values in a array
			PiecePosition previousPos = piece->getPiecePositions();
			piece->givePosition(pos, id);
			PiecePosition newPos = piece->getPiecePositions();

			if(board.canMove(newPos, piece->getSize(),piece->getStencilId())){
				board.erasePiece(previousPos, piece->getSize());
				board.setPiece(newPos, piece->getSize(),piece->getStencilId());
				piece->setPiecePositions(newPos);
				piece->draw(UniformId, id, shader, useShader, cameraPos);
			}else{
				piece->setPiecePositions(previousPos);
				piece->draw(UniformId, id, shader,useShader, cameraPos);
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////// ORDER PIECES

		void orderPieces(){
			Vec3 cameraPos = _mainCamera.cameraPoint();

			float pieceDistances[MAX_PIECES];

			PiecePosition piecePositions;
			int indiceOfClosest;

			//filling an unsorted array of piece distances to the camera. The piece's cube closest to the camera represents it.
			for(int i=0; i<_currentNumberPieces;i++){
				piecePositions = pieces[i]->getPiecePositions();
				indiceOfClosest = pieces[i]->getClosestToCamera();
				pieceDistances[i] = pieces[i]->distance3D(piecePositions.pos[indiceOfClosest],cameraPos);
			}

			//ordering the distances
			std::vector<float> order(pieceDistances, pieceDistances+_currentNumberPieces);
			std::sort(order.begin(), order.end());

			int j[MAX_PIECES];
			for(int i=0;i<_currentNumberPieces;i++) j[i] = 0;
			int i=0;

			//_order[] will now have the index of which piece to draw first
			for(std::vector<float>::iterator it = order.begin();it!=order.end();it++){
				for(int x=0; x < _currentNumberPieces; x++){
					if(*it == pieceDistances[x] && j[x]==0){
						_orderPieces[i] = x;
						j[x]=1;
						//std::cerr << "piece "<< x << " order=" << i << std::endl;
						i++;
					}
				}
			}

			/** /
			for(std::vector<float>::iterator it = order.begin();it!=order.end();it++){
				 std::cerr << *it << std::endl;
			}
			/**/

			std::reverse(_orderPieces, _orderPieces+_currentNumberPieces);
		}

		/////////////////////////////////////////////////////////////////////////////////////// SAVE & LOAD


		void savePiece(std::string filename){
			rwPiece.bigLPiecePos = bigLPiece.getPiecePositions();
			rwPiece.smallLPiecePos = smallLPiece.getPiecePositions();
			rwPiece.tPiecePos = tPiece.getPiecePositions();
			rwPiece.snakePiecePos = snakePiece.getPiecePositions();
			rwPiece.strangePiece1Pos = strangePiece1.getPiecePositions();
			rwPiece.strangePiece2Pos = strangePiece2.getPiecePositions();
			rwPiece.cornerPiecePos = cornerPiece.getPiecePositions();
			rwPiece.WriteFile(filename);
		}

		void loadPiece(std::string filename){
			bigLPiece.setPiecePositions(rwPiece.bigLPiecePos);
			smallLPiece.setPiecePositions(rwPiece.smallLPiecePos);
			tPiece.setPiecePositions(rwPiece.tPiecePos);
			snakePiece.setPiecePositions(rwPiece.snakePiecePos);
			strangePiece1.setPiecePositions(rwPiece.strangePiece1Pos);
			strangePiece2.setPiecePositions(rwPiece.strangePiece2Pos);
			cornerPiece.setPiecePositions(rwPiece.cornerPiecePos);
			rwPiece.ReadFile(filename);
		}

		void loadSolution(std::string filename){
			ReadWritePiece solution;
			solution.ReadFile(filename);
			bigLPiecePos = solution.bigLPiecePos;
			smallLPiecePos = solution.smallLPiecePos;
			tPiecePos = solution.tPiecePos;
			snakePiecePos = solution.snakePiecePos;
			strangePiece1Pos = solution.strangePiece1Pos;
			strangePiece2Pos = solution.strangePiece2Pos;
			cornerPiecePos = solution.cornerPiecePos;
			onlyonce = true;
		}

	};
}

#endif //MANAGER_H