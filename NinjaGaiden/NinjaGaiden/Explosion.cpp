#include "Explosion.h"


Explosion::Explosion(void) : DynamicObject()
{
}

Explosion::Explosion(float x, float y, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	active = false;
}

void Explosion::Update(int dt)
{
	_timeSpawn += dt;
	if (_timeSpawn >= 70)
	{
		active = false;
		_timeSpawn = 0;
	}
}

Explosion::~Explosion(void)
{
}
