#include "Boomerang.h"

#define MAX_WIDTH 180

Boomerang::Boomerang(void) : Weapon()
{
}

Boomerang::Boomerang(float x, float y, float _huong) : Weapon(x, y, _huong, EnumID::Boomerang_ID)
{
	_length = 0;
	_timeSpawn = 0;
	count = 0;
	rad = 0;
}

void Boomerang::Update(int dt)
{
	_length += vX * dt;
	posX += (vX + ryuX) * dt;
	posY -= ryuY * dt;
	rad+=30;

	if (abs(_length) >= MAX_WIDTH && count < 5)
	{
		vX = -vX;
		rad += 30;
		count++;
	}
}

void Boomerang::Collision(Box ryu)
{
	ryuX = ryu.vx;
	ryuY = ryu.vy;

	float moveX;
	float moveY;

	Box box = this->GetBox();
	Box boxOther = ryu;

	if (AABB(box, boxOther, moveX, moveY) == true)
	{
		if (count > 4) {
			active = false;
			return;
		}
	}
}

void Boomerang::Draw(CCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	/*if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}*/
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	/*if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);*/
	sprite->DrawRotate(center.x, center.y, rad);
}

Boomerang::~Boomerang(void)
{
}
