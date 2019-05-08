#include "Bullet.h"

#define SPEED_X 0.4f

Bullet::Bullet(void) : DynamicObject()
{
}

Bullet::Bullet(float x, float y, float _huong, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	if (_huong > 0)
		vX = SPEED_X;
	else
	{
		vX = -SPEED_X;
	}
	active = true;
	_timeSpawn = 0;
	fire = new Fire(posX, posY, vX, EnumID::Fire_ID);
}

void Bullet::Update(int dt)
{
	_timeSpawn += dt;
	posX += vX * dt;
	if (_timeSpawn >= 1000)
		active = false;
	fire->Update(dt);
}

void Bullet::Draw(CCamera* camera)
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
	fire->Draw(camera);
}


Bullet::~Bullet(void)
{
}
