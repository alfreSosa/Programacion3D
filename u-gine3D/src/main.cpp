#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "../include/u-gine.h"
#define FULLSCREEN false

void Practica1();

int main() 
{
	Practica1();
	return 0;
}

void Practica1()
{
	if (FULLSCREEN)
		Screen::Instance()->Open(Screen::Instance()->GetDesktopWidth(), Screen::Instance()->GetDesktopHeight(), true);
	else
		Screen::Instance()->Open(800, 600, false);

	double angle = 0;
	Ptr<Mesh> caja = ResourceManager::Instance()->LoadMesh("data/teapot.msh");
	Ptr<Model> cubo = Model::Create(caja);
	cubo->GetPosition() = vec3(0, 0, 0);
	Scene::Instance()->AddEntity(cubo.UpCast<Entity>());

	Ptr<Camera> mainCamera = Camera::Create();
	mainCamera->SetUsesTarget(true);
	mainCamera->GetTarget() = cubo->GetPosition();
	mainCamera->GetPosition() = vec3(1, 1, 1);
	mainCamera->SetColor(vec3(1, 1, 1));
	mainCamera->SetProjection(glm::perspective<float>(1.7f, (float)Screen::Instance()->GetWidth() / Screen::Instance()->GetHeight(), 0.2, 100));
	mainCamera->SetViewport(0, 0, Screen::Instance()->GetWidth(), Screen::Instance()->GetHeight());

	Scene::Instance()->AddEntity(mainCamera.UpCast<Entity>());

	while (!Screen::Instance()->ShouldClose() && !Screen::Instance()->IsKeyPressed(GLFW_KEY_ESCAPE)) {

		angle += 5 * Screen::Instance()->GetElapsed();
		cubo->GetRotation() = glm::angleAxis<float>(angle, vec3(0, 1, 0));

		Scene::Instance()->Update(Screen::Instance()->GetElapsed());
		Scene::Instance()->Render();

		Screen::Instance()->Refresh();
		Screen::Instance()->SetTitle(Renderer::Instance()->GetProgramError());
	}
}


