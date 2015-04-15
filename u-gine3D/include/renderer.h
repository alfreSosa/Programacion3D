#ifndef UGINE_RENDERER_H
#define UGINE_RENDERER_H

#include "smartptr.h"
#include "string.h"
#include "types.h"

class Renderer {
public:
	static Ptr<Renderer> Instance() { if ( mInstance == 0 ) mInstance = new Renderer(); return mInstance; }

	// Setup
	void Setup3D();
	void SetMatrices(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection);
	void SetViewport(int x, int y, int w, int h);

	// Drawing
	void ClearColorBuffer(const glm::vec3& color);
	void ClearDepthBuffer();

	// Texture
	uint32 LoadTexture(const String& filename, uint32& width, uint32& height);
	void FreeTexture(uint32 tex);
	void SetTexture(uint32 tex);

	// VBO
	uint32 CreateBuffer();
	void FreeBuffer(uint32 buffer);
	void SetVertexBufferData(uint32 vertexBuffer, const void* data, uint32 dataSize);
	void SetIndexBufferData(uint32 indexBuffer, const void* data, uint32 dataSize);
	void DrawBuffers(uint32 vertexBuffer, uint32 indexBuffer, uint32 numIndices);

	// Shaders
	uint32 CreateProgram(const String& vertex, const String& fragment);
	void FreeProgram(uint32 program);
	void UseProgram(uint32 program);
	const String& GetProgramError();
protected:
	Renderer();
	virtual ~Renderer() {}
private:
	static Ptr<Renderer> mInstance;
	int mMVPLoc;
	int mTexSamplerLoc;
	int mVPosLoc;
	int mVTexLoc;
	uint32 mDefaultProgram;
	String mProgramError;
friend class Ptr<Renderer>;
friend class Ptr<const Renderer>;
};

#endif // UGINE_RENDERER_H
