#pragma once
#ifndef _SCENE1_H_
#define _SCENE1_H_

#include "Background.h"
#include "Scene.h"
#include "Ryu.h"
#include "CText.h"
#include "QGameObject.h"
#include "GameScore.h"
#include "Grid.h"
using namespace std;

class SceneGame : public Scene
{
public:
	int _levelNow;
	int _stageNow;

	int _score;
	int _lifes;

	bool _loadLevel;

	SceneGame();
	~SceneGame();
protected:

	Background *bg;
	Ryu* ryu;
	QGameObject* qGameObject;
	GameScore* _gameScore;
	Grid* grid;

	CCamera *camera;
	CText* arial;

	void LoadLevel(int level);
	void LoadStage(int level);
	void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	void ProcessInput(int keyCode);
	void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	void OnKeyDown(int KeyCode);
	void ResetLevel();
};
#endif

#pragma once