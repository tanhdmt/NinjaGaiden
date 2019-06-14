#include "SwordMan.h"

#define SPEED_X 0.2f
#define SPEED_Y 0.35f
#define MAX_HEIGHT 250.0f

SwordMan::SwordMan(void) : DynamicObject()
{
}

SwordMan::SwordMan(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::SwordMan_ID)
{
	type = ObjectType::Enemy_Type;
	//point = 300;
	active = false;
	//hp = 3;
}

void SwordMan::Update(int dt)
{
	sprite->Update(dt);
	if (sprite == NULL || !active)
		return;
	//if (abs(startPosX - samusPos->x) <= 70 && abs(posY - samusPos->y) >= 50 && abs(vX) <= SPEED_X
	//else
		//vX = SPEED_X;
	/*if (abs(vX) > SPEED_X)
		vX = SPEED_X * 3;
	if (samusPos->x < posX)
		vX = -vX;*/
	
	posX += vX * dt;
	posY += vY * dt;
}

Box SwordMan::GetBox()
{
	if (vX < 0)
		return Box(posX - sprite->_texture->FrameWidth / 2, (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);
	return Box(posX - sprite->_texture->FrameWidth / 2, (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);
}

void SwordMan::Collision(list<GameObject*> obj, int dt)
{
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
			case EnumID::Ground1_ID:
				countCollis++;
				if (dir == ECollisionDirect::Colls_Left || dir == ECollisionDirect::Colls_Right)
				{
					vX = -vX;
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

//void Skree::Draw(CCamera* camera)
//{
//	
//
//}

void SwordMan::SetActive(float x, float y)
{

	if (abs(posX - x) <= 300 && !active)
	{
		active = true;
		vX = -SPEED_X;
	}
}

ECollisionDirect SwordMan::GetCollisionDirect(GameObject* other)
{
	/*float x = (this->posX) - (other->posX);
	float y = (this->posY) - (other->posY);*/
	float x = 0;
	if (vX < 0)
		x = (this->posX - (this->getWidth() / 2)) - (other->posX - (other->getWidth() / 2));
	else
		x = (this->posX - (this->getWidth() / 2)) - (other->posX - (other->getWidth() / 2));
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

SwordMan::~SwordMan(void)
{
}
