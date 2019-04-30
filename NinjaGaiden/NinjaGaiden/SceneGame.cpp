#include "SceneGame.h"

SceneGame::SceneGame(void) : Scene(ESceneState::Game_Scene)
{
	camera = new CCamera();
	bg = NULL;
	_gameScore = NULL;
	_levelNow = 1;
	_loadLevel = false;
	_score = 0;
	_lifes = 3;
}

void SceneGame::LoadLevel(int level)
{
	ResetLevel();
	switch (level)
	{
	case 1:
	{
		camera->viewport.y = 420;
		//camera->viewport.x = 1023;
		bg = new Background(level);
		ryu = new Ryu(50, 400);
		_gameScore->initTimer(150);
	}
	break;
	case 2:
	{
		camera->viewport.y = 420;
		//camera->viewport.x = 1023;
		bg = new Background(level);
		//ryu->_action = Action::Idle;
		ryu = new Ryu(2085, 300);
		_gameScore->initTimer(150);
	}
	break;
	case 3:
	{
		camera->viewport.y = 420;
		//camera->viewport.x = 1023;
		bg = new Background(level);
		//ryu->_action = Action::Idle;
		ryu = new Ryu(100, 300);
		_gameScore->initTimer(150);
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
	case 3:
	{
		qGameObject = new QGameObject("Resources\\Maps\\Stage3.3-GameObj.txt");
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
		//Xu ly scene
		//--------------Over time-------------------
		//if (_gameScore->getTimer() <= 0)
			//sceneState = ESceneState::Menu_Scene;
		_gameScore->updateScore(_levelNow, _score, deltaTime, 16, _lifes, EnumID::None_ID, 0, 16);

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
		_gameScore->drawTable();
		G_SpriteHandler->End();
		_gameScore->drawScore();
		//render info
		/*arial->onLost();
		arial->render((char*)"viewport x - y: ", 10, 10);
		arial->render(camera->viewport.x, 10, 10);
		arial->render(camera->viewport.y, 70, 10);
		arial->render(ryu->posX, 130, 10);
		arial->render(ryu->posY, 190, 10);
		arial->render(1000 / deltaTime, 490, 10);*/
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
	case DIK_UP:
	case DIK_W:
		ryu->Climb(true);
		break;
	case DIK_DOWN:
	case DIK_S:
		ryu->Climb(false);
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
	_gameScore = new GameScore(G_Device, 24, G_ScreenWidth, G_ScreenHeight);

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
	case DIK_L:
		ryu->Sit();
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