#ifndef UGINE_MESH_H
#define UGINE_MESH_H

#include "array.h"
#include "string.h"
#include "submesh.h"

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
protected:
  Mesh() { }
	~Mesh() { }
private:
	String mFilename;
	Array<Ptr<Submesh>> mSubmeshes;
friend class Ptr<Mesh>;
friend class Ptr<const Mesh>;
};

#endif // UGINE_MESH_H
