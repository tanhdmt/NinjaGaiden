#pragma once
#pragma once
#ifndef CTEXTURE_H
#define CTEXTURE_H

#include <d3d9.h>
#include <d3dx9.h>
#include "Global.h"

class CTexture
{
public:
	const char* FileName; //đường dẫn tới file ảnh
	RECT Size;		//độ phân giải ảnh
	LPDIRECT3DTEXTURE9 texture;
	int Cols;		//số cột frame
	int Rows;		//số hàng frame
	int Count;		//tổng số frame
	int FrameWidth;		//chiều dài 1 frame
	int FrameHeight;	//chiều cao 1 frame

	CTexture(const CTexture &texture);
	CTexture(const char* _fileName, int cols = 1, int rows = 1, int count = 1);
	~CTexture();
	//vẽ texture tại vị trí (x, y) trên màn hình
	void Draw(int x, int y);

protected:
	void Load();
};

#endif
