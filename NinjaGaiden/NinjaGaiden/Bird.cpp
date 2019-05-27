#include "Bird.h"



Bird::Bird(void):DynamicObject()
{
}
Bird::Bird(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::Bird_ID)
{
	type = ObjectType::Enemy_Type;
	active = false;
	vX = -1;
}
void Bird::Update(int dt) {
	sprite->Update(dt);
}
void Bird::SetActive(float x, float y)
{

	if (abs(posX - x) <= 200 && !active)
	{
		active = true;
		//vX = -SPEED_X;
	}
}

Bird::~Bird()
{
}
