#pragma once

#include "GL/glew.h"
#include "GL/freeglut.h"

enum ETextureFiltering
{
	TEXTURE_FILTER_MAG_NEAREST = 0, // Nearest criterion for magnification
	TEXTURE_FILTER_MAG_BILINEAR, // Bilinear criterion for magnification
	TEXTURE_FILTER_MIN_NEAREST, // Nearest criterion for minification
	TEXTURE_FILTER_MIN_BILINEAR, // Bilinear criterion for minification
	TEXTURE_FILTER_MIN_NEAREST_MIPMAP, // Nearest criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_BILINEAR_MIPMAP, // Bilinear criterion for minification, but on closest mipmap
	TEXTURE_FILTER_MIN_TRILINEAR, // Bilinear criterion for minification on two closest mipmaps, then averaged
};

class Mirror
{
public:
	int tfMinification, tfMagnification;
	int width, height;
	GLuint FBOid, DRBid, Textureid, SamplerId;
	GLint gsamplerId;
	Mirror();
	void CreateFrameBuffer(int w, int h);
	void CreateTexture(int w, int h);
	void AddDepthBuffer();
	void Bind();
	void Unbind();
	bool isOpenGLError();
	void checkOpenGLError();
	~Mirror();
};

