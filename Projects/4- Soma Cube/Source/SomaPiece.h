#ifndef SOMAPIECE_H
#define SOMAPIECE_H

#include "Mesh.h"

namespace engine {

	struct PiecePosition {
		Vec3 pos[4];
	};

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
		int _order[4];				// order that the cubes are drawn
		GLuint VBOID;

	
		Mat4 cubeMat[4];

	public:
		SomaPiece(std::string name) { _name = name; }
		~SomaPiece(){}

		void createBufferObject(const GLuint UBO){
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

		float distance3D(Vec3 p1, Vec3 p2){
			float dist;
			dist = sqrt(((p1.x - p2.x)*(p1.x - p2.x)) + ((p1.y - p2.y)*(p1.y - p2.y)) + ((p1.z - p2.z)*(p1.z - p2.z)));
			return dist;
		}

		int getClosestToCamera(){
			return  _order[0];
		}

		void sortPieces(Vec3 camPos){
			float piece0=0, piece1=0, piece2=0, piece3=0;


			piece0 = distance3D(camPos,_posCube[0]);
			piece1 = distance3D(camPos,_posCube[1]);
			piece2 = distance3D(camPos,_posCube[2]);
			if(_size > 3){
				piece3 = distance3D(camPos,_posCube[3]);
			}

			float indices[] = {piece0, piece1, piece2, piece3};

			std::vector<float> order(indices, indices+_size);
			std::sort(order.begin(),order.end());

			int i=0;
			int j[4] = {0,0,0,0};

			for(std::vector<float>::iterator it = order.begin();it!=order.end();it++){
				if(*it == piece0 && j[0]==0){
					_order[i] = 0;
					j[0]=1;
				}
				if(*it == piece1 && j[1]==0){
					_order[i] = 1;
					j[1]=1;
				}
				if(*it == piece2 && j[2]==0){
					_order[i] = 2;
					j[2]=1;
				}
				if(*it == piece3 && j[3]==0 && _size>3){
					_order[i] = 3;
					j[3]=1;
				}
				i++;
			}
			//std::reverse(_order, _order+_size);
			//std::cerr << " " << _order[0] <<" " << _order[1] <<" " << _order[2] << " " << _order[3] << std::endl;
		}


		virtual ShaderProgram* setColor(Vec3 cameraPos){
			ShaderProgram* normal = SHADER_PROGRAM_LIST::instance()->get("normal");
			return normal;
		}

		void draw(GLint UniformId, int identifier, ShaderProgram *shader, bool useShader, Vec3 cameraPos){
			ShaderProgram* normal = SHADER_PROGRAM_LIST::instance()->get("normal");
			ShaderProgram* black = SHADER_PROGRAM_LIST::instance()->get("black");
			ShaderProgram* white = SHADER_PROGRAM_LIST::instance()->get("white");

			sortPieces(cameraPos);
		
			int i;
			/** /
			
			glDisable(GL_BLEND);
			glDisable(GL_DEPTH_TEST);
			for (int j = 0; j<_size; j++){
				i = _order[j];
				_cubeD[i].setScale(Vec3(1.05f));

				_cubeD[i].setStencilId(10 * _stencilId + i);
				_cubeD[i].setTranslation(_posCube[i]);
				
				_cubeD[i].draw(black, UniformId);
				_cubeD[i].setScale(Vec3(1.0f));
			}
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			
			/**/
			ShaderProgram* colorShader = setColor(cameraPos);
			if(useShader)
				colorShader = shader;
			
			for(int j=0; j<_size;j++){
				i = _order[j];

				_cubeE[i].setStencilId(10*_stencilId +i);
				_cubeE[i].setTranslation(_posCube[i]);

				_cubeD[i].setStencilId(10*_stencilId +i);
				_cubeD[i].setTranslation(_posCube[i]);

				if(identifier ==(int)(10*_stencilId + i)){
					_cubeE[i].drawLine(white, UniformId);
					_cubeD[i].draw(colorShader, UniformId);
				}else{
					_cubeD[i].draw(colorShader, UniformId);
				}
			}

			

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion();

		}

		GLuint getVboId(){ return VBOID; }

		Position getPositionIdentifier(){ return _posIdentifier; }

		void setInitPosition(Vec3 posInit){ _initPosition = posInit; }

		PiecePosition getPiecePositions(){ 
			PiecePosition result;
			result.pos[0] = _posCube[0];
			result.pos[1] = _posCube[1];
			result.pos[2] = _posCube[2];
			result.pos[3] = _posCube[3];
			return result; }

		void setPiecePositions(PiecePosition position){ 
			for(int i=0; i<_size;i++)
				_posCube[i] = position.pos[i]; 
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
			
			_cubeMesh = Mesh("models/roundedCube.obj");
			_size = 4;
			_stencilId = 1;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(0,0,0);

			_initPosCube[0] = Vec3(0,0,0);
			_initPosCube[1] = Vec3(0,0,1);
			_initPosCube[2] = Vec3(0,0,2);
			_initPosCube[3] = Vec3(1,0,0);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(0,0,1);
			_posCube[2] = Vec3(0,0,2);
			_posCube[3] = Vec3(1,0,0);
			
		}

		ShaderProgram* setColor(Vec3 cameraPos){
			ShaderProgram* goochShader = SHADER_PROGRAM_LIST::instance()->get("gooch");
			goochShader->setParameter("warmColor", Vec3(1.0, 0.0, 0.0));
			goochShader->setParameter("cameraPos", cameraPos);
			return goochShader;
		}
	};

	class SmallLPiece : public SomaPiece {
	public:

