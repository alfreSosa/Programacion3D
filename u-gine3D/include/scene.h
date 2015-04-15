#ifndef UGINE_SCENE_H
#define UGINE_SCENE_H

#include "array.h"
#include "camera.h"
#include "entity.h"

class Scene {
public:
	static Ptr<Scene> Instance();

	Ptr<const Camera> GetCurrentCamera() const;
	Ptr<Camera> GetCurrentCamera();
	const glm::mat4& GetModel() const;
	void SetModel(const glm::mat4& m);

	void AddEntity(Ptr<Entity> entity);
	void RemoveEntity(Ptr<Entity> entity);
	uint32 GetNumEntities() const;
	Ptr<const Entity> GetEntity(uint32 index) const;
	Ptr<Entity> GetEntity(uint32 index);

	void Update(float elapsed);
	void Render();
protected:
	Scene();
	~Scene() {}
private:
	static Ptr<Scene> mInstance;
	Ptr<Camera> mCurrentCamera;
	glm::mat4 mModelMatrix;
	Array<Ptr<Camera>> mCameras;
	Array<Ptr<Entity>> mEntities;
friend class Ptr<Scene>;
friend class Ptr<const Scene>;
};

#endif // UGINE_SCENE_H
