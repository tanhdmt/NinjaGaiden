#include "Fire.h"


Fire::Fire(void) : DynamicObject()
{
}

Fire::Fire(float x, float y, float _huong, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	if (_huong > 0)
		vX = 1;
	else
	{
		vX = -1;
	}
	active = true;
}

void Fire::Update(int dt)
{
	_timeSpawn += dt;
	if (_timeSpawn >= 60)
		active = false;
}

Fire::~Fire(void)
{
}
