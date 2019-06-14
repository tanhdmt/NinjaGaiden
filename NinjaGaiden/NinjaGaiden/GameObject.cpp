
#include "GameObject.h"
#include "Camera.h"
#include <d3d9.h>

GameObject::GameObject(void)
{
	posX = 0;
	posY = 0;
	width = 0;
	height = 0;
	canMove = false;
}

void GameObject::SetActive(float x, float y) {}
void GameObject::SetActive()
{
	if (!active)
		active = true;
}

GameObject::GameObject(float _posX, float _posY, EnumID _id)
{
	posX = initX = _posX;
	posY = initY = _posY;
	vX = 0;
	vY = 0;
	id = _id;
	active = true;
	death = false;
	type = ObjectType::None_Type;
	canMove = false;
	hp = 1;

	CreateSprite();
	if (sprite != NULL)
	{
		width = sprite->_texture->FrameWidth;
		height = sprite->_texture->FrameHeight;
	}
}

void GameObject::CreateSprite()
{
	switch (id)
	{
	case EnumID::Ground1_ID:
	case EnumID::Ground2_ID:
	case EnumID::Ground4_ID:
	case EnumID::Stair_ID:
		sprite = NULL;
		break;
	case EnumID::SwordMan_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 2, 200);
		break;
	case EnumID::Boss_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 0);
		break;
	case EnumID::RocketMan_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 0, 150);
		break;
	case EnumID::Banshee_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 80);
		break;
	case EnumID::Boomerang_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 14, 14, 0);
		break;
	case EnumID::BoomerangS_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 13, 13, 0);
		break;
	case EnumID::FireWeapon_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 15, 15, 0);
		break;
	case EnumID::BonusBlue_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 8, 9, 0);
		break;
	case EnumID::BonusRed_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 9, 10, 0);
		break;
	case EnumID::ThrowStar_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 2, 3, 0);
		break;
	case EnumID::WindmillThrowStar_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 3, 4, 0);
		break;
	case EnumID::TimeFreeze_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 12, 13, 0);
		break;
	case EnumID::FireWheel_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 5, 6, 0);
		break;
	case EnumID::SpititualBlue_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 0);
		break;
	case EnumID::SpiritualRed_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 1, 2, 0);
		break;
	case EnumID::RestoreStrength_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 11, 12, 0);
		break;
	case EnumID::Bat_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 150);
		break;
	case EnumID::Bird_BlueStrengthItem_ID:
	case EnumID::Bird_RedStrengthItem_ID:
	case EnumID::Bird_ThrowingItem_ID:
	case EnumID::Bird_RedBonusItem_ID:
	case EnumID::Bird_BlueBonusItem_ID:
	case EnumID::Bird_FireWheelItem_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 80);
		break;
	case EnumID::Butterfly_BlueStrengthItem_ID:
	case EnumID::Butterfly_RedStrengthItem_ID:
	case EnumID::Butterfly_TimeItem_ID:
	case EnumID::Butterfly_ThrowingItem_ID:
	case EnumID::Butterfly_RedBonusItem_ID:
	case EnumID::Butterfly_BlueBonusItem_ID:
	case EnumID::Butterfly_FireWheelItem_ID:
	case EnumID::Butterfly_RestoringItem_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 80);
		break;
	case EnumID::YellowDog_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 150);
		break;
	case EnumID::MachineGunGuy_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 150);
		break;
	case EnumID::BrownBird_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 150);
		break;
	case EnumID::Runner_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 150);
		break;
	default:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 1);
		break;
	}
}

void GameObject::Collision(list<GameObject*> obj, int dt)
{
}

void GameObject::Collision(list<GameObject*> obj, GameObject* ryu, int dt)
{
}

void GameObject::Update(int deltaTime)
{
	if (sprite != NULL && active==true)
		sprite->Update(deltaTime);
}

void GameObject::Update(int dt, D3DXVECTOR2 * samusPos)
{
	if (sprite != NULL && active ==true)
		sprite->Update(dt);
}

void GameObject::Draw(CCamera* camera)
{
	if (sprite != NULL)
	{
		D3DXVECTOR2 center = camera->Transform(posX, posY);
		sprite->Draw(center.x, center.y);
	}
}

ECollisionDirect GameObject::GetCollisionDirect(float normalx, float normaly)
{
	if (normalx == 0 && normaly == 1)
	{
		return ECollisionDirect::Colls_Bot;
	}
	if (normalx == 0 && normaly == -1)
	{
		return ECollisionDirect::Colls_Top;
	}
	if (normalx == 1 && normaly == 0)
	{
		return ECollisionDirect::Colls_Left;
	}
	if (normalx == -1 && normaly == 0)
	{
		return ECollisionDirect::Colls_Right;
	}
	return ECollisionDirect::Colls_None;
}

ECollisionDirect GameObject::GetCollisionDirect(GameObject* other)
{
	float x = this->posX - other->posX;
	float y = this->posY - other->posY;
	

	return ECollisionDirect::Colls_None;
}

void GameObject::Remove()
{
	active = false;
	death = true;
}

void GameObject::ReceiveDamage(int damagePoint)
{
	if (hp <= 0)
		return;
	hp -= damagePoint;
	if (hp == 0)
		death = true;
}

Box GameObject::GetBox()
{
	Box result(posX - width / 2, posY + height / 2, width, height);
	return result;
}

int GameObject::getWidth()
{
	if (sprite == NULL)
		return 32;
	return sprite->_texture->FrameWidth;
}

int GameObject::getHeight()
{
	if (sprite == NULL)
		return 32;
	return sprite->_texture->FrameHeight;
}

void GameObject::setX(float x)
{
	this->posX = x;
}

void GameObject::setY(float y)
{
	this->posY = y;
}

float GameObject::getX()
{
	return this->posX;
}

float GameObject::getY()
{
	return this->posY;
}

void GameObject::onReborn()
{
	setX(initX);
	setY(initY);
	active = true;

}

float GameObject::getInitX()
{
	return this->initX;
}

float GameObject::getInitY()
{
	return this->initY;
}

float GameObject::getLeft()
{
	return this->posX;
}

float GameObject::getRight()
{
	return this->posX - width;
}

float GameObject::getTop()
{
	return this->posY;
}

float GameObject::getBottom()
{
	return this->posY + height;
}

void GameObject::ProcessInput(LPDIRECT3DDEVICE9 d3ddv, int t) {}
void GameObject::OnKeyDown(int KeyCode) {}
GameObject::~GameObject(void) {}