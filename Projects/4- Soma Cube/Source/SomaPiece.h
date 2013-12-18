#ifndef SOMAPIECE_H
#define SOMAPIECE_H

#include "Mesh.h"

namespace engine {

	class SomaPiece {
	protected:
		Vec3 _boardPos[4];			// Cubes positions in board
		int _size;					// 3 cubes or 4 cubes of piece
		unsigned int _stencilId;	// id group for selection by stencil buffer
		std::string _name;			// name of piece
		Entity _cubeE[4];			// Array of 4 entities of selecting cubes
		Entity _cubeD[4];			// Array of 4 entities of drawable cubes
		Vec3 _posCube[4];			// Position of each cubes of piece
		Vec3 _initPosCube[4];		// Default positions of cubes of the pieces
		Position _pos;				// Position of piece
		Position _posIdentifier;	// Position of piece selected
		Entity _pieceEntity;		// Entity for piece ????
		Position _posPiece;			// do not know?????
		Vec3 _initPosition;			// intial position of piece
		Mesh _pieceMesh;			// Mesh of piece
		Mesh _cubeMesh;				// Mesh of individual cube
		GLuint VBOID;

	
		Mat4 cubeMat[4];

	public:
		SomaPiece(std::string name) { _name = name; }
		~SomaPiece(){}

		void createBufferObject(const GLuint UBO){
			//_pieceEntity = _pieceMesh.getMeshEntity(UBO);
			//_pieceEntity.setScale(Vec3(0.4f));
			Cube cube = Cube(1,Vec3(1),Vec3(1),Vec3(1),Vec3(1),Vec3(1),Vec3(1));

			_cubeD[0] = _cubeMesh.getMeshEntity(UBO);
			_cubeD[1] = _cubeMesh.getMeshEntity(UBO);
			_cubeD[2] = _cubeMesh.getMeshEntity(UBO);

			if(_size > 3)
				_cubeD[3] = _cubeMesh.getMeshEntity(UBO);


			// create 4 minicubes that draws different positions
			_cubeE[0].createBufferObject(cube.Vertices, cube.size(), UBO);
			_cubeE[1].createBufferObject(cube.Vertices, cube.size(), UBO);
			_cubeE[2].createBufferObject(cube.Vertices, cube.size(), UBO);


			if(_size > 3)
				_cubeE[3].createBufferObject(cube.Vertices, cube.size(), UBO);

			_cubeE[0].setScale(Vec3(1));
			_cubeE[1].setScale(Vec3(1));
			_cubeE[2].setScale(Vec3(1));

			if(_size > 3)
				_cubeE[3].setScale(Vec3(1));

			_posCube[0] = _initPosition +_posCube[0];
			_posCube[1] = _initPosition +_posCube[1];
			_posCube[2] = _initPosition +_posCube[2];

			if(_size > 3)
				_posCube[3] = _initPosition +_posCube[3];

			if(_size > 3)
				VBOID = _cubeE[3].getVboId();
			else
				VBOID = _cubeE[2].getVboId();
		}

		void destroyBufferObject(){
			//_pieceEntity.destroyBufferObject();
			_cubeE[0].destroyBufferObject();
			_cubeE[1].destroyBufferObject();
			_cubeE[2].destroyBufferObject();
			if(_size > 3)
				_cubeE[3].destroyBufferObject();

			_cubeD[0].destroyBufferObject();
			_cubeD[1].destroyBufferObject();
			_cubeD[2].destroyBufferObject();
			if(_size > 3)
				_cubeD[3].destroyBufferObject();
		}

