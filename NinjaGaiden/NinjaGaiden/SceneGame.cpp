#include "SceneGame.h"

SceneGame::SceneGame(void) : Scene(ESceneState::Game_Scene)
{
	camera = new CCamera();
	bg = NULL;
	_levelNow = 1;
}

void SceneGame::LoadLevel(int level)
{
	camera->viewport.y = 416;
	//camera->viewport.x = 1023;

	bg = new Background(level);

	ryu = new Ryu(50, 400);
}

void SceneGame::LoadStage()
{
	qGameObject = new QGameObject("Resources\\Maps\\Stage3.1-GameObj.txt");
	camera->SetSizeMap(G_MaxSize, G_MinSize);
}

void SceneGame::RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int deltaTime)
{
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

	LoadLevel(_levelNow);
	LoadStage();

}

void SceneGame::OnKeyDown(int KeyCode)
{
	/*switch (KeyCode)
	{
	case DIK_X:
		samus->Jump();
		break;
	case DIK_DOWN:
	case DIK_S:
		samus->Roll();
		break;
	case DIK_Z:
		samus->Shot();
		break;
	}*/
}

SceneGame::~SceneGame(void)
{
	if (camera != NULL)
		delete camera;
}
