#include "Ryu.h"

#define SPEED_X 0.5f
#define SPEED_Y 0.8f
#define MAX_HEIGHT 150.0f
bool isCol = false;

Ryu::Ryu(void) : DynamicObject() {

}

Ryu::Ryu(int _posX, int _posY) : DynamicObject(_posX, _posY, 0, -SPEED_Y, EnumID::Ryu_ID) 
{
	_action = Action::Idle;
	_vLast = 0.2f;
	_lastCollidedGround = nullptr;
	_hasJump = false;
	_heightJump = 0.0f;
	onLand = false;
	ryuRun = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuRun_ID), 0, 2, 18);
	ryuJump = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuJump1_ID), 0, 3, 18);
	ryuClimb = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuClimb_ID), 0, 1, 18);
	Initialize();
}

void Ryu::Update(int dt) {
	switch (_action)
	{
		case Action::Run_Left:
		case Action::Run_Right:
			ryuRun->Update(dt);
			break;
		case Action::Jump1:
			ryuJump->Update(dt);
			break;
		case Action::Climb:
			ryuClimb->Update(dt);
			break;
	}
	posX += vX * dt;
	if (!onLand || _hasJump)
	{
		posY += vY * dt;

	}
	if (_hasJump) {
		ryuJump->Update(dt);
		_heightJump += vY * dt;
		if (_heightJump >= MAX_HEIGHT)
		{
			vY = -SPEED_Y;
		}
	}
	/*if (posY < -80)
	{
		_hasJump = true;

		posY = 200;
		vY = SPEED_Y;
	}*/
	
}

Box Ryu::GetBox()
{
	return Box(posX - width / 2 , (posY + height / 2), width, height);
}

void Ryu::Collision(list<GameObject*> &obj, float dt)
{
	int countCollis = 0;
	for (list<GameObject*>::iterator _itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		
		float moveX;
		float moveY;
		float normalx;
		float normaly;

		Box boxRyu = this->GetBox();
		Box boxOther = other->GetBox();

		if (AABB(boxRyu, boxOther, moveX, moveY) == true)
		{
			float collisiontime = SweptAABB(boxRyu, boxOther, normalx, normaly, dt);
			switch (other->id)
			{
			case EnumID::Ground1_ID:
			{
				countCollis++;
				ECollisionDirect dir = this->GetCollisionDirect(other);
				//va cham canh
				if (dir == ECollisionDirect::Colls_Left || dir == ECollisionDirect::Colls_Right)
				{
					vX = 0;
					if (dir == ECollisionDirect::Colls_Right && _action == Action::Run_Right)
					{
						vX = SPEED_X;
					}
					else if (dir == ECollisionDirect::Colls_Left && _action == Action::Run_Left)
					{
						vX = -SPEED_X;
					}
				}
				//va cham tren
				else if (dir == ECollisionDirect::Colls_Top)
				{
					vY = -(SPEED_Y);
					onLand = false;
				}
				//xet cham dat
				if (vY < 0 && !onLand && dir == ECollisionDirect::Colls_Bot)
				{
					//posY += moveY;
					onLand = true;
					_hasJump = false;
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
		}
	}
	if (countCollis == 0 && onLand == true)
	{
		onLand = false;
	}
}

void Ryu::Draw(CCamera* camera) {
	D3DXVECTOR2 center = camera->Transform(posX, posY);

	if (vX != 0 || vY > 0) 
	{
		if (_vLast > 0)
		{
			if (_hasJump)
			{
				ryuJump->Draw(center.x, center.y);
				return;
			}
			ryuRun->Draw(center.x, center.y);
		}
		else {
			if (_hasJump)
			{
				ryuJump->DrawFlipX(center.x, center.y);
				return;
			}
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

void Ryu::Jump()
{
	if (!_hasJump)
	{
		vY = SPEED_Y;
		_heightJump = 0;
		ryuJump->SelectIndex(0);
		_action = Action::Jump1;
		_hasJump = true;
	}
}

void Ryu::Initialize()
{
	sprite->SelectIndex(0);
}

void Ryu::Stop()
{
	if (!_hasJump) vX = 0;
	_action = Action::Idle;

}

ECollisionDirect Ryu::GetCollisionDirect(GameObject* other)
{
	float x = this->posX - other->posX;
	float y = this->posY - other->posY;
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
		else
			return ECollisionDirect::Colls_Bot;
	}

	return ECollisionDirect::Colls_None;
}

D3DXVECTOR2* Ryu::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}

Ryu::~Ryu(void)
{

}