#include "Mirror.h"

Mirror::Mirror()
{
}

void Mirror::createEntity(GLuint UBO){
	Vertex Plane[] =
	{
		{ { -2.0f, -3.5f, 0.0f, 1.0f }, { 1.0f, 0.0f, 1.0f, 1.0f } }, // 0 - FRONT 
		{ { -2.0f, -3.5f, 3.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f } }, // 1
		{ { 2.0f, -3.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }, // 2
		{ { 2.0f, -3.5f, 0.0f, 1.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }, // 2	
		{ { 2.0f, -3.5f, 3.0f, 1.0f }, { 0.0f, 1.0f, 1.0f, 1.0f } }, // 3
		{ { -2.0f, -3.5f, 0.0f, 1.0f }, { 1.0f, 0.0f, 1.0f, 1.0f } }, // 0
	};	
	mirror.createBufferObject(Plane, UBO);

}

Mirror::~Mirror()
{

}
