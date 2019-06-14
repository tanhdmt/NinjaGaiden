#include "BossBullet.h"



#define SPEED_X 0.4f

BossBullet::BossBullet(void) : DynamicObject()
{
}

BossBullet::BossBullet(float x, float y, float _huong, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	if (_huong > 0)
		vX = SPEED_X;
	else
	{
		vX = -SPEED_X;
	}
	active = true;
	fire = new Fire(posX, posY, vX, EnumID::Fire_ID);
	startX = x;
	startY = y;
}

void BossBullet::Update(int dt)
{
	posX += vX * dt;
	if (sprite == NULL || !active)
		return;
	 fire->Update(dt);
}

void BossBullet::Draw(CCamera* camera)
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
	fire->Draw(camera);
}
void BossBullet::Collision(GameObject* obj, int dt) {
		float moveX;
		float moveY;
		float normalx;
		float normaly;
		Box box = this->GetBox();
		Box boxOther = obj->GetBox();

		if (AABB(box, boxOther, moveX, moveY) == true)
		{
			switch (obj->id)
			{
			case EnumID::Ground1_ID:
				this->active = false;
				this->Reset();
				break;
			}
		}
	
}
void BossBullet::SetActive() {
	this->active = true;
}
void BossBullet::Reset() {
	posX = startX;
	posY = startY;
}

BossBullet::~BossBullet(void)
{
}

