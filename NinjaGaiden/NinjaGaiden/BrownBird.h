#pragma once
#ifndef _BROWNBIRD_H_
#define _BROWNBIRD_H_

#include "DynamicObject.h"
#include "CEnum.h"

class BrownBird:public DynamicObject
{
public:
	bool hasAttack;
	bool active;


	BrownBird(void);
	BrownBird(float x, float y);
	void Update(int dt);
	void Update(int dt, D3DXVECTOR2 * ryupos);
	//void Draw(CCamera* camera);
	void Collision(list<GameObject*> obj, int dt);
	void SetActive(float x, float y);

	~BrownBird(void);
};

#endif

