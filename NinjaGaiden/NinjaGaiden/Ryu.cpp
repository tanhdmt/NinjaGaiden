#include "Ryu.h"

#define SPEED_X 0.5f
#define SPEED_Y 1.0f
bool isCol = false;

Ryu::Ryu(void) : DynamicObject() {

}

Ryu::Ryu(int _posX, int _posY) : DynamicObject(_posX, _posY, 0, -SPEED_Y, EnumID::Ryu_ID) 
{
	_action = Action::Idle;
	_vLast = 0.2f;
	_lastCollidedGround = nullptr;
	ryuRun = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuRun_ID), 0, 2, 18);
	Initialize();
}

void Ryu::Update(int dt) {
	switch (_action)
	{
		case Action::Run_Left:
		case Action::Run_Right:
			ryuRun->Update(dt);
			break;
	}
	posX += vX * dt;
	posY += vY * dt;
}

Box Ryu::GetBox()
{
	return Box(posX - width / 2 , (posY + height / 2) + 4, width, height);
}

void Ryu::Collision(list<GameObject*> &obj, float dt)
{
	for (list<GameObject*>::iterator _itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);

		float moveX;
		float moveY;

		Box boxRyu = this->GetBox();
		Box boxOther = other->GetBox();

		if (AABB(boxRyu, boxOther, moveX, moveY) == true)
		{
			switch (other->id)
			{
			case EnumID::Ground1_ID:
			{
				//xet cham dat
				if (vY < 0)
				{
					vY = 0;
				}
				/*if (vX != 0 && moveX != 0)
				{
					posX += moveX;
				}*/
				break;
			}
			default:
				break;
			}
		}
		else
		{
			/*float normalx, normaly;
			Box boardphasebox = GetSweptBroadphaseBox(boxRyu, dt);
			if (AABBCheck(GetSweptBroadphaseBox(boxRyu, dt), boxOther) == true)
			{
				float collisiontime = SweptAABB(boxRyu, boxOther, normalx, normaly, dt);

			}*/
		}
	}
}

void Ryu::Draw(CCamera* camera) {
	D3DXVECTOR2 center = camera->Transform(posX, posY);

	if (vX != 0) 
	{
		if (_vLast > 0)
		{
			ryuRun->Draw(center.x, center.y);
		}
		else {
			ryuRun->DrawFlipX(center.x, center.y);
		}
	}
	else
	{
		if (_vLast > 0)
		{
			sprite->Draw(center.x, center.y);
		}
		else {
			sprite->DrawFlipX(center.x, center.y);
		}
	}
	
}

void Ryu::TurnLeft()
{
	vX = -SPEED_X;
	_vLast = vX;
	_action = Action::Run_Left;
}

void Ryu::TurnRight() 
{
	vX = SPEED_X;
	_vLast = vX;
	_action = Action::Run_Right;
}

void Ryu::Initialize()
{
	sprite->SelectIndex(0);
}

void Ryu::Stop()
{
	vX = 0;
	_action = Action::Idle;

}

ECollisionDirect Ryu::GetCollisionDirect(GameObject* other)
{
	return ECollisionDirect::Colls_None;
}

D3DXVECTOR2* Ryu::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}

Ryu::~Ryu(void)
{

}