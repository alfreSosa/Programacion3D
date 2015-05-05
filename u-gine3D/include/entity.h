#ifndef UGINE_ENTITY_H
#define UGINE_ENTITY_H

#include "types.h"

class Entity {
public:
	static Ptr<Entity> Create();

  const vec3& GetPosition() const { return mPosition; }
  vec3& GetPosition() { return mPosition; }

  const quat& GetRotation() const { return mRotation; }
  quat& GetRotation() { return mRotation; }

  const vec3& GetScale() const { return mScale; }
  vec3& GetScale() { return mScale; }

  void Move(const vec3& speed) { mPosition += mRotation * speed; }

	virtual void Update(float elapsed) {}
	virtual void Render();
protected:
  Entity();
	virtual ~Entity() {}
private:
	vec3 mPosition;
	quat mRotation;
	vec3 mScale;
friend class Ptr<Entity>;
friend class Ptr<const Entity>;
};

#endif // UGINE_ENTITY_H
