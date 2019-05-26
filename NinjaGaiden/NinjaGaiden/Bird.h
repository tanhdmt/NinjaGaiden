#pragma once
#ifndef _BIRD_H_
#define _BIRD_H_

#include "DynamicObject.h"
#include "CEnum.h"

class Bird : public DynamicObject
{
public:
	bool active;
	Bird(void);
	Bird(float x, float y);
	void Update(int dt);
	void Collision(list<GameObject*> obj, int dt) {}
	void SetActive(float x, float y);

	~Bird(void);
};
#endif
