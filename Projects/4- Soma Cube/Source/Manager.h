#ifndef MANAGER_H
#define MANAGER_H

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Pieces.h"

namespace engine {
	class Manager {
	private:
		GLuint VBO_ID;
		
		Quaternion qx;
	public:
		Manager(){
			qx = Quaternion(0.0f, Z_AXIS);
		}
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

			Entity* mirror1 = new Entity();
			cornerPieceE->createBufferObject(Plane, UBO);
			ENTITY_LIST::instance()->add("mirror", cornerPieceE);

			VBO_ID = cornerPieceE->getVboId();
			//NODE_LIST::instance()->add("root", new Node());


		}
		void destroyPieces(){
			std::map<std::string, Entity*> map = ENTITY_LIST::instance()->getList();
			for (std::map<std::string, Entity*>::iterator it = map.begin(); it!=map.end(); ++it)
				(it->second)->destroyBufferObject();
		}
		void drawPieces(ShaderProgram* progShader, GLint UniformId, int selectedPieceX, Vec3 transl, Quaternion q){
			std::map<std::string, Entity*> map = ENTITY_LIST::instance()->getList();
			int i=1;
			for (std::map<std::string, Entity*>::iterator it = map.begin(); it!=map.end(); ++it){
				if(i == selectedPieceX){				
					(it->second)->addTranslation(transl);
					(it->second)->addRotation(q);
				}
				(it->second)->draw(progShader,UniformId);
				i++;
			}
		}
		void setCamera(float RotationAngleX, float RotationAngleY){
			
			//TODO: change these names :'(
			Mat4 projectionMatrix = GetPerspProjection(30,640/480.0f,1,15);
			Mat4 viewMatrixx = GetView(Vec3(0,0,10),Vec3(0,0,0),Vec3(0,1,0));

	
			Quaternion qX = Quaternion(RotationAngleY*.5f, Y_AXIS);
			Quaternion qY = Quaternion(RotationAngleX*.5f, X_AXIS);

			Quaternion qv = qX * qY;

			qx = qv * qx;
			//qx = qMultiply(qZ,qY);
			//aux = rotY * rotZ;

			//qPrint("qx", qx);
			Mat4 m = qx.getMatrix();
			//m.Transpose();
			viewMatrixx =   m * viewMatrixx ;

			//viewMatrixx = GetScale(CameraScale) * viewMatrixx;

			glBindBuffer(GL_UNIFORM_BUFFER, VBO_ID);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(Mat4), viewMatrixx.matrix);
			glBufferSubData(GL_UNIFORM_BUFFER, sizeof(Mat4), sizeof(Mat4), projectionMatrix.matrix);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	};
}

#endif //MANAGER_H