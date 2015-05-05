#include "../include/scene.h"
#include "../include/renderer.h"
#include "../include/texture.h"

Ptr<Scene> Scene::mInstance = nullptr;

Scene::Scene()
{
  RENDER->Setup3D();
  mDepthCamera = Camera::Create();
  mDepthCamera->SetUsesTarget(true);
  Ptr<Texture> tex = Texture::Create(1024, 1024, Texture::DEPTHBUFFER);
  mDepthCamera->SetViewport(0, 0, 1024, 1024);
  mDepthCamera->SetRenderTarget(tex);
  mDepthFar = 0;
  mEnableShadows = false;
  mScale = { 0.5, 0, 0, 0, 0, 0.5, 0, 0, 0, 0, 0.5, 0, 0.5, 0.5, 0.5, 1 };

}


void Scene::SetDepthOrtho(float left, float right, float bottom, float top, float near, float far) {
  mDepthCamera->SetProjection(glm::ortho(left, right, bottom, top, near, far));
  mDepthFar = far * 0.5f;
}

void Scene::EnableShadows(bool enable) {
  mEnableShadows = enable;
}

void Scene::AddEntity(Ptr<Entity> entity)
{
  mEntities.Add(entity);
  
  Ptr<Camera> cam = entity.DownCast<Camera>();
  if (cam != nullptr)
	  mCameras.Add(cam);

  Ptr<Light> light = entity.DownCast<Light>();
  if (light != nullptr)
	  mLights.Add(light);
}

void Scene::RemoveEntity(Ptr<Entity> entity)
{
  mEntities.Remove(entity);
  
  Ptr<Camera> cam = entity.DownCast<Camera>();
  if (cam != nullptr)
    mCameras.Remove(cam);

  Ptr<Light> light = entity.DownCast<Light>();
  if (light != nullptr)
	  mLights.Remove(light);;
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
  RENDER->SetMatrices(mModelMatrix, mCurrentCamera->GetView(), mCurrentCamera->GetProjection(), mDepthBias);
}

void Scene::Render()
{
  uint32 camLength = mCameras.Size();
  uint32 lightLength = mLights.Size();
  uint32 length = mEntities.Size();

  if (mEnableShadows) {
    Ptr<Light> fDir = nullptr;
    bool found = false;
    for (uint32 j = 0; j < lightLength && !found; j++)
      if (mLights[j]->GetType() == Light::DIRECTIONAL) {
        fDir = mLights[j];
        found = true;
      }
    if (fDir != nullptr) {
      mCurrentCamera = mDepthCamera;
      RENDER->UseProgram(RENDER->GetDepthProgram());
      vec3 NcamPos = glm::normalize(fDir->GetPosition());
      vec3 posCam = NcamPos * mDepthFar;
      mDepthCamera->GetPosition() = posCam;
      mDepthCamera->GetTarget() = -posCam;
      mDepthCamera->Prepare();
      mDepthBias = mScale * mDepthCamera->GetProjection() * mDepthCamera->GetView();
      for (uint32 j = 0; j < length; j++)
        mEntities[j]->Render();

      RENDER->UseProgram(0);
      RENDER->SetDepthTexture(mDepthCamera->GetRenderTarget()->GetDepthHandle());
    }
  }

  RENDER->EnableShadows(mEnableShadows);

  if (lightLength > 0)
	  RENDER->EnableLighting(true);
  else 
	  RENDER->EnableLighting(false);

  for (uint32 i = 0; i < camLength; i++){
    mCurrentCamera = mCameras[i];
    mCameras[i]->Prepare(); 
	  for (uint32 j = 0; j < lightLength; j++)
		  mLights[j]->Prepare();
    for (uint32 j = 0; j < length; j++)
      mEntities[j]->Render();
  }

  for (uint32 i = 0; i < MAX_LIGHTS; i++)
	  RENDER->EnableLight(i, false);
  

}

void Scene::SetAmbient(const glm::vec3& ambient)
{
  RENDER->SetAmbient(ambient);
}