#pragma once
#include "Entity.h"

using namespace engine;

class Mirror
{
public:
	Entity mirror;
	Mirror();
	void createEntity(GLuint UBO);

	~Mirror();
};

