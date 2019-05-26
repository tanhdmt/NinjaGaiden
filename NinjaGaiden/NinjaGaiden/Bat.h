#pragma once
#ifndef _BAT_H_
#define _BAT_H_

#include "DynamicObject.h"
#include "CEnum.h"

class Bat :public DynamicObject
{
public:
	bool active;
	Bat(void);
	Bat(float x, float y);
	void Update(int dt);
	void SetActive(float x, float y);

	~Bat(void);
};
#endif

