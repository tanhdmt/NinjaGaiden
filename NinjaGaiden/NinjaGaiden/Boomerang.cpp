#include "Boomerang.h"

#define MAX_WIDTH 150

Boomerang::Boomerang(void) : DynamicObject()
{
}

Boomerang::Boomerang(float x, float y, float _huong, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	_length = 0;
	_timeSpawn = 0;
}

void Boomerang::Update(int dt)
{
	if (_timeSpawn != 0 && _timeSpawn <= 150)
	{
		_timeSpawn += dt;
	}
	else
	{
		_length += vX * dt;
		posX += vX * dt;

		if (abs(_length) >= MAX_WIDTH && _timeSpawn == 0)
		{
			_timeSpawn += dt;
			vX = -vX;
		}
	}
	sprite->Update(dt);
}

void Boomerang::Collision(Box ryu)
{
	if (_timeSpawn != 0)
	{
		float moveX;
		float moveY;

		Box box = this->GetBox();
		Box boxOther = ryu;

		if (AABB(box, boxOther, moveX, moveY) == true)
		{
			active = false;
			return;
		}
	}
}

Boomerang::~Boomerang(void)
{
}
