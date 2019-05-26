#include "Bat.h"



Bat::Bat(void):DynamicObject()
{
}
Bat::Bat(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::Bat_ID)
{
	type = ObjectType::Enemy_Type;
	active = false;
	vX = -1;
}
void Bat::Update(int dt) {
	sprite->Update(dt);
}
void Bat::SetActive(float x, float y)
{

	if (abs(posX - x) <= 200 && !active)
	{
		active = true;
		//vX = -SPEED_X;
	}
}

Bat::~Bat()
{
}
