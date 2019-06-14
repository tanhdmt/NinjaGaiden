#include "Bird.h"



Bird::Bird(void):DynamicObject()
{
}
Bird::Bird(float x, float y, EnumID _id) : DynamicObject(x, y, 0, 0, _id)
{
	type = ObjectType::Item_Type;
	active = false;
	vX = 1;
}
void Bird::Update(int dt) {
	sprite->Update(dt);
}
void Bird::SetActive(float x, float y)
{

	if (abs(posX - x) <= 400 && !active)
	{
		active = true;
		//vX = -SPEED_X;
	}
}

Bird::~Bird()
{
}
