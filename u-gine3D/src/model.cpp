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
  mAnimating = false;
  mSequence = 0;
  mFPS = 0;
  mCurrentFrame = 0;
  if (mesh->GetRootBone() != nullptr) {
    mBones = GetBones(mesh->GetRootBone());
  }
}

Array<WPtr<Bone>> Model::GetBones(const Ptr<Bone>& bone) {
  Array<WPtr<Bone>> bones;
  bones.Add(bone);

  Array<Ptr<Bone >> childrens = bone->GetChildren();
  uint32 size = childrens.Size();

  for (uint32 i = 0; i < size; i++) {
    Array<WPtr<Bone>> child = GetBones(childrens[i]);
    uint32 sizeChild = child.Size();
    for (uint32 j = 0; j < sizeChild; j++)
      bones.Add(child[j]);
  }
  return bones;
}

void Model::Update(float elapsed)
{
  mCurrentFrame += mFPS * elapsed;
  if (mCurrentFrame < mMesh->GetSequenceFirstFrame(mSequence)) {
    mCurrentFrame += mMesh->GetSequenceNumFrames(mSequence);
  }
  else if (mCurrentFrame > mMesh->GetSequenceLastFrame(mSequence)) {
    mCurrentFrame -= mMesh->GetSequenceNumFrames(mSequence);
  }
}

void Model::Render()
{
  Entity::Render();
  if (mAnimating) {
    uint32 size = mBones.Size();
    for (uint32 i = 0; i < size; i++)
      mBones[i]->CalculateTransform(mCurrentFrame, mMesh->GetSequenceFirstFrame(mSequence), mMesh->GetSequenceLastFrame(mSequence));
  }

  mMesh->Render(mAnimating);
}