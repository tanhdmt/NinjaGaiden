#pragma once
#ifndef _BOSSBULLET_H_
#define _BOSSBULLET_H_
#include "DynamicObject.h"
#include "Fire.h"
#include "Explosion.h"

class BossBullet:public DynamicObject
{
public:
	Fire* fire;
	Explosion* explosion;
	float startX;
	float startY;
	bool ryuHurt;
	BossBullet(void);
	BossBullet(float x, float y, float _huong, EnumID id);
	void Update(int dt );
	void Collision(GameObject* obj, GameObject* ryu, int dt);
	void Draw(CCamera* camera);
	void SetActive();
	void Reset(int dt);
	Box GetBox();
	~BossBullet(void);
};
#endif
