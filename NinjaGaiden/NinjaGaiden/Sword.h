#ifndef _SWORD_H_
#define _SWORD_H_

#include "DynamicObject.h"

class Sword : public DynamicObject
{
	int _timeSpawn;
public:
	Sword(void);
	Sword(float x, float y, float _huong, EnumID id);
	void Update(int dt);
	void Draw(CCamera* camera);
	~Sword(void);
};

#endif