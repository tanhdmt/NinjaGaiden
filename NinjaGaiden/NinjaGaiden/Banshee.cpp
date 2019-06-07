#include "Banshee.h"

#define SPEED_X 0.2f
#define SPEED_Y 0.35f
#define MAX_HEIGHT 250.0f

Banshee::Banshee(void) : DynamicObject()
{
}

Banshee::Banshee(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::Banshee_ID)
{
	type = ObjectType::Enemy_Type;
	//point = 300;
	active = false;
	//hp = 3;
	//sword = new list<Sword*>();
	vX = -1;
	//sword->push_back(new Sword(posX + (24 * vX), posY + 20, vX, EnumID::Sword_ID));
}

void Banshee::Update(int dt)
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
	//list<Sword *>::iterator i = sword->begin();
	//while (i != sword->end())
	//{
	//	if (!(*i)->active)
	//	{
	//		sword->erase(i++);
	//		sword->push_back(new Sword(posX + (24 * vX), posY + 20, vX, EnumID::Sword_ID));
	//	}
	//	else
	//	{
	//		(*i)->Update(dt);
	//		++i;
	//	}
	//}
	posX += vX * dt;
	posY += vY * dt;
}


void Banshee::Collision(list<GameObject*> obj, int dt)
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


void Banshee::SetActive(float x, float y)
{

	if (abs(posX - x) <= 300 && !active)
	{
		active = true;
		vX = -SPEED_X;
	}
}

ECollisionDirect Banshee::GetCollisionDirect(GameObject* other)
{
	float x = 0;
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
	}

	return ECollisionDirect::Colls_None;
}
//void Banshee::Draw(CCamera* camera) {
//	if (sprite == NULL || !active || IsHurt()) {
//		return;
//	}
//	D3DXVECTOR2 center = camera->Transform(posX, posY);
//	if (vX < 0)
//		sprite->DrawFlipX(center.x, center.y);
//	else
//		sprite->Draw(center.x, center.y);
//	//if (active)
//	//{
//	//	for (list<Sword*>::iterator i = sword->begin(); i != sword->end(); i++)
//	//	{
//	//		if ((*i)->active)
//	//			(*i)->Draw(camera);
//	//	}
//	//}
//}

Banshee::~Banshee(void)
{
}
