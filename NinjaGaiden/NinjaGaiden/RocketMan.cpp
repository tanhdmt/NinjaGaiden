#include "RocketMan.h"

#define SPEED_X 0.2f
#define SPEED_Y 0.35f
#define MAX_HEIGHT 250.0f

RocketMan::RocketMan(void) : DynamicObject()
{
}

RocketMan::RocketMan(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::RocketMan_ID)
{
	type = ObjectType::Enemy_Type;
	//point = 300;
	active = false;
	//hp = 3;
	//bullet = new Bullet(x-24, y + 20, vX, EnumID::Bullet_ID);
	bullet = new list<Bullet*>();
	vX = -1;
	bullet->push_back(new Bullet(posX + (24 * vX), posY + 20, vX, EnumID::Bullet_ID));
	//posX = x;
}

void RocketMan::Update(int dt, D3DXVECTOR2* ryuPos)
{
	if (sprite == NULL || !active)
		return;
	//if (abs(startPosX - samusPos->x) <= 70 && abs(posY - samusPos->y) >= 50 && abs(vX) <= SPEED_X
	//else
		//vX = SPEED_X;
	/*if (abs(vX) > SPEED_X)
		vX = SPEED_X * 3;
	if (samusPos->x < posX)
		vX = -vX;*/
	if (posX > ryuPos->x)
		vX = -1;
	else
		vX = 1;
	//posX = vX * dt;
	list<Bullet*>::iterator i = bullet->begin();
	while (i != bullet->end())
	{
		if (!(*i)->active)
		{
			bullet->erase(i++);
			bullet->push_back(new Bullet(posX + (24*vX), posY + 20, vX, EnumID::Bullet_ID));
		}
		else
		{
			(*i)->Update(dt);
			++i;
		}
	}
	sprite->Update(dt);
	//bullet->Update(dt);
}

Box RocketMan::GetBox()
{
	return Box(posX - sprite->_texture->FrameWidth / 2, (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);
}

void RocketMan::Collision(list<GameObject*> obj, int dt)
{
	//int countCollis = 0;
	//list<GameObject*>::iterator _itBegin;
	//for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	//{
	//	float moveX;
	//	float moveY;
	//	float normalx;
	//	float normaly;
	//	GameObject* other = (*_itBegin);
	//	Box box = this->GetBox();
	//	Box boxOther = other->GetBox();

	//	if (AABB(box, boxOther, moveX, moveY) == true)
	//	{
	//		ECollisionDirect dir = this->GetCollisionDirect(other);
	//		switch (other->id)
	//		{
	//		case EnumID::Ground1_ID:
	//			countCollis++;
	//			if (dir == ECollisionDirect::Colls_Left || dir == ECollisionDirect::Colls_Right)
	//			{
	//				vX = -vX;
	//			}
	//			break;
	//		}
	//	}
	//}
	//if (countCollis == 0)
	//{
	//	vX = -vX;
	//}
}

void RocketMan::Draw(CCamera* camera)
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
	if (active)
	{
		for (list<Bullet*>::iterator i = bullet->begin(); i != bullet->end(); i++)
		{
			if ((*i)->active)
				(*i)->Draw(camera);
		}
	}
}

void RocketMan::SetActive(float x, float y)
{

	if (abs(posX - x) <= 200 && !active)
	{
		active = true;
		//vX = -SPEED_X;
	}
}

ECollisionDirect RocketMan::GetCollisionDirect(GameObject* other)
{
	/*float x = (this->posX) - (other->posX);
	float y = (this->posY) - (other->posY);*/
	/*float x = 0;
	if (vX < 0)
		x = (this->posX - (this->getWidth() / 2) - 32) - (other->posX - (other->getWidth() / 2));
	else
		x = (this->posX - (this->getWidth() / 2) + 32) - (other->posX - (other->getWidth() / 2));
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
	}*/

	return ECollisionDirect::Colls_None;
}

RocketMan::~RocketMan(void)
{
}
