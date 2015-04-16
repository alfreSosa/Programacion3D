#include "../include/model.h"
#include "../include/mesh.h"

Ptr<Model> Model::Create(Ptr<Mesh> mesh)
{
  if (mesh == nullptr)
    return nullptr;
  return new Model(mesh);
}

Model::Model(Ptr<Mesh> mesh)
{
  mMesh = mesh;
}

void Model::Render()
{
  Entity::Render();
  mMesh->Render();
}