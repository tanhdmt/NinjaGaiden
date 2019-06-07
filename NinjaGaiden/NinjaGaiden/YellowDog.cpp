#include "YellowDog.h"



#define SPEED_X 0.8f
#define SPEED_Y 0.4f
#define MAX_HEIGHT 250.0f

YellowDog::YellowDog(void) : DynamicObject()
{
}

YellowDog::YellowDog(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::YellowDog_ID)
{
	type = ObjectType::Enemy_Type;
	//point = 300;
	active = false;
	//hp = 3;
	vX = SPEED_X;
	vY = SPEED_Y;
}

void YellowDog::Update(int dt)
{
	if (active)
		sprite->Update(dt);

	if (sprite == NULL || !active)
		return;
	posX += vX * dt;
	posY -= vY * dt;

}


void YellowDog::Collision(list<GameObject*> obj, int dt)
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
					//vX = -vX;
				}
				if (dir == ECollisionDirect::Colls_Bot || dir == ECollisionDirect::Colls_Bot){
					vY = 0;
				}
				break;
			case EnumID::Ground4_ID:
				countCollis++;
				if (dir == ECollisionDirect::Colls_Left || dir == ECollisionDirect::Colls_Right)
				{
					//vX = -vX;
				}
				if (dir == ECollisionDirect::Colls_Bot || dir == ECollisionDirect::Colls_Bot) {
					vY = 0;
				}
				break;
			}
		}
	}
	if (countCollis == 0)
	{
		vY = SPEED_Y;
	}
}

//void Skree::Draw(CCamera* camera)
//{
//	
//
//}

void YellowDog::SetActive(float x, float y)
{

	if (abs(posX - x) <= 200 && !active)
	{
		active = true;
		vX = SPEED_X;
	}

}

ECollisionDirect YellowDog::GetCollisionDirect(GameObject* other)
{
	/*float x = (this->posX) - (other->posX);
	float y = (this->posY) - (other->posY);*/
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

YellowDog::~YellowDog(void)
{
}
