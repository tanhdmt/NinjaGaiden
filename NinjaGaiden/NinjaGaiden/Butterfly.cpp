#include "Butterfly.h"



Butterfly::Butterfly(void) : DynamicObject()
{
}
Butterfly::Butterfly(float x, float y, EnumID _id) : DynamicObject(x, y, 0, 0, _id)
{
	type = ObjectType::Enemy_Type;
	active = false;
	vX = 1;
}
void Butterfly::Update(int dt) {
	sprite->Update(dt);
}
void Butterfly::SetActive(float x, float y)
{
}

Butterfly::~Butterfly()
{
}