		void givePosition(Position pos, int identifier){ 
			_pos = pos; 
			
			if(identifier == (int)(10 * _stencilId + 0)){
				if(_pos.translation != Vec3(0)){ // case translation position is added to cubes position
					_posCube[0] += _pos.translation;
					_posCube[1] += _pos.translation;
					_posCube[2] += _pos.translation;
					_posCube[3] += _pos.translation;
				}else{							// else rotation, the position is calculated to each cubes position
					_posCube[0] = _posCube[0];
					_posCube[1] = _posCube[0] + getPositionRotation(_posCube[1] - _posCube[0], _pos.rotation);
					_posCube[2] = _posCube[0] + getPositionRotation(_posCube[2] - _posCube[0], _pos.rotation);
					_posCube[3] = _posCube[0] + getPositionRotation(_posCube[3] - _posCube[0], _pos.rotation);
				}
			}
			if(identifier == (int)(10 * _stencilId + 1)){
				if(_pos.translation != Vec3(0)){
					_posCube[0] += _pos.translation;
					_posCube[1] += _pos.translation;
					_posCube[2] += _pos.translation;
					_posCube[3] += _pos.translation;
				}else{
					_posCube[0] = _posCube[1] + getPositionRotation(_posCube[0] - _posCube[1], _pos.rotation);
					_posCube[1] = _posCube[1];
					_posCube[2] = _posCube[1] + getPositionRotation(_posCube[2] - _posCube[1], _pos.rotation);
					_posCube[3] = _posCube[1] + getPositionRotation(_posCube[3] - _posCube[1], _pos.rotation);
				}
			}
			if(identifier == (int)(10 * _stencilId + 2)){
				if(_pos.translation != Vec3(0)){
					_posCube[0] += _pos.translation;
					_posCube[1] += _pos.translation;
					_posCube[2] += _pos.translation;
					_posCube[3] += _pos.translation;
				}else{
					
					_posCube[0] = _posCube[2] + getPositionRotation(_posCube[0] - _posCube[2], _pos.rotation);
					_posCube[1] = _posCube[2] + getPositionRotation(_posCube[1] - _posCube[2], _pos.rotation);
					_posCube[2] = _posCube[2];
					_posCube[3] = _posCube[2] + getPositionRotation(_posCube[3] - _posCube[2], _pos.rotation);
				}
			}
			if(_size > 3){
				if(identifier == (int)(10 * _stencilId + 3)){
					if(_pos.translation != Vec3(0)){
						_posCube[0] += _pos.translation;
						_posCube[1] += _pos.translation;
						_posCube[2] += _pos.translation;
						_posCube[3] += _pos.translation;
					}else{
						_posCube[0] = _posCube[3] + getPositionRotation(_posCube[0] - _posCube[3], _pos.rotation);
						_posCube[1] = _posCube[3] + getPositionRotation(_posCube[1] - _posCube[3], _pos.rotation);
						_posCube[2] = _posCube[3] + getPositionRotation(_posCube[2] - _posCube[3], _pos.rotation);
						_posCube[3] = _posCube[3];
					}
				}
			}

			//std::cerr << _posCube[0].x << std::endl;
		}

		unsigned int getStencilId(){ return _stencilId; }

		Vec3 getPositionRotation(Vec3 vi, Quaternion r){
			Quaternion q = Quaternion(0,vi.x,vi.y,vi.z);
			Vec3 newPos;
			Quaternion f;
			if(r.t != 0)
				f = (r * q) * r.Inverse();
			else
				return vi;
			newPos.x = f.x; newPos.y = f.y; newPos.z = f.z;
			return newPos;
		}

		void draw(GLint UniformId, int identifier){
			ShaderProgram* normal = SHADER_PROGRAM_LIST::instance()->get("normal");
			ShaderProgram* black = SHADER_PROGRAM_LIST::instance()->get("black");
			ShaderProgram* white = SHADER_PROGRAM_LIST::instance()->get("white");

			//_pieceEntity.addRotation(_pos.rotation);
			//_pieceEntity.addTranslation(_pos.translation);
			//_pieceEntity.draw(normal, UniformId);
			glDisable(GL_DEPTH_TEST);
			for (int i = 0; i<_size; i++){
				_cubeD[i].setScale(Vec3(1.05f));

				_cubeD[i].setStencilId(10 * _stencilId + i);
				_cubeD[i].setTranslation(_posCube[i]);
				
				_cubeD[i].draw(black, UniformId);
				_cubeD[i].setScale(Vec3(1.0f));
			}
			glEnable(GL_DEPTH_TEST);

			for(int i=0; i<_size;i++){
				_cubeE[i].setStencilId(10*_stencilId +i);
				_cubeE[i].setTranslation(_posCube[i]);

				_cubeD[i].setStencilId(10*_stencilId +i);
				_cubeD[i].setTranslation(_posCube[i]);

				if(identifier ==(int)(10*_stencilId + i)){
					_cubeE[i].drawLine(white, UniformId);
					_cubeD[i].draw(normal, UniformId);
				}else{
					_cubeD[i].draw(normal, UniformId);
				}	
			}

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion();

		}

		GLuint getVboId(){ return VBOID; }

		Position getPositionIdentifier(){ return _posIdentifier; }

		void setInitPosition(Vec3 posInit){ _initPosition = posInit; }

		Vec3* getPiecePositions(){ 
			Vec3 ppp[4];
			ppp[0] = _posCube[0];
			ppp[1] = _posCube[1];
			ppp[2] = _posCube[2];
			ppp[3] = _posCube[3];
			return _posCube; }

		void setPiecePositions(Vec3 positions[4]){ 
			for(int i=0; i<_size;i++)
				_posCube[i] = positions[i]; 
		}

		int getSize(){ return _size; }
	};

