
#include "SceneMain.h"

SceneMain::SceneMain(int _nCmdShow) : CGame(_nCmdShow)
{
	/*sceneNow = new SceneMenu();
	currentStateScene = ESceneState::Menu_Scene;*/
	sceneNow = new SceneGame();
}

void SceneMain::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t)
{
	if (sceneNow->sceneState != currentStateScene)
	{
		switch (sceneNow->sceneState)
		{
		case ESceneState::Game_Scene:
			sceneNow = new SceneGame();
			sceneNow->LoadResources(d3ddv);
			break;
			/*case ESceneState::Menu_Scene:
				sceneNow = new SceneMenu();
				sceneNow->LoadResources(d3ddv);
				break;*/
				/*case ESceneState::EndGame_Scene:
				sceneNow = new EndGameScene();
				sceneNow->LoadResources(d3ddv);
				break;*/
		}
		currentStateScene = sceneNow->sceneState;
	}
	sceneNow->RenderFrame(d3ddv, t);
}

void SceneMain::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int Delta)
{
	if (currentStateScene == ESceneState::Game_Scene)
	{
		if (IsKeyDown(DIK_RIGHT) || IsKeyDown(DIK_D))
		{
			sceneNow->ProcessInput(DIK_RIGHT);
		}
		else if (IsKeyDown(DIK_LEFT) || IsKeyDown(DIK_A))
		{
			sceneNow->ProcessInput(DIK_LEFT);
		}
		else if (IsKeyDown(DIK_DOWN) || IsKeyDown(DIK_S))
		{
			sceneNow->ProcessInput(DIK_DOWN);
		}
		else if (IsKeyDown(DIK_UP) || IsKeyDown(DIK_W))
		{
			sceneNow->ProcessInput(DIK_UP);
		}
		else if (IsKeyDown(DIK_Q))
		{
			sceneNow->ProcessInput(DIK_Q);
		}
		else if (IsKeyDown(DIK_SPACE))
		{
			sceneNow->ProcessInput(DIK_SPACE);
		}
		else
		{
			sceneNow->ProcessInput(DIK_0);
		}
	}
}

void SceneMain::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	sceneNow->LoadResources(d3ddv);
}

void SceneMain::OnKeyDown(int KeyCode)
{
	sceneNow->OnKeyDown(KeyCode);
}

SceneMain::~SceneMain(void)
{
}
