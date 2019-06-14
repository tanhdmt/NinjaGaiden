#pragma once
#ifndef _RUNNER_H_
#define _RUNNER_H_
#include "DynamicObject.h"
#include "CEnum.h"

class Runner :public DynamicObject
{
public:
	bool hasAttack;
	bool active;

	GameObject* _lastCollidedGround;
	GameObject* _sideCollidedGround;
	ECollisionDirect _curCollideDir;

	Runner(void);
	Runner(float x, float y);
	void Update(int dt);
	//void Draw(CCamera* camera);
	void Collision(list<GameObject*> obj, int dt);
	ECollisionDirect GetCollisionDirect(GameObject* other);
	void SetActive(float x, float y);
	Box GetBox();

	~Runner(void);
};

#endif

