#ifndef UGINE_VERTEX_H
#define UGINE_VERTEX_H

#include "types.h"

struct Vertex {
	Vertex() : mPosition(0,0,0), mTexCoords(0,0), mNormals(0,0,0) {}
  Vertex(const vec3& position, const vec2& texCoords, const vec3& normals) : mPosition(position), mTexCoords(texCoords), mNormals(normals) {}
  bool operator==(const Vertex& other) const { return mPosition == other.mPosition && mTexCoords == other.mTexCoords && mNormals == other.mNormals; }

  vec3 mPosition;
	vec2 mTexCoords;
  vec3 mNormals;
};

#endif // UGINE_VERTEX_H
