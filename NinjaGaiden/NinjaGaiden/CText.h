#pragma once
#ifndef CTEXT_H
#define CTEXT_H

#include <d3dx9.h>
#include <iostream>
#include <string>
using namespace std;

#define FRAME_RATE 20

class CText
{
private:
	LPD3DXFONT	_font;
	RECT		_fontPosition;
	void _render(char* text_, float x_, float y_, D3DCOLOR color_);
	DWORD _localTime;
	int _frameRate;
	bool _isDrawAnimation;

	void _initialize();

public:
	CText(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_);
	~CText();
	void updateAnimation();
	void render(char* text_, float x_, float y_);
	void render(int number_, float x_, float y_);
	void renderAnimation(char* text_, float x_, float y_, int deltaTime_);
	void renderAnimation(int number_, float x_, float y_, int deltaTime_);
	void onLost();
};
#endif