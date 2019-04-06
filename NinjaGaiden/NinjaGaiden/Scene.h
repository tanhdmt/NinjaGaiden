#ifndef _SCENE_H_
#define _SCENE_H_

#include <d3dx9.h>
#include <time.h>
#include "Global.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <sstream>
#include "Camera.h"
//#include "SoundManager.h"
#include "Game.h"
#include "CEnum.h"

class Scene
{
public:
	LPDIRECT3DSURFACE9 background;
	CCamera* camera;
	ESceneState sceneState;

	Scene(ESceneState);
	ESceneState GetSceneState();
	virtual void RenderFrame(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void ProcessInput(int keyCode);
	virtual void LoadResources(LPDIRECT3DDEVICE9 d3ddv);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
	~Scene(void);
};

#endif