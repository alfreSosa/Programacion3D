#ifndef UGINE_TEXTURE_H
#define UGINE_TEXTURE_H

#include "renderer.h"
#include "smartptr.h"
#include "string.h"

class Texture {
public:
  enum Buffers {
    COLORBUFFER = 1,
    DEPTHBUFFER = 2
  };
	static Ptr<Texture> Create(const String& filename);
  static Ptr<Texture> Create(uint32 width, uint32 height, uint32 buffers = COLORBUFFER);
  uint32 GetFrameBuffer() const { return mFramebuffer; }
  uint32 GetDepthHandle() const { return mDepthHandle; }

  const String& GetFilename() const { return mFilename;}
  uint32 GetHandle() const { return mHandle; }
  uint32 GetWidth() const { return mWidth; }
  uint32 GetHeight() const { return mHeight; }
protected:
	Texture(const String& filename);
  ~Texture();
private:
	String mFilename;
	uint32 mHandle;
	uint32 mWidth;
	uint32 mHeight;
  uint32 mFramebuffer;
  uint32 mDepthHandle;
friend class Ptr<Texture>;
friend class Ptr<const Texture>;
};

#endif // UGINE_TEXTURE_H
