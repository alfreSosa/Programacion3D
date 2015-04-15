#ifndef UGINE_MODEL_H
#define UGINE_MODEL_H

#include "entity.h"

class Mesh;

class Model : public Entity {
public:
	static Ptr<Model> Create(Ptr<Mesh> mesh);

	virtual void Update(float elapsed) {}
	virtual void Render();
protected:
	Model(Ptr<Mesh> mesh);
	virtual ~Model() {}
private:
	Ptr<Mesh> mMesh;
friend class Ptr<Model>;
friend class Ptr<const Model>;
};

#endif // UGINE_MODEL_H
