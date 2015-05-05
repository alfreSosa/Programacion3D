#include "../include/bone.h"


Ptr<Bone> Bone::Create(const String& name, const glm::mat4& transform, const Array<uint32>& submeshes) {
  Ptr<Bone> bone = new Bone(name, transform, submeshes);
  bone->mThis = bone;
  return bone;
}

Bone::Bone(const String& name, const glm::mat4& transform, const Array<uint32>& submeshes) {
  mName = name;
  mDefaultTransform = transform;
  mSubmeshes = submeshes;
}

void Bone::AddChild(const Ptr<Bone>& bone) {
  bone->mParent = mThis;
  mChildren.Add(bone);
}

Ptr<Bone> Bone::Find(const String& name) {
  if (name == mName)
    return mThis;
  
  uint32 childrenLength = mChildren.Size();
  for (uint32 i = 0; i < childrenLength; i++) {
    Ptr<Bone> f = nullptr;
    f = mChildren[i]->Find(name);
    if (f != nullptr)
      return f;
  }
  return nullptr;
}

void Bone::CalculateTransform(float frame, uint32 firstSeqFrame, uint32 lastSeqFrame) {

}

