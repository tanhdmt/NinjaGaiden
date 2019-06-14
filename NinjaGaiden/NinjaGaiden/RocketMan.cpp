#include "RocketMan.h"

#define SPEED_X 0.0f
#define SPEED_Y 0.0f
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
	posX = x;
	posY = y;
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
	//if (posX > ryuPos->x)
	//	vX = -1;
	//else
	//	vX = 1;
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

//Box RocketMan::GetBox()
//{
//	return Box(posX - sprite->_texture->FrameWidth / 2, (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);
//}

void RocketMan::Collision(list<GameObject*> obj, int dt)
{
}

void RocketMan::Draw(CCamera* camera)
{
	if (sprite == NULL || IsHurt() || !active) {
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

RocketMan::~RocketMan(void)
{
}
