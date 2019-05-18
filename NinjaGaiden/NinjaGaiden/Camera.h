#pragma once
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "Global.h"
#include "Sprite.h"
#include "GameObject.h"

class CCamera : public GameObject
{
public:
	D3DXVECTOR2 viewport;		//Thiết lập tọa độ của camera	
	int _maxSize, _minSize;
	static CCamera* instance;

	CCamera();
	~CCamera();
	static CCamera* getInstance();
	D3DXVECTOR3 CenterSprite(int x, int y);	//Tìm tọa độ center của sprite
	void UpdateCamera(int x);
	void UpdateCamera(int &w, int &h);
	void SetSizeMap(int _max, int _min);
	D3DXVECTOR2 Transform(int x, int y);		//Hàm transform, chuyển tọa độ viewport về tọa độ world
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	float getX();
	float getY();
};

#endif
