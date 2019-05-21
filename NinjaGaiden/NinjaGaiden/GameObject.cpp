
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
	case EnumID::Stair_ID:
		sprite = NULL;
		break;
	case EnumID::SwordMan_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 2, 80);
		break;
	case EnumID::Boss_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 0);
		break;
	case EnumID::Banshee_ID:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 0, 1, 0);
		break;
	default:
		sprite = new CSprite(Singleton::getInstance()->getTexture(id), 1);
		break;
	}
}

void GameObject::Collision(list<GameObject*> obj, int dt)
{
}

void GameObject::Update(int deltaTime)
{
	if (sprite != NULL)
		sprite->Update(deltaTime);
}

void GameObject::Update(int dt, D3DXVECTOR2 * samusPos)
{
	if (sprite != NULL)
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
}

void GameObject::ReceiveDamage(int damagePoint)
{
	
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
	this->active = false;
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