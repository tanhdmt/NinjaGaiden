#pragma once
#ifndef _BOSSBULLET_H_
#define _BOSSBULLET_H_
#include "DynamicObject.h"
#include "Fire.h"

class BossBullet:public DynamicObject
{
public:
	Fire* fire;
	float startX;
	float startY;
	BossBullet(void);
	BossBullet(float x, float y, float _huong, EnumID id);
	void Update(int dt );
	void Collision(GameObject* obj, int dt);
	void Draw(CCamera* camera);
	void SetActive();
	void Reset();
	~BossBullet(void);
};
#endif
