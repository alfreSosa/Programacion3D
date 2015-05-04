#include "../include/texture.h"

Texture::Texture(const String& filename)
{
  mFilename = filename;
}

Texture::~Texture() {
  if (mFramebuffer != 0)
    RENDER->FreeFrameBuffer(mFramebuffer);
  if (mHandle != 0)
    RENDER->FreeTexture(mHandle);
  if (mDepthHandle != 0)
    RENDER->FreeTexture(mDepthHandle);
}

Ptr<Texture> Texture::Create(const String& filename)
{
  uint32 width = 0;
  uint32 height = 0;
  uint32 handle = RENDER->LoadTexture(filename, width, height);
  if (handle == 0)
    return nullptr;

  Ptr<Texture> texture = new Texture(filename);
  texture->mHandle = handle;
  texture->mWidth = width;
  texture->mHeight = height;
  return texture;

}

Ptr<Texture> Texture::Create(uint32 width, uint32 height, uint32 buffers)
{
  uint32 handleDepth = 0, handle = 0, handleBuffer = 0;
  
  if (buffers & DEPTHBUFFER)
    handleDepth = RENDER->CreateTexture(width, height, true);
  if (buffers & COLORBUFFER)
    handle = RENDER->CreateTexture(width, height, false);

  if (handleDepth != 0 || handle != 0) {
    handleBuffer = RENDER->CreateFrameBuffer(handle, handleDepth);

    Ptr<Texture> texture = new Texture("");
    texture->mWidth = width;
    texture->mHeight = height;
    texture->mDepthHandle = handleDepth;
    texture->mHandle = handle;
    texture->mFramebuffer = handleBuffer;
    return texture;
  }
  else {
    return nullptr;
  }

}