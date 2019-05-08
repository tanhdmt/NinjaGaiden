#ifndef _BULLET_H_
#define _BULLET_H_

#include "DynamicObject.h"
#include "Fire.h"

class Bullet : public DynamicObject
{
	int _timeSpawn;
public:
	Fire* fire;
	Bullet(void);
	Bullet(float x, float y, float _huong, EnumID id);
	void Update(int dt);
	void Draw(CCamera* camera);
	~Bullet(void);
};

#endif