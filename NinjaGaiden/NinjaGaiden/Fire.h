#ifndef _FIRE_H_
#define _FIRE_H_

#include "DynamicObject.h"

class Fire : public DynamicObject
{
	int _timeSpawn;
public:
	Fire(void);
	Fire(float x, float y, float _huong, EnumID id);
	void Update(int dt);
	~Fire(void);
};

#endif