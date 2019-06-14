#include "Items.h"

#define SPEED_Y 0.5f

Items::Items(void)
{
}

Items::Items(float x, float y, EnumID id) : DynamicObject(x, y, 0, -SPEED_Y, id)
{
	active = true;
	_timeSpawn = 0;
	ryuScore = 0;
	ryuHp = 0;
	ryuSpiri = 0;
	ryuFreeze = false;
	weaponID = EnumID::None_ID;
}

void Items::Update(int dt)
{
	if (!active)
		return;
	//posX += vX * dt;
	
	if (vY == 0)
	{
		_timeSpawn += dt;
		if (_timeSpawn >= 350)
			active = false;
	}
	else
	{
		_timeSpawn += dt;
		if (_timeSpawn >= 100)
			posY += vY * dt;
	}
	//sprite->Update(dt);
}
void Items::Collision(list<GameObject*> &obj, int dt)
{
	
}

void Items::Collision(Box ryuBox, list<GameObject*> &obj, int dt)
{
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
			case EnumID::Ground1_ID:
				//xet cham dat
				if (vY < 0 && dir == ECollisionDirect::Colls_Bot)
				{
					vY = 0;
					_timeSpawn = 0;
				}
				break;
			}
		}
	}
	float moveX;
	float moveY;

	Box box = this->GetBox();
	Box boxOther = ryuBox;

	if (AABB(box, boxOther, moveX, moveY) == true && _timeSpawn > 100)
	{
		switch (this->id)
		{
		case EnumID::BonusBlue_ID:
		{
			ryuScore += 500;
		}
		break;
		case EnumID::BonusRed_ID:
		{
			ryuScore += 1000;
		}
		break;
		case EnumID::ThrowStar_ID:
		{
			weaponID = EnumID::BoomerangS_ID;
		}
		break;
		case EnumID::WindmillThrowStar_ID:
		{
			weaponID = EnumID::Boomerang_ID;
		}
		break;
		case EnumID::TimeFreeze_ID:
		{
			ryuFreeze = true;
		}
		break;
		case EnumID::FireWheel_ID:
		{
			weaponID = EnumID::FireWeapon_ID;
		}
		break;
		case EnumID::SpititualBlue_ID:
		{
			ryuSpiri += 5;
		}
		break;
		case EnumID::SpiritualRed_ID:
		{
			ryuSpiri += 10;
		}
		break;
		case EnumID::RestoreStrength_ID:
		{
			ryuHp = 6;
		}
		break;
		default:
			break;
		}
		active = false;
	}
}

ECollisionDirect Items::GetCollisionDirect(GameObject* other)
{
	float x = (this->posX - (this->getWidth() / 2)) - (other->posX - (other->getWidth() / 2));
	float y = (this->posY + (this->getHeight() / 2)) - (other->posY + (other->getHeight() / 2));
	if (abs(x) > abs(y)) {
		if (x < 0)
			return ECollisionDirect::Colls_Left;
		else if (x > 0)
			return ECollisionDirect::Colls_Right;
	}
	else
	{
		if (y < 0)
			return ECollisionDirect::Colls_Top;
		else if (y > 0)
			return ECollisionDirect::Colls_Bot;
	}

	return ECollisionDirect::Colls_None;
}

Items::~Items(void)
{
}
