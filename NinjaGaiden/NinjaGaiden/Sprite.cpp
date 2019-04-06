#include "Sprite.h"
#include "Global.h"

CSprite::CSprite()
{
	_texture = NULL;
	_start = 0;
	_end = 0;
	_timeAni = 0;
	_index = 0;
	_timeLocal = 0;
}

CSprite::CSprite(const CSprite &sprite)
{
	_texture = sprite._texture;
	_start = sprite._start;
	_end = sprite._end;
	_timeAni = sprite._timeAni;
	_index = sprite._start;
	_timeLocal = sprite._timeLocal;
}

CSprite::CSprite(CTexture* texture, int start, int end, float timeAnimation)
	: _texture(texture)
{
	_start = start;
	_end = end;
	_timeAni = timeAnimation;
	_index = start;
	_timeLocal = 0;
}

CSprite::CSprite(CTexture* texture, int timeAnimation)
	: _texture(texture)
{
	_start = 0;
	_end = _texture->Count - 1;
	_timeAni = timeAnimation;
	_index = 0;
	_timeLocal = 0;
}

CSprite::~CSprite()
{
	//if(_texture != NULL)
	//delete _texture;
}

void CSprite::Next()
{
	_index++;
	if (_index > _end)
		_index = _start;
}

void CSprite::Reset()
{
	_index = _start;
	_timeLocal = 0;
}

void CSprite::SelectIndex(int index)
{
	_index = index;
}

void CSprite::Update(int ellapseTime)
{
	_timeLocal += ellapseTime;

	if (_timeLocal >= _timeAni) //Nếu time hiện tại lớn hơn or bằng time frame thì reset và chuyển frame
	{
		_timeLocal = 0;
		this->Next();
	}
}

void CSprite::Draw(int X, int Y)
{
	RECT srect;

	srect.left = (_index % _texture->Cols)*(_texture->FrameWidth);// + 1;
	srect.top = (_index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

													 //D3DXVECTOR3 position((float)X, (float)Y, 0);
	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - _texture->FrameWidth / 2;
	position.y = Y - _texture->FrameHeight / 2;
	G_SpriteHandler->Draw(
		_texture->texture,
		&srect,
		&center,
		&position,
		0xFFFFFFFF //color
	);
}

void CSprite::DrawFlipX(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(-1, 1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	x += _texture->FrameWidth;
	this->Draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

void CSprite::DrawFlipY(int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &rotate, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	this->Draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

void CSprite::DrawScale(int index, int x, int y)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x + _texture->FrameWidth / 2, y + _texture->FrameHeight / 2);
	D3DXVECTOR2 scale = D3DXVECTOR2(2, 2);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, &scale, NULL, 0.0f, NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	this->DrawIndex(index, x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}


void CSprite::DrawRotate(int x, int y, float rad)
{
	D3DXMATRIX oldMt;
	G_SpriteHandler->GetTransform(&oldMt);

	D3DXMATRIX newMt;
	D3DXVECTOR2 center = D3DXVECTOR2(x, y);
	D3DXVECTOR2 rotate = D3DXVECTOR2(1, -1);

	D3DXMatrixTransformation2D(&newMt, &center, 0.0f, NULL, &center, D3DXToRadian(rad), NULL);
	D3DXMATRIX finalMt = newMt * oldMt;
	G_SpriteHandler->SetTransform(&finalMt);

	this->Draw(x, y);

	G_SpriteHandler->SetTransform(&oldMt);
}

void CSprite::DrawRect(int X, int Y, RECT SrcRect)
{
	D3DXVECTOR3 position((float)X, (float)Y, 0);
	G_SpriteHandler->Draw(
		_texture->texture,
		&SrcRect,
		NULL,
		&position,
		D3DCOLOR_XRGB(255, 255, 255)
	);
}

void CSprite::DrawIndex(int index, int X, int Y)
{
	RECT srect;		//con trỏ RECT chứa sprite được chọn để cắt

	srect.left = (index % _texture->Cols)*(_texture->FrameWidth);// + 1; texture->Cols: số cột của file Texture
	srect.top = (index / _texture->Cols)*(_texture->FrameHeight);// + 1;
	srect.right = srect.left + _texture->FrameWidth;
	srect.bottom = srect.top + _texture->FrameHeight;// + 1;

	D3DXVECTOR3 position(0, 0, 0);
	D3DXVECTOR3 center(0, 0, 0);
	position.x = X - _texture->FrameWidth / 2;
	position.y = Y - _texture->FrameHeight / 2;
	G_SpriteHandler->Draw(
		_texture->texture,
		&srect,
		&center,
		&position,
		0xFFFFFFFF //color
	);
}

int CSprite::GetIndex()
{
	return _index;
}