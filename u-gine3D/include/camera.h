#ifndef UGINE_CAMERA_H
#define UGINE_CAMERA_H

#include "entity.h"

class Camera : public Entity {
public:
	static Ptr<Camera> Create();

  int32 GetViewportX() const { return mVX; }
  int32 GetViewportY() const { return mVY; }
  uint16 GetViewportWidth() const { return mVW; }
  uint16 GetViewportHeight() const { return mVH; }
  void SetViewport(int32 x, int32 y, uint16 w, uint16 h) { mVX = x; mVY = y; mVW = w; mVH = h; }

  void SetProjection(const mat4& proj) { mProjMatrix = proj; }
  const mat4& GetProjection() const { return mProjMatrix; }

  const mat4& GetView() const { return mViewMatrix; }

  const vec3& GetColor() const { return mColor; }
  void SetColor(const vec3& color) { mColor = color; }

  bool GetUsesTarget() const { return mUsesTarget; }
  void SetUsesTarget(bool usesTarget) { mUsesTarget = usesTarget; }

  const vec3& GetTarget() const { return mTarget; }
  vec3& GetTarget() { return mTarget; }

	void Prepare();
	virtual void Render() {}
protected:
	Camera();
	virtual ~Camera() {}
private:
	mat4 mProjMatrix;
	mat4 mViewMatrix;
	int32 mVX, mVY;
	uint16 mVW, mVH;
	vec3 mColor;
	bool mUsesTarget;
	vec3 mTarget;
friend class Ptr<Camera>;
friend class Ptr<const Camera>;
};

#endif // UGINE_CAMERA_H