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

void Bone::AddPosition(uint32 frame, const glm::vec3& position) {
  mPositionFrames.Add(frame);
  mPositions.Add(position);
}

void Bone::AddRotation(uint32 frame, const glm::quat& rotation) {
  mRotationFrames.Add(frame);
  mRotations.Add(rotation);
}

void Bone::AddScale(uint32 frame, const glm::vec3& scale) {
  mScaleFrames.Add(frame);
  mScales.Add(scale);
}

void Bone::CalculateTransform(float frame, uint32 firstSeqFrame, uint32 lastSeqFrame) {
  uint32 posSize = mPositionFrames.Size();

  bool hasFrame = false;
  for (uint32 i = 0; i < posSize && !hasFrame; i++)
    if (mPositionFrames[i] >= firstSeqFrame || mPositionFrames[i] <= lastSeqFrame)
      hasFrame = true;

  if (hasFrame) {
    vec3 position = GetPosition(frame);
    vec3 scale = GetScale(frame);
    quat rot = GetRotation(frame); 

    mCurrentTransform = glm::translate(glm::mat4(), position);
    mCurrentTransform = glm::rotate(mCurrentTransform, glm::angle(rot), glm::axis(rot));
    mCurrentTransform = glm::scale(mCurrentTransform, scale);
  }
  else{
    mCurrentTransform = mDefaultTransform;
  }
}

glm::vec3 Bone::GetPosition(float frame) const {
  uint32 posSize = mPositionFrames.Size();
  uint32 i = 0;
  for (; i < posSize; i++) {
    if (mPositionFrames[i] == frame) {
      return mPositions[i];
    }
    else if (mPositionFrames[i] > frame) {
      uint32 prevFrame = 0;
      uint32 indPrevFrame = 0;
      uint32 nextFrame = 1000000;
      uint32 indNextFrame = 0;

      for (uint32 j = 0; j < posSize; j++) {
        if (mPositionFrames[j] < frame)
          if (mPositionFrames[j] > prevFrame) {
            prevFrame = mPositionFrames[j];
            indPrevFrame = j;
          }

        if (mPositionFrames[j] > frame)
          if (mPositionFrames[j] < nextFrame) {
            nextFrame = mPositionFrames[j];
            indNextFrame = j;
          }
      }

      return glm::mix(mPositions[indPrevFrame], mPositions[indNextFrame], (frame - prevFrame) / (nextFrame - prevFrame));
    }
  }
  return mPositions[i - 1];
}

glm::vec3 Bone::GetScale(float frame) const {
  uint32 size = mScaleFrames.Size();
  uint32 i = 0;
  for (; i < size; i++) {
    if (mScaleFrames[i] == frame) {
      return mScales[i];
    }
    else if (mScaleFrames[i] > frame) {
      uint32 prevFrame = 0;
      uint32 indPrevFrame = 0;
      uint32 nextFrame = 1000000;
      uint32 indNextFrame = 0;

      for (uint32 j = 0; j < size; j++) {
        if (mScaleFrames[j] < frame)
          if (mScaleFrames[j] > prevFrame) {
            prevFrame = mScaleFrames[j];
            indPrevFrame = j;
          }

        if (mScaleFrames[j] > frame)
          if (mScaleFrames[j] < nextFrame) {
            nextFrame = mScaleFrames[j];
            indNextFrame = j;
          }
      }
      return glm::mix(mScales[indPrevFrame], mScales[indNextFrame], (frame - prevFrame) / (nextFrame - prevFrame));
    }
  }

  return mScales[i - 1];
}


glm::quat Bone::GetRotation(float frame) const {
  uint32 size = mRotationFrames.Size();
  uint32 i = 0;
  for (; i < size; i++) {
    if (mRotationFrames[i] == frame) {
      return mRotations[i];
    }
    else if (mRotationFrames[i] > frame) {
      uint32 prevFrame = 0;
      uint32 indPrevFrame = 0;
      uint32 nextFrame = 1000000;
      uint32 indNextFrame = 0;

      for (uint32 j = 0; j < size; j++) {
        if (mRotationFrames[j] < frame)
          if (mRotationFrames[j] > prevFrame) {
            prevFrame = mRotationFrames[j];
            indPrevFrame = j;
          }

        if (mRotationFrames[j] > frame)
          if (mRotationFrames[j] < nextFrame) {
            nextFrame = mRotationFrames[j];
            indNextFrame = j;
          }
      }

      return glm::slerp(mRotations[indPrevFrame], mRotations[indNextFrame], (frame - prevFrame) / (nextFrame - prevFrame));
    }
  }
  return mRotations[i - 1];
}

