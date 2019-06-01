#include "Weapon.h"

#define SPEED_X 0.8f

Weapon::Weapon(void)
{
}

Weapon::Weapon(float x, float y, float _huong, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	if (_huong > 0)
		vX = SPEED_X;
	else
	{
		vX = -SPEED_X;
	}
	explosion = new Explosion(x, y, EnumID::Explosion_ID);
	active = true;
}

void Weapon::Draw(CCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void Weapon::Update(int dt)
{
	if (sprite == NULL || !active)
		return;
	posX += vX * dt;
	posY += vY * dt;
	//sprite->Update(dt);
}
void Weapon::Collision(list<GameObject*> &obj, int dt)
{
	list<GameObject*>::reverse_iterator _itBegin;
	//for (_itBegin = obj.rbegin(); _itBegin != obj.rend(); _itBegin++)
	//{
	//	GameObject* other = (*_itBegin);
	//	if (other->type == ObjectType::Item_Type
	//		|| other->id == EnumID::MagicalCrystal_ID || other->id == EnumID::StairDownLeft_ID
	//		|| other->id == EnumID::StairDownRight_ID || other->id == EnumID::StairUpLeft_ID
	//		|| other->id == EnumID::StairUpRight_ID || other->id == EnumID::MovingPlatform_ID
	//		|| other->id == EnumID::DoorDown_ID || other->id == EnumID::DoorUp_ID
	//		|| other->id == EnumID::DoorLeft_ID || other->id == EnumID::DoorRight_ID
	//		|| other->id == EnumID::CastleGate_ID || other->id == EnumID::StupidDoor_ID)
	//	{
	//	}
	//	else
	//	{
	//		float moveX;
	//		float moveY;

	//		Box box = this->GetBox();
	//		Box boxOther = other->GetBox();

	//		if (AABB(box, boxOther, moveX, moveY) == true)
	//		{
	//			if (other->id != EnumID::Brick_ID)
	//			{
	//				if (other->id == EnumID::QueenMedusa_ID)
	//				{
	//					QueenMedusa* qm = (QueenMedusa*)other;
	//					if (qm->_hasGetUp)
	//					{
	//						other->ReceiveDamage(damage);
	//						if (other->hp <= 0)
	//						{
	//							point += other->point;
	//						}
	//					}
	//					else
	//						qm->getUp();
	//				}
	//				else if (other->id == EnumID::PhantomBat_ID)
	//				{
	//					other->ReceiveDamage(damage);
	//					if (other->hp <= 0)
	//					{
	//						point += other->point;
	//					}
	//				}
	//				else
	//				{
	//					other->ReceiveDamage(damage);
	//					if (other->hp <= 0)
	//					{
	//						point += other->point;
	//						(*_itBegin) = new FireDie(other->posX, other->posY);
	//					}
	//				}
	//				SoundManager::GetInst()->PlaySoundEffect(ESoundEffect::ES_HitByWeapon);
	//			}
	//			if (id != EnumID::Axe_ID && id != EnumID::Boomerang_ID)
	//				active = false;
	//			return;
	//		}
	//	}
	//}
}

void Weapon::Collision(Box ryuBox, list<GameObject*> &obj, int dt)
{
}

Weapon::~Weapon(void)
{
}
