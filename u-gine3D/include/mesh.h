#ifndef UGINE_MESH_H
#define UGINE_MESH_H

#include "array.h"
#include "string.h"
#include "submesh.h"
#include "animseq.h"
#include "bone.h"

class Mesh {
public:
	static Ptr<Mesh> Create();
	static Ptr<Mesh> Create(const String& filename);

  const String& GetFilename() const { return mFilename; }

  void AddSubmesh(Ptr<Submesh> submesh) { mSubmeshes.Add(submesh); submesh->Rebuild(); }
  void RemoveSubmesh(uint32 i) { mSubmeshes.RemoveAt(i); }
  void RemoveSubmesh(Ptr<Submesh> submesh) { mSubmeshes.Remove(submesh); }
  uint32 NumSubmeshes() const { return mSubmeshes.Size(); }
  Ptr<const Submesh> GetSubmesh(uint32 i) const { return mSubmeshes[i].ConstCast(); }
  Ptr<Submesh> GetSubmesh(uint32 i) { return mSubmeshes[i]; }
	void Render();

  //Animation
  const Ptr<Bone>& GetRootBone() { return mRootBone; }
  Ptr<const Bone> GetRootBone() const { return mRootBone.ConstCast(); }
  void SetRootBone(const Ptr<Bone>& bone) { mRootBone = bone; }
  void AddSequence(const AnimSeq& seq) { mSequences.Add(seq); }
  uint32 NumSequences() const { return mSequences.Size(); }
  uint32 GetSequenceNamed(const String& name) const;
  uint32 GetSequenceFirstFrame(uint32 seq) const { return mSequences[seq].GetFirstFrame(); }
  uint32 GetSequenceLastFrame(uint32 seq) const { return mSequences[seq].GetLastFrame(); }
  uint32 GetSequenceNumFrames(uint32 seq) const { return mSequences[seq].GetNumFrames(); }
  void RenderBone(const Ptr<const Bone>& bone, bool animated);
protected:
  Mesh() { }
	~Mesh() { }
private:
	String mFilename;
	Array<Ptr<Submesh>> mSubmeshes;
  Ptr<Bone> mRootBone;
  Array<AnimSeq> mSequences;
friend class Ptr<Mesh>;
friend class Ptr<const Mesh>;
};

#endif // UGINE_MESH_H
