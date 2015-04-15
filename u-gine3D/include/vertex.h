#ifndef UGINE_VERTEX_H
#define UGINE_VERTEX_H

#include "types.h"

struct Vertex {
	Vertex() : mPosition(0,0,0), mTexCoords(0,0) {}
	Vertex(const vec3& position, const vec2& texCoords) : mPosition(position), mTexCoords(texCoords) {}
	bool operator==(const Vertex& other) const { return mPosition == other.mPosition && mTexCoords == other.mTexCoords; }

	vec3 mPosition;
	vec2 mTexCoords;
};

#endif // UGINE_VERTEX_H
