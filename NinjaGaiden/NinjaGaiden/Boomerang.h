#ifndef _BOOMERANG_H_
#define _BOOMERANG_H_

#include "DynamicObject.h"

class Boomerang : public DynamicObject
{
	float _length;
	int _timeSpawn;
public:
	Boomerang(void);
	Boomerang(float x, float y, float _huong, EnumID id);
	void Update(int dt);
	void Collision(Box simonBox);
	~Boomerang(void);
};

#endif