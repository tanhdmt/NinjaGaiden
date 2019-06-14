#include "Boss.h"

#define SPEED_X 0.6f
#define SPEED_Y 0.8f
#define MAX_HEIGHT 180.0f
int times = 0;
Boss::Boss(void) : DynamicObject()
{
}

Boss::Boss(float x, float y) : DynamicObject(x, y, 0, -SPEED_Y, EnumID::Boss_ID)
{
	type = ObjectType::Enemy_Type;
	//point = 300;
	active = true;
	hasJump = true;
	_heightJump = 0.0f;
	sprite->SelectIndex(0);
	vX = SPEED_X;
	timeDelay = 0;
	bossHp = 16;
	ryuHurt = false;

	lbullet = new list<BossBullet*>();
	lbullet->push_back(new BossBullet(40, 64, 1, EnumID::Bullet_ID));
	lbullet->push_back(new BossBullet(56, 96, 1, EnumID::Bullet_ID));
	lbullet->push_back(new BossBullet(72, 128, 1, EnumID::Bullet_ID));
	rbullet = new list<BossBullet*>();
	rbullet->push_back(new BossBullet(440, 64, -1, EnumID::Bullet_ID));
	rbullet->push_back(new BossBullet(424, 96, -1, EnumID::Bullet_ID));
	rbullet->push_back(new BossBullet(408, 128, -1, EnumID::Bullet_ID));
}

void Boss::Update(int dt)
{
	if (sprite == NULL || !active)
		return;
	if (bossHp <= 0)
	{
		times += dt;
		if (times > 300)
			active = false;
	}
	else
	{
		if (hasJump)
		{
			posX += vX * dt;
			posY += vY * dt;
			sprite->SelectIndex(1);
			_heightJump += vY * dt;
			if (_heightJump >= MAX_HEIGHT)
			{
				vY = -SPEED_Y;
				fireCount++;
				if (fireCount == 4)fireCount = 0;

			}
		}
		else {
			sprite->SelectIndex(0);
		}
		list<BossBullet*>::iterator i = lbullet->begin();
		if (fireCount == 1) {
			//active lại đạn bên trái
			while (i != lbullet->end())
			{
				(*i)->SetActive();
				++i;
			}
		}
		i = rbullet->begin();
		if (fireCount == 3) {
			//active lại đạn bên phải
			while (i != rbullet->end())
			{
				(*i)->SetActive();
				++i;
			}
		}
		// cập nhật đạn bên trái
		i = lbullet->begin();
		while (i != lbullet->end())
		{
			if ((*i)->active)
			{
				(*i)->Update(dt);
			}
			++i;
		}
		// cập nhật đạn bên phải
		i = rbullet->begin();
		while (i != rbullet->end())
		{
			if ((*i)->active)
			{
				(*i)->Update(dt);
			}
			++i;
		}
	}
}

Box Boss::GetBox()
{
	return Box(posX - sprite->_texture->FrameWidth / 2, (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight);
}

void Boss::Collision(list<GameObject*> obj, GameObject* ryu, int dt)
{
	int countCollis = 0;
	timeDelay += dt;
	list<GameObject*>::iterator _itBegin;
	if (bossHp > 0)
	{
		for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
		{
			float moveX;
			float moveY;
			float normalx;
			float normaly;
			GameObject* other = (*_itBegin);
			Box box = this->GetBox();
			Box boxOther = other->GetBox();
			// kiểm tra đạn đã đi hết đường bay chưa
			//if (other->id == EnumID::Ground1_ID) {
				list<BossBullet*>::iterator i = lbullet->begin();
				while (i != lbullet->end())
				{
					if ((*i)->active)
					{
						(*i)->Collision(other, ryu, dt);
						if (!ryuHurt && (*i)->ryuHurt)
						{
							ryuHurt = (*i)->ryuHurt;
						}
					}
					++i;
				}
				i = rbullet->begin();
				while (i != rbullet->end())
				{
					if ((*i)->active)
					{
						(*i)->Collision(other, ryu, dt);
						if (!ryuHurt && (*i)->ryuHurt)
						{
							ryuHurt = (*i)->ryuHurt;
						}
					}
					++i;
				}
			//}

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				ECollisionDirect dir = this->GetCollisionDirect(other);
				switch (other->id)
				{
				case EnumID::Ground1_ID:
					countCollis++;
					//xet cham dat
					if (vY < 0 && hasJump && dir == ECollisionDirect::Colls_Bot)
					{
						//posY += moveY;
						//onLand = true;
						hasJump = false;
						vY = 0;
						sprite->SelectIndex(0);

						vX = -vX;
						hasJump = true;
						vY = SPEED_Y;
						//_isFall = false;
					}
					break;
				}
			}
		}
	}
	
	/*if (countCollis == 0)
	{
		vX = -vX;
	}*/
}

//void Skree::Draw(CCamera* camera)
//{
//	
//
//}

void Boss::SetActive(float x, float y)
{
	/*active = true;
	hasJump = true;*/
}

ECollisionDirect Boss::GetCollisionDirect(GameObject* other)
{
	/*float x = (this->posX) - (other->posX);
	float y = (this->posY) - (other->posY);*/
	float x = (this->posX - (this->getWidth() / 2)) - (other->posX - (other->getWidth() / 2));
	/*if (vX < 0)
		x = (this->posX - (this->getWidth() / 2) - 32) - (other->posX - (other->getWidth() / 2));
	else
		x = (this->posX - (this->getWidth() / 2) + 32) - (other->posX - (other->getWidth() / 2));*/
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
void Boss::Draw(CCamera* camera) {
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
		list<BossBullet*>::iterator i = lbullet->begin();
		// cập nhật đạn bên trái
		i = lbullet->begin();
		while (i != lbullet->end())
		{
			if ((*i)->active)
			{
				(*i)->Draw(camera);
			}
			++i;
		}
		// cập nhật đạn bên phải
		i = rbullet->begin();
		while (i != rbullet->end())
		{
			if ((*i)->active)
			{
				(*i)->Draw(camera);
			}
			++i;
		}
	}
}

Boss::~Boss(void)
{
}
