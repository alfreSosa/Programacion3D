#ifndef UGINE_SUBMESH_H
#define UGINE_SUBMESH_H

#include "array.h"
#include "smartptr.h"
#include "texture.h"
#include "vertex.h"

class Submesh {
public:
	static Ptr<Submesh> Create(Ptr<Texture> tex = nullptr);

	void AddVertex(const Vertex& v);
	void AddTriangle(uint32 v0, uint32 v1, uint32 v2);

	Ptr<Texture> GetTexture() const;
	void SetTexture(Ptr<Texture> tex);

	const Array<Vertex>& GetVertices() const;
	Array<Vertex>& GetVertices();

	void Rebuild();
	void Render();
protected:
	Submesh(Ptr<Texture> tex);
	~Submesh();
private:
	Ptr<Texture> mTexture;
	uint32 mVertexBuffer;
	uint32 mIndexBuffer;
	Array<Vertex> mVertices;
	Array<uint16> mIndices;
friend class Ptr<Submesh>;
friend class Ptr<const Submesh>;
};

#endif // UGINE_SUBMESH_H
