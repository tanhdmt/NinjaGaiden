#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include "SweptAABB.h"
#include "Sprite.h"
#include "Camera.h"
#include "Singleton.h"
#include <list>
using namespace std;


class GameObject
{
public:
	float posX, posY;
	float vX, vY;
	LPDIRECT3DTEXTURE9 texture;
	CSprite* sprite;
	int width;
	int height;
	EnumID id;
	bool active;
	ObjectType type;
	bool canMove;

	virtual void Update(int dt);
	virtual void Update(int dt, D3DXVECTOR2* ryuPos);
	virtual void Draw(CCamera*);
	virtual void ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t);
	virtual void OnKeyDown(int KeyCode);
	virtual void CreateSprite();
	virtual void Collision(list<GameObject*> obj, int dt);
	ECollisionDirect GetCollisionDirect(float normalx, float normaly);
	virtual ECollisionDirect GetCollisionDirect(GameObject* other);
	virtual Box GetBox();
	virtual void SetActive(float x, float y);
	virtual void SetActive();
	virtual void Remove();
	virtual void ReceiveDamage(int damagePoint);

	GameObject(void);
	GameObject(float posX, float posY, EnumID id);
	~GameObject(void);
};
