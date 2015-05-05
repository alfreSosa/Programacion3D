#ifndef UGINE_BONE_H
#define UGINE_BONE_H

#include "types.h"
#include "string.h"

class Bone 
{
public:
  static Ptr<Bone> Create(const String& name, const glm::mat4& transform, const Array<uint32>& submeshes);
  void AddChild(const Ptr<Bone>& bone);
  Ptr<Bone> Find(const String& name);
  const String& GetName() const { return mName; }
  const glm::mat4& GetDefaultTransform() const { return mDefaultTransform; }
  const glm::mat4& GetCurrentTransform() const { return mCurrentTransform; }
  void CalculateTransform(float frame, uint32 firstSeqFrame, uint32 lastSeqFrame);
  const Array<uint32>& GetSubmeshes() const { return mSubmeshes; }
  const Array<Ptr<Bone>>& GetChildren() const { return mChildren; }
  void AddPosition(uint32 frame, const glm::vec3& position);
  void AddRotation(uint32 frame, const glm::quat& rotation);
  void AddScale(uint32 frame, const glm::vec3& scale);
protected:
  Bone(const String& name, const glm::mat4& transform, const Array<uint32>& submeshes);
  ~Bone() { }
  glm::vec3 GetPosition(float frame) const;
  glm::quat GetRotation(float frame) const;
  glm::vec3 GetScale(float frame) const;
private:
  WPtr<Bone> mThis;
  String mName;
  WPtr<Bone> mParent;
  glm::mat4 mDefaultTransform;
  glm::mat4 mCurrentTransform;
  Array<uint32> mSubmeshes;
  Array<Ptr<Bone>> mChildren;
  Array<uint32> mPositionFrames;
  Array<uint32> mRotationFrames;
  Array<uint32> mScaleFrames;
  Array<glm::vec3> mPositions;
  Array<glm::quat> mRotations;
  Array<glm::vec3> mScales;
  friend class Ptr<Bone>;
  friend class Ptr<const Bone>;

};
#endif