	class Line {
	private:
		Entity _lineX, _lineY, _lineZ;		// Entities for lines on X, Y, Z axis
		Position _pos;						// Position of line
		GLuint VBOID;
	public:
		Line(){}
		~Line(){}
		void createBufferObject(const GLuint UBO){
			const Vertex lineVertsX[] = {
										{{ 5.0f, 0.0f, 0.0f, 1.0f},{ 1.0f, 1.0f, 1.0f, 1.0f}},
										{{-5.0f, 0.0f, 0.0f, 1.0f},{ 1.0f, 1.0f, 1.0f, 1.0f}}
										};
			const Vertex lineVertsY[] = {
										{{ 0.0f, 5.0f, 0.0f, 1.0f},{ 1.0f, 1.0f, 1.0f, 1.0f}},
										{{ 0.0f,-5.0f, 0.0f, 1.0f},{ 1.0f, 1.0f, 1.0f, 1.0f}},
										};
			const Vertex lineVertsZ[] = {
										{{ 0.0f, 0.0f, 5.0f, 1.0f},{ 1.0f, 1.0f, 1.0f, 1.0f}},
										{{ 0.0f, 0.0f,-5.0f, 1.0f},{ 1.0f, 1.0f, 1.0f, 1.0f}},
										};
			_lineX.createBufferObject(lineVertsX, 2, UBO);
			_lineY.createBufferObject(lineVertsY, 2, UBO);
			_lineZ.createBufferObject(lineVertsZ, 2, UBO);
			VBOID = _lineZ.getVboId();
		}
		void destroyBufferObject(){
			_lineX.destroyBufferObject();
			_lineY.destroyBufferObject();
			_lineZ.destroyBufferObject();
		}

		void draw(GLint UniformId, std::string axis){
			ShaderProgram* white = SHADER_PROGRAM_LIST::instance()->get("white");

			if(axis == "X_AXIS"){
				_lineX.setPosition(_pos);
				_lineX.drawLine(white, UniformId);
			}else if(axis == "Y_AXIS"){
				_lineY.setPosition(_pos);
				_lineY.drawLine(white, UniformId);
			}else if(axis == "Z_AXIS"){
				_lineZ.setPosition(_pos);
				_lineZ.drawLine(white, UniformId);
			}
		}

		void setPosition(Position pos){
			_pos = pos;
		}

		GLuint getVboId(){
			return VBOID;
		}

	};

	class BigLPiece : public SomaPiece {
	public:

		BigLPiece() : SomaPiece("BigLPiece"){
			_pieceMesh = Mesh("models/BigLPiece.obj");
			_cubeMesh = Mesh("models/bevelCube.obj");
			_size = 4;
			_stencilId = 1;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(-4,0,0);



			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(0,0,1);
			_posCube[2] = Vec3(0,0,2);
			_posCube[3] = Vec3(1,0,0);
			
		}
	};

	class SmallLPiece : public SomaPiece {
	public:

		SmallLPiece() : SomaPiece("SmallLPiece"){
			_pieceMesh = Mesh("models/BigLPiece.obj");
			_cubeMesh = Mesh("models/bevelCube.obj");
			_size = 3;
			_stencilId = 2;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(4,0,0);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(0,0,-1);
			_posCube[2] = Vec3(-1,0,0);

		}
	};

	class TPiece : public SomaPiece {
	public:

		TPiece() : SomaPiece("TPiece"){
			_pieceMesh = Mesh("models/BigLPiece.obj");
			_cubeMesh = Mesh("models/bevelCube.obj");
			_size = 4;
			_stencilId = 3;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(4,0,0);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(0,0,-1);
			_posCube[2] = Vec3(1,0,0);
			_posCube[3] = Vec3(-1,0,0);

		}
	};

	class SnakePiece : public SomaPiece {
	public:

		SnakePiece() : SomaPiece("SnakePiece"){
			_pieceMesh = Mesh("models/BigLPiece.obj");
			_cubeMesh = Mesh("models/bevelCube.obj");
			_size = 4;
			_stencilId = 4;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(4,0,0);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(-1,0,0);
			_posCube[2] = Vec3(0,0,-1);
			_posCube[3] = Vec3(1,0,-1);

		}
	};

	class StrangePiece1 : public SomaPiece {
	public:

		StrangePiece1() : SomaPiece("StrangePiece1"){
			_pieceMesh = Mesh("models/BigLPiece.obj");
			_cubeMesh = Mesh("models/bevelCube.obj");
			_size = 4;
			_stencilId = 5;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(4,0,0);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(-1,0,0);
			_posCube[2] = Vec3(0,0,-1);
			_posCube[3] = Vec3(0,1,-1);

		}
	};

	class StrangePiece2 : public SomaPiece {
	public:

		StrangePiece2() : SomaPiece("StrangePiece2"){
			_pieceMesh = Mesh("models/BigLPiece.obj");
			_cubeMesh = Mesh("models/bevelCube.obj");
			_size = 4;
			_stencilId = 6;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(4,0,0);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(1,0,0);
			_posCube[2] = Vec3(0,0,-1);
			_posCube[3] = Vec3(0,1,-1);

		}
	};

	class CornerPiece : public SomaPiece {
	public:

		CornerPiece() : SomaPiece("CornerPiece"){
			_pieceMesh = Mesh("models/BigLPiece.obj");
			_cubeMesh = Mesh("models/bevelCube.obj");
			_size = 4;
			_stencilId = 7;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(4,0,0);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(1,0,0);
			_posCube[2] = Vec3(0,1,0);
			_posCube[3] = Vec3(0,0,1);

		}
	};
}

#endif //SOMAPIECE_H