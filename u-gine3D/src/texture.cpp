#include "../include/texture.h"

Texture::Texture(const String& filename)
{
  mFilename = filename;
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