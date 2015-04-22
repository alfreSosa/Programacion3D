#include "../include/entity.h"
#include "../include/scene.h"



Entity::Entity()
{
  mPosition = vec3(0, 0, 0);
  mRotation = quat(1, 0, 0, 0);
  mScale = vec3(1, 1, 1);
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