#include "../include/entity.h"
#include "../include/scene.h"



Entity::Entity()
{
  mPosition.x = 0;
  mPosition.y = 0;
  mPosition.z = 0;
  mRotation.w = 1;
  mRotation.x = 0;
  mRotation.y = 0;
  mRotation.z = 0;
  mScale.x = 1;
  mScale.y = 1;
  mScale.z = 1;
}
Ptr<Entity> Entity::Create()
{
  return new Entity();
}

void Entity::Render()
{
  mat4 mat = glm::translate(glm::mat4(), mPosition);
  mat = glm::rotate(mat, glm::angle(mRotation), glm::axis(mRotation));
  mat = glm::scale(mat, mScale);
  Scene::Instance()->SetModel(mat);
}