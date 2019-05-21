#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#include "DynamicObject.h"

class Explosion : public DynamicObject
{
	int _timeSpawn;
public:
	Explosion(void);
	Explosion(float x, float y, EnumID id);
	void Update(int dt);
	~Explosion(void);
};

#endif