#include "Boss.h"

#define SPEED_X 0.6f
#define SPEED_Y 0.8f
#define MAX_HEIGHT 180.0f

Boss::Boss(void) : DynamicObject()
{
}

Boss::Boss(float x, float y) : DynamicObject(x, y, 0, -SPEED_Y, EnumID::Boss_ID)
{
	type = ObjectType::Enemy_Type;
	//point = 300;
	active = true;
	hasJump = true;
	_heightJump = 0.0f;
	sprite->SelectIndex(0);
	vX = SPEED_X;
	timeDelay = 0;
	//hp = 3;
}

void Boss::Update(int dt)
{
	if (sprite == NULL || !active)
		return;
	if (hasJump)
	{
		posX += vX * dt;
		posY += vY * dt;
		sprite->SelectIndex(1);
		_heightJump += vY * dt;
		if (_heightJump >= MAX_HEIGHT)
		{
			vY = -SPEED_Y;
		}
	}
	else {
		sprite->SelectIndex(0);
	}
	//sprite->Update(dt);
	//if (abs(startPosX - samusPos->x) <= 70 && abs(posY - samusPos->y) >= 50 && abs(vX) <= SPEED_X
	//else
		//vX = SPEED_X;
	/*if (abs(vX) > SPEED_X)
		vX = SPEED_X * 3;
	if (samusPos->x < posX)
		vX = -vX;*/
}

Box Boss::GetBox()
{
	/*if (vX < 0)
		return Box(posX - sprite->_texture->FrameWidth / 2 - 32, (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);*/
	return Box(posX - sprite->_texture->FrameWidth / 2, (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);
}

void Boss::Collision(list<GameObject*> obj, int dt)
{
	int countCollis = 0;
	timeDelay += dt;
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
				countCollis++;
				//xet cham dat
				if (vY < 0 && hasJump && dir == ECollisionDirect::Colls_Bot)
				{
					//posY += moveY;
					//onLand = true;
					hasJump = false;
					vY = 0;
					sprite->SelectIndex(0);

						vX = -vX;
						hasJump = true;
						vY = SPEED_Y;
					//_isFall = false;
				}
				break;
			}
		}
	}
	/*if (countCollis == 0)
	{
		vX = -vX;
	}*/
}

//void Skree::Draw(CCamera* camera)
//{
//	
//
//}

void Boss::SetActive(float x, float y)
{
	/*active = true;
	hasJump = true;*/
}

ECollisionDirect Boss::GetCollisionDirect(GameObject* other)
{
	/*float x = (this->posX) - (other->posX);
	float y = (this->posY) - (other->posY);*/
	float x = (this->posX - (this->getWidth() / 2)) - (other->posX - (other->getWidth() / 2));
	/*if (vX < 0)
		x = (this->posX - (this->getWidth() / 2) - 32) - (other->posX - (other->getWidth() / 2));
	else
		x = (this->posX - (this->getWidth() / 2) + 32) - (other->posX - (other->getWidth() / 2));*/
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

Boss::~Boss(void)
{
}
