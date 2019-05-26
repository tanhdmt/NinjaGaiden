#pragma once
#ifndef _BUTTERFLY_H_
#define _BUTTERFLY_H_

#include "DynamicObject.h"
#include "CEnum.h"
class Butterfly : public DynamicObject
{
public:
	bool active;
	Butterfly(void);
	Butterfly(float x, float y);
	void Update(int dt);
	void Collision(list<GameObject*> obj, int dt){}
	void SetActive(float x, float y);

	~Butterfly(void);
};
#endif

