#ifndef ENTITY_H
#define ENTITY_H

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Shader.h"
#include "Matrix.h"
//#include "OpenGLErrors.h"


namespace engine {
	
#define VERTICES 0
#define COLORS 1

	typedef struct {
		GLfloat XYZW[4];
		GLfloat RGBA[4];
	} Vertex;
	
	class Entity {
			
		private:
			
			const Vertex * verts;
			GLuint UBO_BP;
			GLint size;
			Shader shader;

		public:
			Entity();
			~Entity();
			GLuint VaoId, VboId[2];
			template<size_t N>
			Entity(const Vertex (&Vertices)[N],const GLuint UBO){
				size = N;
				verts = Vertices;
				UBO_BP = UBO;

				createBufferObjects();
			}

			void createBufferObjects();

			//void destroyBufferObjects();
			//void draw(GLuint progShaderId, GLint UniformId, Mat4 m);
			//GLint getVboId(int i);
			

		};

		//typedef ListManager<Entity> ENTITY_LIST;
		//ListManager<Entity>* ListManager<Entity>::_instance = 0;
}

#endif //ENTITY_H