#include "Camera.h"

CCamera* CCamera::instance = 0;

CCamera::CCamera()
{
	viewport.x = 1;
	viewport.y = G_ScreenHeight;
}

CCamera::~CCamera()
{

}

CCamera* CCamera::getInstance()
{
	if (instance == 0) instance = new CCamera();
	return instance;
}

void CCamera::SetSizeMap(int _max, int _min)
{
	_maxSize = _max;
	_minSize = _min;
}
D3DXVECTOR2 CCamera::Transform(int x, int y)
{
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix);
	matrix._22 = -1;
	matrix._41 = -viewport.x;
	matrix._42 = viewport.y;

	D3DXVECTOR3 pos3(x, y, 1);
	D3DXVECTOR4 MatrixResult;
	D3DXVec3Transform(&MatrixResult, &pos3, &matrix);
	//Kết thúc transform

	D3DXVECTOR2 result = D3DXVECTOR2(MatrixResult.x, MatrixResult.y);
	return result;
}

D3DXVECTOR3 CCamera::CenterSprite(int x, int y)
{
	D3DXVECTOR3 pCenter = D3DXVECTOR3(x / 2, y / 2, 0);
	return pCenter;
}

void CCamera::UpdateCamera(int x)
{
	//if((viewport.x + G_ScreenWidth < _maxSize) || (x - 249 + G_ScreenWidth < _maxSize))
	//	viewport.x = x - 250;
	//if (viewport.x + G_ScreenWidth > _maxSize)
	//	viewport.x = 5138 - G_ScreenWidth;
	//if (viewport.x < _minSize)
	//	viewport.x = _minSize;
	if (x > viewport.x + G_ScreenWidth || x < viewport.x)
	{
		viewport.x = x - G_ScreenWidth / 2;
	}

	if (x < _maxSize - G_ScreenWidth / 2)
		viewport.x = x - G_ScreenWidth / 2;
	if (viewport.x < _minSize)
		viewport.x = _minSize;
	if (viewport.x + G_ScreenWidth > _maxSize)
		viewport.x = _maxSize - G_ScreenWidth;
}

void CCamera::UpdateCamera(int &w, int &h)
{
	if (h == 0)
		return;
	if (h > 0)
	{
		h -= 4;
		viewport.y += 4;
	}
	else
	{
		h += 4;
		viewport.y -= 4;
	}
}

float CCamera::getLeft()
{
	return viewport.x;
}

float CCamera::getRight()
{
	return viewport.x + G_ScreenWidth;
}

float CCamera::getTop()
{
	return viewport.y;
}

float CCamera::getBottom()
{
	return viewport.y - G_ScreenHeight;
}

float CCamera::getX()
{
	return viewport.x;
}

float CCamera::getY()
{
	return viewport.y;
}