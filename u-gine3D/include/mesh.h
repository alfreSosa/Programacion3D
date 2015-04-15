#ifndef UGINE_MESH_H
#define UGINE_MESH_H

#include "array.h"
#include "string.h"
#include "submesh.h"

class Mesh {
public:
	static Ptr<Mesh> Create();
	static Ptr<Mesh> Create(const String& filename);

	const String& GetFilename() const;

	void AddSubmesh(Ptr<Submesh> submesh);
	void RemoveSubmesh(uint32 i);
	void RemoveSubmesh(Ptr<Submesh> submesh);
	uint32 NumSubmeshes() const;
	Ptr<const Submesh> GetSubmesh(uint32 i) const;
	Ptr<Submesh> GetSubmesh(uint32 i);

	void Render();
protected:
	Mesh(const String& filename);
	~Mesh() {}
private:
	String mFilename;
	Array<Ptr<Submesh>> mSubmeshes;
friend class Ptr<Mesh>;
friend class Ptr<const Mesh>;
};

#endif // UGINE_MESH_H
