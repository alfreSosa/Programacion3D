#include "../lib/glew/glew.h"
#include "../include/renderer.h"
#include "../include/vertex.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

Ptr<Renderer> Renderer::mInstance = nullptr;

Renderer::Renderer() {
  mDefaultProgram = CreateProgram("data/vertex.glsl", "data/fragment.glsl");
  mDepthProgram = CreateProgram("data/depth_vertex.glsl", "data/depth_fragment.glsl");
  UseProgram(mDefaultProgram);
}

void Renderer::Setup3D() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_TEXTURE_2D);
	glDepthFunc(GL_LEQUAL);
}

void Renderer::SetMatrices(const glm::mat4& model, const glm::mat4& view, const glm::mat4& projection, const glm::mat4& depthBias) {
  mat4 mvp = projection * view * model;
  mat4 mv = view * model;
  mat4 normal = glm::transpose(glm::inverse(mv));

  glUniformMatrix4fv(mMVPLoc, 1, false, glm::value_ptr(mvp));
  glUniformMatrix4fv(mMVLoc, 1, false, glm::value_ptr(mv));
  glUniformMatrix4fv(mNormalMatrixLoc, 1, false, glm::value_ptr(normal));
  glUniformMatrix4fv(mDepthBiasLoc, 1, false, glm::value_ptr(depthBias));
}

void Renderer::SetViewport(int x, int y, int w, int h) {
	glViewport(x, y, w, h);
	glScissor(x, y, w, h);
}

void Renderer::ClearColorBuffer(const glm::vec3& color) {
	glClearColor(color.r, color.g, color.b, 1);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::ClearDepthBuffer() {
	glClear(GL_DEPTH_BUFFER_BIT);
}

uint32 Renderer::CreateTexture(uint32 width, uint32 height, bool isDepth) {

  // Create GL texture
  GLuint handle;
  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  if (!isDepth)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
  else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, nullptr);

  glBindTexture(GL_TEXTURE_2D, 0);

  return handle;
}

uint32 Renderer::LoadTexture(const String& filename, uint32& width, uint32& height) {
	// Load bitmap
	int w, h, c;
	uint8* buffer = stbi_load(filename.ToCString(), &w, &h, &c, 4);
	if ( !buffer ) return 0;
	width = w;
	height = h;

	// Flip lines
	uint8* newBuffer = (uint8*)malloc(width*height*4);
	int line = 0;
	for ( int y = height-1; y >= 0; y-- ) {
		memcpy(&newBuffer[line*width*4], &buffer[y*width*4], width*4);
		line++;
	}
	free(buffer);
	buffer = newBuffer;

	// Create GL texture
	GLuint handle;
	glGenTextures(1, &handle);
	glBindTexture(GL_TEXTURE_2D, handle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Unload bitmap
	free(buffer);

	return handle;
}

void Renderer::FreeTexture(uint32 tex) {
	glDeleteTextures(1, &tex);
}

void Renderer::SetTexture(uint32 tex) {
  if (tex != 0)
    glUniform1i(mEnabledTextureLoc, true);
  else
    glUniform1i(mEnabledTextureLoc, false);
  glBindTexture(GL_TEXTURE_2D, tex);
}

uint32 Renderer::CreateBuffer() {
	uint32 buffer;
	glGenBuffers(1, &buffer);
	return buffer;
}

void Renderer::FreeBuffer(uint32 buffer) {
	glDeleteBuffers(1, &buffer);
}

void Renderer::SetVertexBufferData(uint32 vertexBuffer, const void* data, uint32 dataSize) {
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::SetIndexBufferData(uint32 indexBuffer, const void* data, uint32 dataSize) {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Renderer::DrawBuffers(uint32 vertexBuffer, uint32 indexBuffer, uint32 numIndices) {
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
  glEnableVertexAttribArray(mVPosLoc);
  glEnableVertexAttribArray(mVTexLoc);
  glEnableVertexAttribArray(mVNormalLoc);
  glVertexAttribPointer(mVPosLoc, 3, GL_FLOAT, false, sizeof(Vertex), (const void *)offsetof(Vertex, mPosition));
  glVertexAttribPointer(mVTexLoc, 2, GL_FLOAT, true, sizeof(Vertex), (const void *)offsetof(Vertex, mTexCoords));
  glVertexAttribPointer(mVNormalLoc, 3, GL_FLOAT, true, sizeof(Vertex), (const void *)offsetof(Vertex, mNormals));
  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32 Renderer::CreateFrameBuffer(uint32 colortex, uint32 depthtex) {
  uint32 buffer;
  glGenFramebuffers(1, &buffer);
  BindFrameBuffer(buffer);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, colortex, 0);
  glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthtex, 0);
  
  if (colortex)
    glDrawBuffer(GL_NONE);

  return buffer;
}

void Renderer::FreeFrameBuffer(uint32 handle) {
  glDeleteFramebuffers(1, &handle);
}

void Renderer::BindFrameBuffer(uint32 handle) {
  glBindFramebuffer(GL_FRAMEBUFFER, handle);
}

void Renderer::SetDepthTexture(uint32 tex) {
  glActiveTexture(GL_TEXTURE0 + 16);
  glBindTexture(GL_TEXTURE_2D, tex);
  glActiveTexture(GL_TEXTURE0);
}

void Renderer::EnableShadows(bool enable) {
  glUniform1i(mEnabledShadowsLoc, enable);
}


uint32 Renderer::CreateProgram(const String& vertex, const String& fragment) {
  //leo ficheros
  String vertexCode = String::Read(vertex);
  String fragmentCode = String::Read(fragment);
  const char *strVertexCode = vertexCode.ToCString();
  const char *strFragmentCode = fragmentCode.ToCString();
  //crear shaders
  GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  //pasar codigo
  glShaderSource(vertexShader, 1, &strVertexCode, NULL);
  glShaderSource(fragmentShader, 1, &strFragmentCode, NULL);
  //Compilamos Shaders
  GLint retCode;
  char errorLog[1024];
  glCompileShader(vertexShader);
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &retCode);
  if (retCode == GL_FALSE){
    glGetShaderInfoLog(vertexShader, sizeof(errorLog), NULL, errorLog);
    mProgramError = errorLog;
    glDeleteShader(vertexShader);
    return 0;
  }
  glCompileShader(fragmentShader);
  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &retCode);
  if (retCode == GL_FALSE){
    glGetShaderInfoLog(fragmentShader, sizeof(errorLog), NULL, errorLog);
    mProgramError = errorLog;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return 0;
  }

  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &retCode);
  if (retCode == GL_FALSE){ 
    glGetProgramInfoLog(program, sizeof(errorLog), NULL, errorLog);
    mProgramError = errorLog;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteProgram(program);
    return 0;
  }

	return program;
}

