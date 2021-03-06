#include "FireWeapon.h"

#define SPEED_X 0.4f

FireWeapon::FireWeapon(void) : DynamicObject()
{
}

FireWeapon::FireWeapon(float x, float y, float _huong, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	if (_huong > 0)
		vX = SPEED_X;
	else
	{
		vX = -SPEED_X;
	}
	active = true;
	_timeSpawn = 0;
}

void FireWeapon::Update(int dt)
{
	_timeSpawn += dt;
	posX += vX * dt;
	if (_timeSpawn >= 1000)
		active = false;
}

void FireWeapon::Draw(CCamera* camera)
{
	if (sprite == NULL || IsHurt()) {
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX < 0)
	{
		sprite->DrawFlipX(center.x, center.y);
	}
	else
	{
		sprite->Draw(center.x, center.y);
	}
}


FireWeapon::~FireWeapon(void)
{
}
