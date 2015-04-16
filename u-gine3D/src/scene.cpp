#include "../include/scene.h"
#include "../include/renderer.h"

Ptr<Scene> Scene::mInstance = nullptr;

Scene::Scene()
{
  RENDER->Setup3D();
}

void Scene::AddEntity(Ptr<Entity> entity)
{
  mEntities.Add(entity);
  Ptr<Camera> cam = entity.DownCast<Camera>();
  if (cam != nullptr)
    mCameras.Add(cam);
}

void Scene::RemoveEntity(Ptr<Entity> entity)
{
  mEntities.Remove(entity);
  Ptr<Camera> cam = entity.DownCast<Camera>();
  if (cam != nullptr)
    mCameras.Remove(cam);
}

void Scene::Update(float elapsed)
{
  uint32 length = mEntities.Size();
  for (uint32 i = 0; i < length; i++)
    mEntities[i]->Update(elapsed);
}

void Scene::SetModel(const mat4& m)
{
  mModelMatrix = m;
  RENDER->SetMatrices(mModelMatrix, mCurrentCamera->GetView(), mCurrentCamera->GetProjection());
}

void Scene::Render()
{
  uint32 camLength = mCameras.Size();
  uint32 length = mEntities.Size();

  for (uint32 i = 0; i < camLength; i++){
    mCurrentCamera = mCameras[i];
    mCameras[i]->Prepare();  
    for (uint32 j = 0; j < length; j++)
      mEntities[j]->Render();
  }

  
}