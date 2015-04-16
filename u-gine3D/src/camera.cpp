#include "../include/camera.h"
#include "../include/renderer.h"

void Camera::Prepare()
{
  //calulamos matriz vista
  if (GetUsesTarget()){
    mViewMatrix = glm::lookAt(GetPosition(), mTarget, glm::vec3(0, 1, 0));
  }
  else{
    //lookat con balanceo
    mViewMatrix = glm::inverse(glm::rotate(glm::translate(glm::mat4(), GetPosition()), glm::angle(GetRotation()), glm::axis(GetRotation())));
    //mViewMatrix = glm::lookAt(GetPosition(), GetPosition() + GetRotation() * vec3(0,0,-1), glm::vec3(0, 1, 0));
  }
  
  RENDER->ClearColorBuffer(mColor);
  RENDER->ClearDepthBuffer();
}