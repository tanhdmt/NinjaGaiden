#pragma once
#ifndef _BANSHEE_H_
#define _BANSHEE_H_

#include "DynamicObject.h"
#include "CEnum.h"
#include "Sword.h"

class Banshee : public DynamicObject
{
public:
	bool hasAttack;
	bool active;	
	

	GameObject* _lastCollidedGround;
	GameObject* _sideCollidedGround;
	ECollisionDirect _curCollideDir;
	list<Sword*> * sword;


	Banshee(void);
	Banshee(float x, float y);
	void Update(int dt);
	//void Draw(CCamera* camera);
	void Collision(list<GameObject*> obj, int dt);
	ECollisionDirect GetCollisionDirect(GameObject* other);
	void SetActive(float x, float y);
	Box GetBox();

	~Banshee(void);
};
#endif
