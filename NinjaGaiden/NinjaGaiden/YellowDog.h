#pragma once
#ifndef _YELLOWDOG_H_
#define _YELLOWDOG_H_
#include "DynamicObject.h"
#include "CEnum.h"

class YellowDog: public DynamicObject
{
public:
	bool hasAttack;
	bool active;


	YellowDog(void);
	YellowDog(float x, float y);
	void Update(int dt);
	//void Draw(CCamera* camera);
	void Collision(list<GameObject*> obj, int dt);
	ECollisionDirect GetCollisionDirect(GameObject* other);
	void SetActive(float x, float y);

	~YellowDog(void);
};
#endif
