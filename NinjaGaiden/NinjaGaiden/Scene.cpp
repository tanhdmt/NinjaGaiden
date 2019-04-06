#include "Scene.h"


Scene::Scene(ESceneState state)
{
	background = NULL;
	camera = NULL;
	sceneState = state;
}

void Scene::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
}

void Scene::ProcessInput(int keycode)
{
}

void Scene::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
}

void Scene::OnKeyDown(int KeyCode)
{
}

void Scene::OnKeyUp(int KeyCode)
{
}

Scene::~Scene(void)
{
}
