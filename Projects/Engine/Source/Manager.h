#ifndef MANAGER_H
#define MANAGER_H

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Pieces.h"

namespace engine {
	class Manager {
	private:
		Entity BigLPieceE;
		Entity SmallLPieceE;
		Entity TPieceE;
		Entity snakePieceE;
		Entity strangePiece1E;
		Entity strangePiece2E;
		Entity cornerPieceE;
		Entity mirror;

	public:
		Manager(){} 
		~Manager(){}

		void createPieces(GLuint UBO){
			BigLPieceE.createBufferObject(BigLPiece, UBO);
			SmallLPieceE.createBufferObject(SmallLPiece, UBO);
			TPieceE.createBufferObject(TPiece, UBO);
			snakePieceE.createBufferObject(snakePiece, UBO);
			strangePiece1E.createBufferObject(strangePiece1, UBO);
			strangePiece2E.createBufferObject(strangePiece2, UBO);
			cornerPieceE.createBufferObject(cornerPiece, UBO);
			mirror.createBufferObject(Plane, UBO);
		}
		void destroyPieces(){
			BigLPieceE.destroyBufferObject();
			SmallLPieceE.destroyBufferObject();
			TPieceE.destroyBufferObject();
			snakePieceE.destroyBufferObject();
			strangePiece1E.destroyBufferObject();
			strangePiece2E.destroyBufferObject();
			cornerPieceE.destroyBufferObject();
		}
		void drawPieces(){}
		void setCamera(){}
	};
}

#endif //MANAGER_H