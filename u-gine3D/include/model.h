#ifndef UGINE_MODEL_H
#define UGINE_MODEL_H

#include "entity.h"
#include "bone.h"
#include "mesh.h"

class Model : public Entity {
public:
	static Ptr<Model> Create(Ptr<Mesh> mesh);

  virtual void Update(float elapsed);
	virtual void Render();

  //Animation
  void Animate(bool animate, uint32 seq) {
    if (mMesh->GetRootBone() != nullptr) {
      mAnimating = animate;
      mSequence = seq;
    }
  }
  uint32 GetSequence() const { return mSequence; }
  int GetFPS() const { return mFPS; }
  void SetFPS(int fps) { this->mFPS = fps; }
  float GetCurrentFrame() const { return mCurrentFrame; }
  void SetCurrentFrame(float frame) { mCurrentFrame = frame; }
  Array<WPtr<Bone>> GetBones(const Ptr<Bone>& bone);
protected:
	Model(Ptr<Mesh> mesh);
	virtual ~Model() {}
private:
	Ptr<Mesh> mMesh;
  bool mAnimating;
  uint32 mSequence;
  int mFPS;
  float mCurrentFrame;
  Array<WPtr<Bone>> mBones;
friend class Ptr<Model>;
friend class Ptr<const Model>;
};

#endif // UGINE_MODEL_H
