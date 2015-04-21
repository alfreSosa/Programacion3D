#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#include "../include/u-gine.h"
#define FULLSCREEN false

int main() {
	if ( FULLSCREEN )
    Screen::Instance()->Open(Screen::Instance()->GetDesktopWidth(), Screen::Instance()->GetDesktopHeight(), true);
	else			
    Screen::Instance()->Open(800, 600, false);

  Ptr<Mesh> caja = ResourceManager::Instance()->LoadMesh("data/box.msh");
  Ptr<Camera> mainCamera = Camera::Create();

  Scene::Instance()->AddEntity(mainCamera.UpCast<Entity>());

	while ( !Screen::Instance()->ShouldClose() && !Screen::Instance()->IsKeyPressed(GLFW_KEY_ESCAPE) ) {
		Scene::Instance()->Update(Screen::Instance()->GetElapsed());
		Scene::Instance()->Render();

		Screen::Instance()->Refresh();
		Screen::Instance()->SetTitle(Renderer::Instance()->GetProgramError());
	}
  

	return 0;
}
