#ifndef ENTITY_H
#define ENTITY_H

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"


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
		Mat4 transfM;
		Vec3 translation;
		Quaternion rotation;


	public:
		Entity();
		Entity(Vec3 pos, Quaternion q);
		~Entity();
		GLuint VaoId, VboId[2];

		template<size_t N>
		void createBufferObject(const Vertex (&Vertices)[N],const GLuint UBO){

			size = N;

			UBO_BP = UBO;


			glGenVertexArrays(1, &VaoId);
			glBindVertexArray(VaoId);

			glGenBuffers(2, VboId);

			glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), (Vertices), GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(Vertices[0].XYZW));

			glBindBuffer(GL_UNIFORM_BUFFER, VboId[1]);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4)*2, 0, GL_STREAM_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, VboId[1]);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glDisableVertexAttribArray(VERTICES);
			glDisableVertexAttribArray(COLORS);

			//checkOpenGLError("ERROR: Could not create VAOs and VBOs.");
			//createBufferObject();
		}

		void destroyBufferObject();
		void draw(ShaderProgram* progShader, GLint UniformId);
		GLuint getVboId();
		void addTranslation(Vec3 newTranslation);
		void addRotation(Quaternion newRotation);

	};

	typedef ListManager<Entity> ENTITY_LIST;
	ListManager<Entity>* ListManager<Entity>::_instance = 0;
}

#endif //ENTITY_H