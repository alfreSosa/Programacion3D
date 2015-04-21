#include "../include/entity.h"
#include "../include/scene.h"


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