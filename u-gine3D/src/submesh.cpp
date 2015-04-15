#include "../include/submesh.h"

void Submesh::AddTriangle(uint32 v0, uint32 v1, uint32 v2)
{
  mIndices.Add(v0);
  mIndices.Add(v1);
  mIndices.Add(v2);
}
