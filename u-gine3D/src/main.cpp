#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "../include/u-gine.h"
#define FULLSCREEN false

void Practica1();
void Practica2();
void Practica3();
void Practica4();

int main() 
{
	//Practica1();
  //Practica2();
  //Practica3();
  Practica4();
	return 0;
}

void Practica1()
{
	if (FULLSCREEN)
		Screen::Instance()->Open(Screen::Instance()->GetDesktopWidth(), Screen::Instance()->GetDesktopHeight(), true);
	else
		Screen::Instance()->Open(800, 600, false);

	double angle = 0;
	Ptr<Mesh> caja = ResourceManager::Instance()->LoadMesh("data/box.msh");
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

void Practica2()
{
  if (FULLSCREEN)
    Screen::Instance()->Open(Screen::Instance()->GetDesktopWidth(), Screen::Instance()->GetDesktopHeight(), true);
  else
    Screen::Instance()->Open(800, 600, false);

  Scene::Instance()->SetAmbient(vec3(0.2, 0.2, 0.2));

  double angle = 0;
  Ptr<Mesh> teapot = ResourceManager::Instance()->LoadMesh("data/teapot.msh");
  Ptr<Model> tetera = Model::Create(teapot);
  tetera->GetPosition() = vec3(0, 0, 0);
  Scene::Instance()->AddEntity(tetera.UpCast<Entity>());

  Ptr<Camera> mainCamera = Camera::Create();
  mainCamera->SetUsesTarget(true);
  mainCamera->GetTarget() = tetera->GetPosition();
  mainCamera->GetPosition() = vec3(0, 1, 3);
  mainCamera->SetColor(vec3(0, 0, 0));
  mainCamera->SetProjection(glm::perspective<float>(1.7f, (float)Screen::Instance()->GetWidth() / Screen::Instance()->GetHeight(), 0.2, 100));
  mainCamera->SetViewport(0, 0, Screen::Instance()->GetWidth(), Screen::Instance()->GetHeight());
  Scene::Instance()->AddEntity(mainCamera.UpCast<Entity>());

  Ptr<Light> pointLight = Light::Create();
  pointLight->SetColor(vec3(0, 1, 0));
  pointLight->SetType(Light::POINT);
  pointLight->SetAttenuation(0.05);
  pointLight->GetPosition() = mainCamera->GetPosition();
  Scene::Instance()->AddEntity(pointLight.UpCast<Entity>());

  Ptr<Light> directionalLight = Light::Create();
  directionalLight->SetColor(vec3(0, 0, 1));
  directionalLight->SetType(Light::DIRECTIONAL);
  directionalLight->SetAttenuation(0);
  directionalLight->GetPosition() = vec3(1, 1, 1);
  Scene::Instance()->AddEntity(directionalLight.UpCast<Entity>());

  while (!Screen::Instance()->ShouldClose() && !Screen::Instance()->IsKeyPressed(GLFW_KEY_ESCAPE)) {

    angle += 2 * Screen::Instance()->GetElapsed();
    tetera->GetRotation() = glm::angleAxis<float>(angle, vec3(0, 1, 0));

    Scene::Instance()->Update(Screen::Instance()->GetElapsed());
    Scene::Instance()->Render();

    Screen::Instance()->Refresh();
    Screen::Instance()->SetTitle(Renderer::Instance()->GetProgramError());
  }
}

void Practica3()
{
  if (FULLSCREEN)
    Screen::Instance()->Open(Screen::Instance()->GetDesktopWidth(), Screen::Instance()->GetDesktopHeight(), true);
  else
    Screen::Instance()->Open(800, 600, false);

  Scene::Instance()->SetAmbient(vec3(0.2, 0.2, 0.2));

  double angle = 0;
  Ptr<Mesh> room = ResourceManager::Instance()->LoadMesh("data/room.msh");
  Ptr<Model> sala = Model::Create(room);
  sala->GetPosition() = vec3(0, 0, 0);
  Scene::Instance()->AddEntity(sala.UpCast<Entity>());

  Ptr<Camera> mainCamera = Camera::Create();
  mainCamera->GetRotation() = quat(glm::radians(vec3(-30.0f, 180.0f, 0.0f)));
  mainCamera->GetPosition() = vec3(0, 8, -12);
  mainCamera->SetColor(vec3(0, 0, 0));
  mainCamera->SetProjection(glm::perspective<float>(1.7f, (float)Screen::Instance()->GetWidth() / Screen::Instance()->GetHeight(), 1, 100));
  mainCamera->SetViewport(0, 0, Screen::Instance()->GetWidth(), Screen::Instance()->GetHeight());
  Scene::Instance()->AddEntity(mainCamera.UpCast<Entity>());

  Ptr<Light> directionalLight = Light::Create();
  directionalLight->SetColor(vec3(1, 1, 1));
  directionalLight->SetType(Light::DIRECTIONAL);
  Scene::Instance()->AddEntity(directionalLight.UpCast<Entity>());
  Scene::Instance()->EnableShadows(true);
  Scene::Instance()->SetDepthOrtho(-10, 10, -10, 10, 1, 100);

  while (!Screen::Instance()->ShouldClose() && !Screen::Instance()->IsKeyPressed(GLFW_KEY_ESCAPE)) {
    angle += 32.0f * Screen::Instance()->GetElapsed();
    directionalLight->GetPosition() = vec3(0, 0, 0);
    directionalLight->GetRotation() = quat(glm::radians(vec3(-30.0f, angle, 0.0f)));
    directionalLight->Move(vec3(0, 0, 1));
    Scene::Instance()->Update(Screen::Instance()->GetElapsed());
    Scene::Instance()->Render();

    Screen::Instance()->Refresh();
    Screen::Instance()->SetTitle(Renderer::Instance()->GetProgramError());
  }
}

void Practica4()
{
  if (FULLSCREEN)
    Screen::Instance()->Open(Screen::Instance()->GetDesktopWidth(), Screen::Instance()->GetDesktopHeight(), true);
  else
    Screen::Instance()->Open(800, 600, false);

  Scene::Instance()->SetAmbient(vec3(0.2, 0.2, 0.2));

  double angle = 0;
  Ptr<Mesh> room = ResourceManager::Instance()->LoadMesh("data/swat.msh");
  Ptr<Model> sala = Model::Create(room);
  sala->GetPosition() = vec3(0, 0, 0);
  Scene::Instance()->AddEntity(sala.UpCast<Entity>());

  Ptr<Camera> mainCamera = Camera::Create();
  mainCamera->GetRotation() = quat(glm::radians(vec3(-30.0f, 180.0f, 0.0f)));
  mainCamera->GetPosition() = vec3(0, 8, -12);
  mainCamera->SetColor(vec3(1, 1, 1));
  mainCamera->SetProjection(glm::perspective<float>(1.7f, (float)Screen::Instance()->GetWidth() / Screen::Instance()->GetHeight(), 1, 100));
  mainCamera->SetViewport(0, 0, Screen::Instance()->GetWidth(), Screen::Instance()->GetHeight());
  Scene::Instance()->AddEntity(mainCamera.UpCast<Entity>());

  Ptr<Light> directionalLight = Light::Create();
  directionalLight->SetColor(vec3(1, 1, 1));
  directionalLight->SetType(Light::DIRECTIONAL);
  Scene::Instance()->AddEntity(directionalLight.UpCast<Entity>());
  Scene::Instance()->EnableShadows(true);
  Scene::Instance()->SetDepthOrtho(-10, 10, -10, 10, 1, 100);

  while (!Screen::Instance()->ShouldClose() && !Screen::Instance()->IsKeyPressed(GLFW_KEY_ESCAPE)) {
    angle += 32.0f * Screen::Instance()->GetElapsed();
    directionalLight->GetPosition() = vec3(0, 0, 0);
    directionalLight->GetRotation() = quat(glm::radians(vec3(-30.0f, angle, 0.0f)));
    directionalLight->Move(vec3(0, 0, 1));
    Scene::Instance()->Update(Screen::Instance()->GetElapsed());
    Scene::Instance()->Render();

    Screen::Instance()->Refresh();
    Screen::Instance()->SetTitle(Renderer::Instance()->GetProgramError());
  }
}


