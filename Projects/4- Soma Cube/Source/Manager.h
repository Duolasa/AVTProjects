#ifndef MANAGER_H
#define MANAGER_H

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Pieces.h"

namespace engine {
	class Manager {
	private:
		

	public:
		Manager(){}
		~Manager(){}

		void createPieces(GLuint UBO){
			Entity* BigLPieceE = new Entity();
			BigLPieceE->createBufferObject(BigLPiece, UBO);
			ENTITY_LIST::instance()->add("BigLPiece", BigLPieceE);

			Entity* SmallLPieceE = new Entity();
			SmallLPieceE->createBufferObject(SmallLPiece, UBO);
			ENTITY_LIST::instance()->add("SmallLPiece", SmallLPieceE);

			Entity* TPieceE = new Entity();
			TPieceE->createBufferObject(TPiece, UBO);
			ENTITY_LIST::instance()->add("TPiece", TPieceE);

			Entity* snakePieceE = new Entity();
			snakePieceE->createBufferObject(snakePiece, UBO);
			ENTITY_LIST::instance()->add("snakePiece", snakePieceE);

			Entity* strangePiece1E = new Entity();
			strangePiece1E->createBufferObject(strangePiece1, UBO);
			ENTITY_LIST::instance()->add("strangePiece1", strangePiece1E);

			Entity* strangePiece2E = new Entity();
			strangePiece2E->createBufferObject(strangePiece2, UBO);
			ENTITY_LIST::instance()->add("strangePiece2", strangePiece2E);

			Entity* cornerPieceE = new Entity();
			cornerPieceE->createBufferObject(cornerPiece, UBO);
			ENTITY_LIST::instance()->add("cornerPiece", cornerPieceE);

			//NODE_LIST::instance()->add("root", new Node());


		}
		void destroyPieces(){
			std::map<std::string, Entity*> map = ENTITY_LIST::instance()->getList();
			for (std::map<std::string, Entity*>::iterator it = map.begin(); it!=map.end(); ++it)
				(it->second)->destroyBufferObject();
		}
		void drawPieces(ShaderProgram* progShader, GLint UniformId){
			std::map<std::string, Entity*> map = ENTITY_LIST::instance()->getList();
			for (std::map<std::string, Entity*>::iterator it = map.begin(); it!=map.end(); ++it)
				(it->second)->draw(progShader,UniformId, GetIdentity().matrix);
		}
		void setCamera(){}
	};
}

#endif //MANAGER_H