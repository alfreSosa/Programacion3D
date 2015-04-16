#include "../include/submesh.h"

void Submesh::AddTriangle(uint32 v0, uint32 v1, uint32 v2)
{
  mIndices.Add(v0);
  mIndices.Add(v1);
  mIndices.Add(v2);
}

Submesh::Submesh(Ptr<Texture> tex)
{
  mVertexBuffer = RENDER->CreateBuffer();
  mIndexBuffer = RENDER->CreateBuffer();
  SetTexture(tex);
}

Submesh::~Submesh()
{
  RENDER->FreeBuffer(mVertexBuffer);
  RENDER->FreeBuffer(mIndexBuffer);
}

Ptr<Submesh> Submesh::Create(Ptr<Texture> tex)
{
  return new Submesh(tex);
}

void Submesh::Rebuild()
{
  uint32 indexSize = mIndices.Size() * sizeof(uint16);
  uint32 vertexSize = mVertices.Size() * sizeof(Vertex);

  RENDER->SetIndexBufferData(mIndexBuffer, &mIndices, indexSize);
  RENDER->SetVertexBufferData(mVertexBuffer, &mVertices, vertexSize);
}

void Submesh::Render()
{
  if (mTexture != nullptr)
    RENDER->SetTexture(mTexture->GetHandle());
  else
    RENDER->SetTexture(0);

  RENDER->DrawBuffers(mVertexBuffer, mIndexBuffer, mIndices.Size());
}