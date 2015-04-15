#ifndef UGINE_ENTITY_H
#define UGINE_ENTITY_H

#include "types.h"

class Entity {
public:
	static Ptr<Entity> Create();

	const glm::vec3& GetPosition() const;
	glm::vec3& GetPosition();

	const glm::quat& GetRotation() const;
	glm::quat& GetRotation();

	const glm::vec3& GetScale() const;
	glm::vec3& GetScale();

	void Move(const glm::vec3& speed);

	virtual void Update(float elapsed) {}
	virtual void Render();
protected:
	Entity();
	virtual ~Entity() {}
private:
	glm::vec3 mPosition;
	glm::quat mRotation;
	glm::vec3 mScale;
friend class Ptr<Entity>;
friend class Ptr<const Entity>;
};

#endif // UGINE_ENTITY_H
