#ifndef UGINE_RENDERER_H
#define UGINE_RENDERER_H

#include "smartptr.h"
#include "string.h"
#include "types.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))
#define MAX_LIGHTS 8

class Renderer {
public:
	static Ptr<Renderer> Instance() { if ( mInstance == 0 ) mInstance = new Renderer(); return mInstance; }

	// Setup
	void Setup3D();
  void SetMatrices(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const glm::mat4& depthBias);
	void SetViewport(int x, int y, int w, int h);

	// Drawing
	void ClearColorBuffer(const glm::vec3& color);
	void ClearDepthBuffer();

	// Texture
  uint32 CreateTexture(uint32 width, uint32 height, bool isDepth);
	uint32 LoadTexture(const String& filename, uint32& width, uint32& height);
	void FreeTexture(uint32 tex);
	void SetTexture(uint32 tex);

	// VBO
	uint32 CreateBuffer();
	void FreeBuffer(uint32 buffer);
	void SetVertexBufferData(uint32 vertexBuffer, const void* data, uint32 dataSize);
	void SetIndexBufferData(uint32 indexBuffer, const void* data, uint32 dataSize);
	void DrawBuffers(uint32 vertexBuffer, uint32 indexBuffer, uint32 numIndices);
  
  //FrameBuffer
  uint32 CreateFrameBuffer(uint32 colortex, uint32 depthtex);
  void FreeFrameBuffer(uint32 handle);
  void BindFrameBuffer(uint32 handle);

	// Shaders
	uint32 CreateProgram(const String& vertex, const String& fragment);
  uint32 GetDepthProgram() { return mDepthProgram; }
	void FreeProgram(uint32 program);
	void UseProgram(uint32 program);
	const String& GetProgramError();

	//Lightning
	void SetDiffuse(const glm::vec3& color);
	void SetAmbient(const glm::vec3& color);
	void SetShininess(uint8 shininess);

	void EnableLighting(bool enable);
	void EnableLight(uint32 index, bool enabled);
	void SetLightData(uint32 index, const glm::vec4& vector, const glm::vec3& color, float attenuation);

  //Shadows
  void SetDepthTexture(uint32 tex);
  void EnableShadows(bool enable);
protected:
	Renderer();
	virtual ~Renderer() {}
private:
	static Ptr<Renderer> mInstance;
	int mMVPLoc;
	int mMVLoc;
	int mNormalMatrixLoc;
	int mTexSamplerLoc;
	int mVPosLoc;
	int mVTexLoc;
  //Light
	int mVNormalLoc;
	int mLightingEnabledLoc;
	int mLightEnabledLoc[MAX_LIGHTS];
	int mLightPosLoc[MAX_LIGHTS];
	int mLightColorLoc[MAX_LIGHTS];
	int mLightAttLoc[MAX_LIGHTS];
	int mVDiffuseLoc;
	int mVAmbientLoc;
  int mShininessLoc;
  int mEnabledTextureLoc;
  //Shadows
  int mDepthSamplerLoc;
  int mDepthBiasLoc;
  int mEnabledShadowsLoc;

  uint32 mDefaultProgram;
  uint32 mDepthProgram;
	String mProgramError;
friend class Ptr<Renderer>;
friend class Ptr<const Renderer>;
};

#endif // UGINE_RENDERER_H
