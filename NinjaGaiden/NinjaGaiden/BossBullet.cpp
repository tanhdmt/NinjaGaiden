#include "BossBullet.h"



#define SPEED_X 0.4f
int t = 0;

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
	active = false;
	fire = new Fire(posX, posY, vX, EnumID::Fire_ID);
	startX = x;
	startY = y;
	ryuHurt = false;
	explosion = new Explosion(posX, posY, EnumID::Explosion_ID);

}

void BossBullet::Update(int dt)
{
	if (explosion->active)
		explosion->Update(dt);
	if (sprite == NULL || !active)
		return;
	posX += vX * dt;
	fire->Update(dt);
}

void BossBullet::Draw(CCamera* camera)
{
	if (explosion->active)
		explosion->Draw(camera);
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
void BossBullet::Collision(GameObject* obj, GameObject* ryu, int dt) {
		float moveX;
		float moveY;
		float normalx;
		float normaly;
		if (this->active)
		{
			Box box = this->GetBox();
			Box boxOther = obj->GetBox();
			Box boxRyu = ryu->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				switch (obj->id)
				{
				case EnumID::Ground1_ID:
					this->active = false;
					this->Reset(dt);
					break;
					break;
				}
			}
			if (AABB(box, boxRyu, moveX, moveY) == true)
			{
				if (ryu->_hasAttack)
				{
					explosion->setX(this->posX);
					explosion->setY(this->posY);
					explosion->active = true;

				}
				else
				{
					if (!ryuHurt)
						ryuHurt = true;
				}
				this->active = false;
				this->Reset(dt);
			}
		}
}
void BossBullet::SetActive() {
	if (!this->active)
		this->active = true;
}
void BossBullet::Reset(int dt) {
	posX = startX;
	posY = startY;

	//t += dt;
	//if (t > 50)
	//{
	//	ryuHurt = false;
	//	t = 0;
	//}
	//ryuHurt = false;
	//active = false;
}
Box BossBullet::GetBox()
{
	if (vX < 0)
		return Box(posX - sprite->_texture->FrameWidth / 2, (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);
	return Box(posX - sprite->_texture->FrameWidth / 2, (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);
}

BossBullet::~BossBullet(void)
{
}

