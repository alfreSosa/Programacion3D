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

	//Lightning
	void SetDiffuse(const glm::vec3& color);
	void SetAmbient(const glm::vec3& color);
	void SetShininess(uint8 shininess);

  //Averiguar si guardar un array fijo de luces
	void EnableLighting(bool enable);
	void EnableLight(uint32 index, bool enabled);
	void SetLightData(uint32 index, const glm::vec4& vector, const glm::vec3& color, float attenuation);

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

	uint32 mDefaultProgram;
	String mProgramError;
friend class Ptr<Renderer>;
friend class Ptr<const Renderer>;
};

#endif // UGINE_RENDERER_H
