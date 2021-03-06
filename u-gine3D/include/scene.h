#ifndef UGINE_SCENE_H
#define UGINE_SCENE_H

#include "array.h"
#include "camera.h"
#include "light.h"
#include "entity.h"

class Scene {
public:
  static Ptr<Scene> Instance(){ if (mInstance == 0) mInstance = new Scene(); return mInstance; }

  Ptr<const Camera> GetCurrentCamera() const { return mCurrentCamera.ConstCast(); }
  Ptr<Camera> GetCurrentCamera() { return mCurrentCamera; }
  const mat4& GetModel() const { return mModelMatrix; }
  void SetModel(const mat4& m);

  void AddEntity(Ptr<Entity> entity);
  void RemoveEntity(Ptr<Entity> entity);
  uint32 GetNumEntities() const { return mEntities.Size(); }
  Ptr<const Entity> GetEntity(uint32 index) const { return mEntities[index].ConstCast(); }
  Ptr<Entity> GetEntity(uint32 index) { return mEntities[index]; }
  void SetAmbient(const glm::vec3& ambient);
  void Update(float elapsed);
  void Render();
  //Shadows
  void SetDepthOrtho(float left, float right, float bottom, float top, float near, float far);
  void EnableShadows(bool enable);
protected:
	Scene();
	~Scene() {}
private:
	static Ptr<Scene> mInstance;
	Ptr<Camera> mCurrentCamera;
	mat4 mModelMatrix;
	Array<Ptr<Camera>> mCameras;
	Array<Ptr<Entity>> mEntities;
	Array<Ptr<Light>> mLights;
  //Shadows
  Ptr<Camera> mDepthCamera;
  glm::mat4 mDepthBias;
  glm::mat4 mScale;
  float mDepthFar;
  bool mEnableShadows;

friend class Ptr<Scene>;
friend class Ptr<const Scene>;
};

#endif // UGINE_SCENE_H