void Renderer::FreeProgram(uint32 program) {
  glDeleteProgram(program);
}

void Renderer::UseProgram(uint32 program) {
  if (program == 0)
    program = mDefaultProgram;

  glUseProgram(program);

	mMVPLoc = glGetUniformLocation(program, "MVP");
	mMVLoc = glGetUniformLocation(program, "modelView"); //nombre de las variables en el shader  comprobar
  mNormalMatrixLoc = glGetUniformLocation(program, "normalMatrix");
  mDepthBiasLoc = glGetUniformLocation(program, "depthBias");
  mTexSamplerLoc = glGetUniformLocation(program, "texSampler");
  mDepthSamplerLoc = glGetUniformLocation(program, "depthSampler");
	glUniform1i(mTexSamplerLoc, 0);
	mVPosLoc = glGetAttribLocation(program, "vpos");
	mVTexLoc = glGetAttribLocation(program, "vtex");
	mVNormalLoc = glGetAttribLocation(program, "vnormal");
  mLightingEnabledLoc = glGetUniformLocation(program, "lightingEnabled");

	for (uint32 i = 0; i < MAX_LIGHTS; i++){
		String enabled = String("lightEnabled[") + String::FromInt(i) + String("]");
		String pos = String("lightPos[") + String::FromInt(i) + String("]");
		String color = String("lightColor[") + String::FromInt(i) + String("]");
		String att = String("lightAtt[") + String::FromInt(i) + String("]");
    mLightEnabledLoc[i] = glGetUniformLocation(program, enabled.ToCString());
    mLightPosLoc[i] = glGetUniformLocation(program, pos.ToCString());
    mLightColorLoc[i] = glGetUniformLocation(program, color.ToCString());
    mLightAttLoc[i] = glGetUniformLocation(program, att.ToCString());
	}
  mVDiffuseLoc = glGetUniformLocation(program, "diffuse");
  mVAmbientLoc = glGetUniformLocation(program, "ambient");
  mShininessLoc = glGetUniformLocation(program, "shininess");
  mEnabledTextureLoc = glGetUniformLocation(program, "textEnabled");
  mEnabledShadowsLoc = glGetUniformLocation(program, "shadowsEnabled");
}

void Renderer::SetDiffuse(const glm::vec3& color) 
{
	glUniform3f(mVDiffuseLoc, color.r, color.g, color.b);
}

void Renderer::SetAmbient(const glm::vec3& color) 
{
	glUniform3f(mVAmbientLoc, color.r, color.g, color.b);
}

void Renderer::SetShininess(uint8 shininess) 
{
	glUniform1i(mShininessLoc, shininess);
}

void Renderer::EnableLighting(bool enable) 
{
	glUniform1i(mLightingEnabledLoc, enable);
}

void Renderer::EnableLight(uint32 index, bool enabled)
{
	glUniform1i(mLightEnabledLoc[index], enabled);
}

void Renderer::SetLightData(uint32 index, const glm::vec4& vector, const glm::vec3& color, float attenuation) 
{
	glUniform4f(mLightPosLoc[index], vector.x, vector.y, vector.z, vector.w);
	glUniform3f(mLightColorLoc[index], color.r, color.g, color.b);
	glUniform1f(mLightAttLoc[index], attenuation);
}

const String& Renderer::GetProgramError() {
	return mProgramError;
}