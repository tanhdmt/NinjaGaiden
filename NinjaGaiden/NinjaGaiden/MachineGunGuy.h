#pragma once
#ifndef _MACHINEGUNGUY_H_
#define _MACHINEGUNGUY_H_

#include "DynamicObject.h"
#include "CEnum.h"
class MachineGunGuy:public DynamicObject
{
public:
	bool hasAttack;
	bool active;

	GameObject* _lastCollidedGround;
	GameObject* _sideCollidedGround;
	ECollisionDirect _curCollideDir;

	MachineGunGuy(void);
	MachineGunGuy(float x, float y);
	void Update(int dt);
	//void Draw(CCamera* camera);
	void Collision(list<GameObject*> obj, int dt);
	ECollisionDirect GetCollisionDirect(GameObject* other);
	void SetActive(float x, float y);
	Box GetBox();

	~MachineGunGuy(void);
};

#endif