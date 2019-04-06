#include "DynamicObject.h"

DynamicObject::DynamicObject(void) : GameObject()
{

}

DynamicObject::DynamicObject(float _posX, float _posY, float _vX, float _vY, EnumID id) : GameObject(_posX, _posY, id)
{
	vX = _vX;
	vY = _vY;
	
}

void DynamicObject::Update(int dt) {
	if (sprite == NULL)
		return;
	posX = vX * dt;
	posY = vY * dt;
	sprite->Update(dt);
}

void DynamicObject::Draw(CCamera* camera)
{
	if (sprite == NULL) {
		return;
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
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
}