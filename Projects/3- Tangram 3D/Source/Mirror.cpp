#include "Mirror.h"


Mirror::Mirror()
{
}

void Mirror::CreateFrameBuffer(int w, int h) {


  glGenFramebuffers(1, &FBOid);
  glBindFramebuffer(GL_FRAMEBUFFER, FBOid);

  CreateTexture(w, h);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Textureid, 0);

  width = w;
  height = h;
}

void Mirror::CreateTexture(int w, int h) {  //creates an empty texture
  glGenTextures(1, &Textureid);
  glBindTexture(GL_TEXTURE_2D, Textureid);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glGenSamplers(1, &SamplerId);

}

void Mirror::AddDepthBuffer(){
  glBindFramebuffer(GL_FRAMEBUFFER, FBOid);
  glGenRenderbuffers(1, &DRBid);
  glBindRenderbuffer(GL_RENDERBUFFER, DRBid);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, DRBid);

}
void Mirror::Bind(){
  glBindFramebuffer(GL_FRAMEBUFFER, FBOid);
  glActiveTexture(GL_TEXTURE0 ); ///wut...
  glBindTexture(GL_TEXTURE_2D, Textureid);
  glBindSampler(0, SamplerId);

}
void Mirror::Unbind(){
  glBindFramebuffer(GL_FRAMEBUFFER, NULL);
  glBindTexture(GL_TEXTURE_2D, NULL);
  glBindSampler(0, NULL);


}

Mirror::~Mirror()
{
}
