#include "Mirror.h"


Mirror::Mirror()
{
}

void Mirror::CreateFrameBuffer(int w, int h) {


  glGenFramebuffers(1, &FBOid);
  glBindFramebuffer(GL_FRAMEBUFFER, FBOid);
  width = w;
  height = h;
}

void Mirror::CreateTexture(int w, int h) {  //creates an empty texture
  glGenTextures(1, &Textureid);
  glBindTexture(GL_TEXTURE_2D, Textureid);


  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  float pixels[] = {
	  0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
	  1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f
  };
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_FLOAT, 0);

  //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Textureid, 0);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Textureid, 0);

 


 /* glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glGenSamplers(1, &SamplerId);
  glGenerateMipmap(GL_TEXTURE_2D);*/

}

void Mirror::AddDepthBuffer(){
  glBindFramebuffer(GL_FRAMEBUFFER, FBOid);
  glGenRenderbuffers(1, &DRBid);
  glBindRenderbuffer(GL_RENDERBUFFER, DRBid);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DRBid);
  
}
void Mirror::Bind(){
  glBindRenderbuffer(GL_RENDERBUFFER, DRBid);
  glBindFramebuffer(GL_FRAMEBUFFER, FBOid);
  glActiveTexture(GL_TEXTURE0 ); 
  glBindTexture(GL_TEXTURE_2D, Textureid);

  glUniform1i(gsamplerId, 0);

}
void Mirror::Unbind(){
  glBindFramebuffer(GL_FRAMEBUFFER, NULL);
  glBindSampler(0, NULL);


}



Mirror::~Mirror()
{
}