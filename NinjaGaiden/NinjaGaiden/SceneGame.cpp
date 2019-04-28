#include "SceneGame.h"

SceneGame::SceneGame(void) : Scene(ESceneState::Game_Scene)
{
	camera = new CCamera();
	bg = NULL;
	_levelNow = 1;
	_loadLevel = false;
}

void SceneGame::LoadLevel(int level)
{
	ResetLevel();
	switch (level)
	{
	case 1:
	{
		camera->viewport.y = 416;
		//camera->viewport.x = 1023;
		bg = new Background(level);
		ryu = new Ryu(3800, 400);
	}
	break;
	case 2:
	{
		camera->viewport.y = 416;
		//camera->viewport.x = 1023;
		bg = new Background(level);
		//ryu->_action = Action::Idle;
		ryu = new Ryu(50, 300);
	}
	break;
	default:
		break;
	}
}

void SceneGame::LoadStage(int level)
{
	switch (level)
	{
	case 1:
	{
		qGameObject = new QGameObject("Resources\\Maps\\Stage3.1-GameObj.txt");
	}
	break;
	case 2:
	{
		qGameObject = new QGameObject("Resources\\Maps\\Stage3.2-GameObj.txt");
	}
	break;
	}
	camera->SetSizeMap(bg->getWidth(), 0);
}

void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int deltaTime)
{
	if (_levelNow > 0)
	{
		if (ryu->posX > bg->getWidth() - 100 && !_loadLevel) 
		{
			_levelNow++;
			LoadResources(G_Device);
			ryu->sprite->SelectIndex(0);
			ryu->_action = Action::Idle;
			_loadLevel = true;
		}
		qGameObject->Update(deltaTime);
		qGameObject->Update(deltaTime, ryu->getPos());
		ryu->Collision(*(qGameObject->_staticObject), deltaTime);
		//samus->Collision(*(qGameObject->_dynamicObject), deltaTime);

		qGameObject->Collision(deltaTime);

		G_SpriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		ryu->Update(deltaTime);
		camera->UpdateCamera(ryu->posX);

		bg->Draw(camera);
		qGameObject->Draw(camera);
		ryu->Draw(camera);

		G_SpriteHandler->End();

		//render info
		arial->onLost();
		//arial->render("viewport x - y: ", 10, 10);
		arial->render(camera->viewport.x, 10, 10);
		arial->render(camera->viewport.y, 70, 10);
		arial->render(ryu->posX, 130, 10);
		arial->render(ryu->posY, 190, 10);
		arial->render(1000 / deltaTime, 490, 10);
	}
}

void SceneGame::ProcessInput(int keyCode)
{
	switch (keyCode)
	{
	case DIK_RIGHT:
	case DIK_D:
		ryu->TurnRight();
		break;
	case DIK_LEFT:
	case DIK_A:
		ryu->TurnLeft();
		break;

	default:
		ryu->Stop();
		break;
	}
}


void SceneGame::LoadResources(LPDIRECT3DDEVICE9 d3ddv)
{
	srand((unsigned)time(NULL));

	D3DXCreateSprite(d3ddv, &G_SpriteHandler);

	HRESULT res = D3DXCreateSprite(d3ddv, &G_SpriteHandler);
	arial = new CText(d3ddv, 22, G_ScreenWidth, G_ScreenHeight);

	if (_levelNow != 0)
	{
		LoadLevel(_levelNow);
		LoadStage(_levelNow);
	}
}

void SceneGame::OnKeyDown(int KeyCode)
{
	switch (KeyCode)
	{
	case DIK_J:
		ryu->Jump();
		break;
	case DIK_K:
		ryu->Attack();
		break;
	}
}

SceneGame::~SceneGame(void)
{
	if (camera != NULL)
		delete camera;
}
void SceneGame::ResetLevel()
{
	if (bg != NULL)
		delete bg;
	if (qGameObject != NULL)
		delete qGameObject;
}