		SmallLPiece() : SomaPiece("SmallLPiece"){
		
			_cubeMesh = Mesh("models/roundedCube.obj");
			_size = 3;
			_stencilId = 2;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(0,0,0);

			_initPosCube[0] = Vec3(0,0,0);
			_initPosCube[1] = Vec3(0,0,-1);
			_initPosCube[2] = Vec3(-1,0,0);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(0,0,-1);
			_posCube[2] = Vec3(-1,0,0);

		}

		ShaderProgram* setColor(Vec3 cameraPos){
			ShaderProgram* goochShader = SHADER_PROGRAM_LIST::instance()->get("gooch");
			goochShader->setParameter("warmColor", Vec3(0.0, 1.0, 0.0));
			goochShader->setParameter("cameraPos", cameraPos);
			return goochShader;
		}
	};

	class TPiece : public SomaPiece {
	public:

		TPiece() : SomaPiece("TPiece"){
		
			_cubeMesh = Mesh("models/roundedCube.obj");
			_size = 4;
			_stencilId = 3;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(0,0,0);

			_initPosCube[0] = Vec3(0,0,0);
			_initPosCube[1] = Vec3(0,0,-1);
			_initPosCube[2] = Vec3(1,0,0);
			_initPosCube[3] = Vec3(-1,0,0);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(0,0,-1);
			_posCube[2] = Vec3(1,0,0);
			_posCube[3] = Vec3(-1,0,0);

		}

		ShaderProgram* setColor(Vec3 cameraPos){
			ShaderProgram* goochShader = SHADER_PROGRAM_LIST::instance()->get("gooch");
			goochShader->setParameter("warmColor", Vec3(0.0, 0.0, 1.0));
			goochShader->setParameter("cameraPos", cameraPos);
			return goochShader;
		}
	};

	class SnakePiece : public SomaPiece {
	public:

		SnakePiece() : SomaPiece("SnakePiece"){
			
			_cubeMesh = Mesh("models/roundedCube.obj");
			_size = 4;
			_stencilId = 4;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(0,0,0);

			_initPosCube[0] = Vec3(0,0,0);
			_initPosCube[1] = Vec3(-1,0,0);
			_initPosCube[2] = Vec3(0,0,-1);
			_initPosCube[3] = Vec3(1,0,-1);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(-1,0,0);
			_posCube[2] = Vec3(0,0,-1);
			_posCube[3] = Vec3(1,0,-1);

		}

		ShaderProgram* setColor(Vec3 cameraPos){
			ShaderProgram* goochShader = SHADER_PROGRAM_LIST::instance()->get("gooch");
			goochShader->setParameter("warmColor", Vec3(1.0, 1.0, 0.0));
			goochShader->setParameter("cameraPos", cameraPos);
			return goochShader;
		}
	};

	class StrangePiece1 : public SomaPiece {
	public:

		StrangePiece1() : SomaPiece("StrangePiece1"){
		
			_cubeMesh = Mesh("models/roundedCube.obj");
			_size = 4;
			_stencilId = 5;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(0,0,0);

			
			_initPosCube[0] = Vec3(0,0,0);
			_initPosCube[1] = Vec3(-1,0,0);
			_initPosCube[2] = Vec3(0,0,-1);
			_initPosCube[3] = Vec3(1,0,-1);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(-1,0,0);
			_posCube[2] = Vec3(0,0,-1);
			_posCube[3] = Vec3(0,1,-1);

		}

		ShaderProgram* setColor(Vec3 cameraPos){
			ShaderProgram* goochShader = SHADER_PROGRAM_LIST::instance()->get("gooch");
			goochShader->setParameter("warmColor", Vec3(0.0, 1.0, 1.0));
			goochShader->setParameter("cameraPos", cameraPos);
			return goochShader;
		}
	};

	class StrangePiece2 : public SomaPiece {
	public:

		StrangePiece2() : SomaPiece("StrangePiece2"){
			
			_cubeMesh = Mesh("models/roundedCube.obj");
			_size = 4;
			_stencilId = 6;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(0,0,0);

			_initPosCube[0] = Vec3(0,0,0);
			_initPosCube[1] = Vec3(-1,0,0);
			_initPosCube[2] = Vec3(0,0,-1);
			_initPosCube[3] = Vec3(0,1,-1);


			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(1,0,0);
			_posCube[2] = Vec3(0,0,-1);
			_posCube[3] = Vec3(0,1,-1);

		}

		ShaderProgram* setColor(Vec3 cameraPos){
			ShaderProgram* goochShader = SHADER_PROGRAM_LIST::instance()->get("gooch");
			goochShader->setParameter("warmColor", Vec3(1.0, 0.0, 1.0));
			goochShader->setParameter("cameraPos", cameraPos);
			return goochShader;
		}
	};

	class CornerPiece : public SomaPiece {
	public:

		CornerPiece() : SomaPiece("CornerPiece"){
		
			_cubeMesh = Mesh("models/roundedCube.obj");
			_size = 4;
			_stencilId = 7;

			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion(0,1,0,0);

			_initPosition = Vec3(0,0,0);

			_initPosCube[0] = Vec3(0,0,0);
			_initPosCube[1] = Vec3(1,0,0);
			_initPosCube[2] = Vec3(0,1,0);
			_initPosCube[3] = Vec3(0,0,1);

			_posCube[0] = Vec3(0,0,0);
			_posCube[1] = Vec3(1,0,0);
			_posCube[2] = Vec3(0,1,0);
			_posCube[3] = Vec3(0,0,1);

		}
		
		ShaderProgram* setColor(Vec3 cameraPos){
			ShaderProgram* goochShader = SHADER_PROGRAM_LIST::instance()->get("gooch");
			goochShader->setParameter("warmColor", Vec3(0.5, 0.5, 0.0));
			goochShader->setParameter("cameraPos", cameraPos);
			return goochShader;
		}

	};
}

#endif //SOMAPIECE_H