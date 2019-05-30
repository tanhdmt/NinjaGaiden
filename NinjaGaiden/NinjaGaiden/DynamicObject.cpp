#include "DynamicObject.h"

DynamicObject::DynamicObject(void) : GameObject()
{

}

DynamicObject::DynamicObject(float _posX, float _posY, float _vX, float _vY, EnumID id) : GameObject(_posX, _posY, id)
{
	vX = _vX;
	vY = _vY;
	canMove = true;
	active = true;
	Initialize();
}

void DynamicObject::Update(int dt) {
	if (sprite == NULL || !active)
		return;
	posX = vX * dt;
	if (posX <= width / 2 + 2 || posX >= G_MapWidth - (width / 2 - 2))
		vX = -vX;
	posY = vY * dt;
	if (active)
		sprite->Update(dt);
}

void DynamicObject::Draw(CCamera* camera)
{
	if (sprite == NULL || !active || IsHurt()) {
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX < 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void DynamicObject::SetActive(float x, float y)
{
	/*if (active) return;
	if (abs(posX - x) <= 350 && abs(posY - y) <= 200)
	{
		if (posX - x > 0)
		{
			vX = -vX;
		}
		active = true;
	}*/
}

DynamicObject::~DynamicObject(void)
{
}

void DynamicObject::Collision(list<GameObject*> obj, int dt)
{

}

Box DynamicObject::GetBox()
{
	Box result(posX - width / 2, posY + height / 2, width, height, vX, 0);
	return result;
}

void DynamicObject::Initialize()
{
	bActiveHurt = false;
	_localHurtTime = 0;
	_bHurt = false;
}

bool DynamicObject::IsHurt()
{
	if (!bActiveHurt)
		return false;
	bool result = _bHurt;
	DWORD now = GetTickCount();
	DWORD deltaTime = now - _localHurtTime;
	if (deltaTime >= 500)
	{
		bActiveHurt = false;
	}
	if (deltaTime % (int)(1000 / 25) < 15)
	{
		_bHurt = !_bHurt;
	}
	return result;
}

void DynamicObject::ReceiveDamage(int damagePoint)
{
	if (!IsHurt())
	{
		if (hp <= 0)
			return;
		hp -= damagePoint;
		if (hp == 0)
			death = true;
		bActiveHurt = true;
		_localHurtTime = GetTickCount();
	}
}