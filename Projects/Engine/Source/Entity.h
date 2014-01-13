#ifndef ENTITY_H
#define ENTITY_H

#include "GL/glew.h"
#include "GL/freeglut.h"

#include "Shader.h"
#include "Matrix.h"
#include "Vector.h"
#include "Quaternion.h"

#define VERTICES 0
#define COLORS 1
#define NORMALS 2
#define TEXTURE_COORDS 3

namespace engine {

	struct Position {
		Vec3 translation;
		Quaternion rotation;
	};

	typedef struct {
		GLfloat XYZW[4];
		GLfloat RGBA[4];
		GLfloat NXYZW[4];
		GLfloat UV[2];
	} Vertex;

	class Entity {

	private:

		const Vertex * verts;
		GLuint UBO_BP;
		GLint _size;
		Position _pos;
		Vec3 _scale;				// scale of entity       
		Vec3 _toCenter;				// center of entity to rotate from
		GLuint VaoId, VboId[2];
		GLint _stencilId;

		Mat4 _positionMatrix;

		Mat4 getPositionMatrix(){
			// because is transpose the order is inverse M = R * T instead of M = T * R
			Mat4 mat =  (GetScale(_scale) *_pos.rotation.getMatrix())* GetTranslation(_pos.translation);
			return mat;
		}

	public:

		Entity(){
			_scale = Vec3(1);
			_toCenter = Vec3(0);
			_pos.translation = Vec3(0);
			_pos.rotation = Quaternion();

			_positionMatrix = GetIdentity();
		}
		~Entity(){}
		

		
		void createBufferObject(const Vertex *Vertices, GLint N, const GLuint UBO){
			_size = N;

			UBO_BP = UBO;


			glGenVertexArrays(1, &VaoId);
			glBindVertexArray(VaoId);

			glGenBuffers(2, VboId);

			glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*N, (Vertices), GL_STATIC_DRAW);
			glEnableVertexAttribArray(VERTICES);
			glVertexAttribPointer(VERTICES, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
			glEnableVertexAttribArray(COLORS);
			glVertexAttribPointer(COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)sizeof(Vertices[0].XYZW));
			glEnableVertexAttribArray(NORMALS);
			glVertexAttribPointer(NORMALS, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(Vertices[0].XYZW) + sizeof(Vertices[0].RGBA)));
			glEnableVertexAttribArray(TEXTURE_COORDS);
			glVertexAttribPointer(TEXTURE_COORDS, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)(sizeof(Vertices[0].XYZW) + sizeof(Vertices[0].RGBA) + sizeof(Vertices[0].NXYZW)));


			glBindBuffer(GL_UNIFORM_BUFFER, VboId[1]);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(Mat4)*2, 0, GL_STREAM_DRAW);
			glBindBufferBase(GL_UNIFORM_BUFFER, UBO_BP, VboId[1]);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
			glDisableVertexAttribArray(VERTICES);
			glDisableVertexAttribArray(COLORS);
			glDisableVertexAttribArray(NORMALS);
			glDisableVertexAttribArray(TEXTURE_COORDS);

		}

		void destroyBufferObject(){

			glDisableVertexAttribArray(VERTICES);
			glDisableVertexAttribArray(COLORS);
			glDisableVertexAttribArray(NORMALS);
			glDisableVertexAttribArray(TEXTURE_COORDS);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			glDeleteBuffers(2, VboId);
			glDeleteVertexArrays(1, &VaoId);
		}

		void setStencilId(GLint id){
			_stencilId = id;
		}

		void draw(ShaderProgram* progShader, GLint UniformId){
			glStencilFunc(GL_ALWAYS, _stencilId, -1);
			glBindVertexArray(VaoId);
			glUseProgram(progShader->getProgramId());

			glUniformMatrix4fv(UniformId, 1, GL_FALSE, getPositionMatrix().matrix);	
			glDrawArrays(GL_TRIANGLES, 0, _size);
			
			glUseProgram(0);
			glBindVertexArray(0);
		}

		void drawLine(ShaderProgram* progShader, GLint UniformId){

			glBindVertexArray(VaoId);
			glUseProgram(progShader->getProgramId());

			glUniformMatrix4fv(UniformId, 1, GL_FALSE, /**/ getPositionMatrix().matrix);	
			glDrawArrays(GL_LINE_STRIP, 0, _size);
			
			glUseProgram(0);
			glBindVertexArray(0);
		}

		GLuint getVboId(){
			return VboId[1];
		}

		void setPosition(Position pos){
			_pos = pos;
		}

		void addPosition(Position pos){
			_pos.translation += pos.translation;
			_pos.rotation = pos.rotation * _pos.rotation;
		}

		void addTranslation(Vec3 pos){
			_pos.translation += pos;
		}

		void addRotation(Quaternion rot){
			_pos.rotation = rot * _pos.rotation;
		}

		void setRotation(Quaternion rot){
			_pos.rotation = rot;
		}

		void setScale(Vec3 scale){
			_scale = scale;
		}

		void setCenter(Vec3 center){
			_toCenter = center;
		}

		void setTranslation(Vec3 translate){
			_pos.translation = translate;
		}

		void moveToCenter(){
			_pos.translation = _toCenter;
		}

	};

	typedef ListManager<Entity> ENTITY_LIST;
	ListManager<Entity>* ListManager<Entity>::_instance = 0;
}

#endif //ENTITY_H