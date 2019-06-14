#include "BrownBird.h"



#define SPEED_X 0.4f
#define SPEED_Y 0.3f
#define ACCELERATION_X 0.01f
#define MAX_HEIGHT 250.0f

BrownBird::BrownBird(void) : DynamicObject()
{
}

BrownBird::BrownBird(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::BrownBird_ID)
{
	type = ObjectType::Enemy_Type;
	//point = 300;
	active = false;
	//hp = 3;
	vX = SPEED_X;
	vY = SPEED_Y;
	aX = ACCELERATION_X;
}

void BrownBird::Update(int dt, D3DXVECTOR2 * ryupos) {
	if (active)
		sprite->Update(dt);

	if (sprite == NULL || !active)
		return;

	if (posX < ryupos->x - 70 && posY < ryupos->y +40) {
		vX = 0;
		vY = SPEED_Y;
	}
	else if (posX < ryupos->x - 70 && posY > ryupos->y +40) {
		vX = SPEED_X;
		vY = -SPEED_Y;
	}
	else if (posX >= ryupos->x + 70 && posY > ryupos->y +40) {
		vX = -SPEED_X;
		vY = -SPEED_Y;
	}
	else if (posX >= ryupos->x + 70 && posY < ryupos->y +40) {
		vX = 0;
		vY = SPEED_Y;
	}
	

	posX += vX * dt + 1 / 2 * aX*dt*dt;
	posY += vY * dt;
}


void BrownBird::Collision(list<GameObject*> obj, int dt)
{

}



void BrownBird::SetActive(float x, float y)
{

	if (abs(posX - x) <= 400 && !active)
	{
		active = true;
		vX = SPEED_X;
	}

}


BrownBird::~BrownBird(void)
{
}

