#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include "SweptAABB.h"
#include "Sprite.h"
#include "Singleton.h"
#include <list>
using namespace std;

class CCamera;

class GameObject
{
public:
	float posX, posY;
	float vX, vY;
	float initX, initY;
	LPDIRECT3DTEXTURE9 texture;
	CSprite* sprite;
	int width;
	int height;
	EnumID id;
	bool active;
	bool death;
	ObjectType type;
	bool canMove;
	int hp;

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
	virtual int getWidth();
	virtual int getHeight();
	virtual void setX(float x);
	virtual void setY(float y);
	virtual float getX();
	virtual float getY();
	virtual float getInitX();
	virtual float getInitY();

	float getLeft();
	float getRight();
	float getTop();
	float getBottom();

	virtual void SetActive(float x, float y);
	virtual void SetActive();
	virtual void Remove();
	virtual void ReceiveDamage(int damagePoint);
	virtual void onReborn();

	GameObject(void);
	GameObject(float posX, float posY, EnumID id);
	~GameObject(void);
};
