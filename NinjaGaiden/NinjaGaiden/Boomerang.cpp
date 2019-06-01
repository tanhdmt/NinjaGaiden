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
	//posY -= ryuY * dt;
	rad+=30;

	if (abs(_length) >= MAX_WIDTH && count < 5)
	{
		vX = -vX;
		rad += 30;
		count++;
	}
	if (explosion->active)
		explosion->Update(dt);
}

void Boomerang::Collision(Box ryuBox, list<GameObject*> &obj, int dt)
{
	ryuX = ryuBox.vx;
	ryuY = ryuBox.vy;

	float moveX;
	float moveY;

	Box box = this->GetBox();
	Box boxOther = ryuBox;

	if (AABB(box, boxOther, moveX, moveY) == true)
	{
		if (count > 4) {
			active = false;
			return;
		}
	}
	int countCollis = 0;
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		float moveX;
		float moveY;
		float normalx;
		float normaly;
		GameObject* other = (*_itBegin);
		Box box = this->GetBox();
		Box boxOther = other->GetBox();

		if (AABB(box, boxOther, moveX, moveY) == true)
		{
			ECollisionDirect dir = this->GetCollisionDirect(other);
			switch (other->id)
			{
			case EnumID::SwordMan_ID:
			case EnumID::RocketMan_ID:
			case EnumID::YellowDog_ID:
			{
				if (other->active)
				{
					int enemyPosX = other->getX();
					int enemyPosY = other->getY();
					other->active = false;
					explosion->setX(enemyPosX);
					explosion->setY(enemyPosY);
					explosion->active = true;
				}
			}
			break;
			}
		}
	}
	if (countCollis == 0)
	{
		vX = -vX;
	}
}

void Boomerang::Draw(CCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	if (explosion->active)
		explosion->Draw(camera);
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
