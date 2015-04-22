#include "../include/camera.h"
#include "../include/renderer.h"


Ptr<Camera> Camera::Create()
{
  return new Camera();
}

void Camera::Prepare()
{
  //calulamos matriz vista
  if (GetUsesTarget()){
    mViewMatrix = glm::lookAt(GetPosition(), mTarget, glm::vec3(0, 1, 0));
  }
  else{
    //lookat con balanceo
    //mViewMatrix = glm::inverse(glm::rotate(glm::translate(glm::mat4(), GetPosition()), glm::angle(GetRotation()), glm::axis(GetRotation())));
	  //MIKEL:  mViewMatrix = glm::lookAt(GetPosition(), GetPosition() + GetRotation() * glm::vec3(1, 0, 0), glm::vec3(0, 1, 0));
    mViewMatrix = glm::lookAt(GetPosition(), GetPosition() + GetRotation() * vec3(0,0,-1), glm::vec3(0, 1, 0));
  }

  RENDER->SetViewport(mVX, mVY, mVW, mVH);
  RENDER->ClearColorBuffer(mColor);
  RENDER->ClearDepthBuffer();
}