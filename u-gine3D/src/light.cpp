#include "../include/light.h"
#include "../include/scene.h"
#include "../include/camera.h"

bool Light::lightsUsed[] = { false };

Light::Light()
{

}

Ptr<Light> Light::Create()
{
	for (int i = 0; i < MAX_LIGHTS; i++)
	{
		if (!lightsUsed[i]) {
			lightsUsed[i] = true;
			Light *l = new Light();
			l->mIndex = i;
			return l;
		}
	}
	return nullptr;
}

Light::~Light()
{
	lightsUsed[mIndex] = false;
}

void Light::Prepare()
{
	RENDER->EnableLight(mIndex, true);

	vec4 pos;
	pos.x = GetPosition().x;
	pos.y = GetPosition().y;
	pos.z = GetPosition().z;

	switch (mType)
	{
	case DIRECTIONAL:
		pos.w = 0;
		break;
	case POINT:
		pos.w = 1;
		break;
	}
		
	RENDER->SetLightData(mIndex, Scene::Instance()->GetCurrentCamera()->GetView() * pos, mColor, mAttenuation);
}
