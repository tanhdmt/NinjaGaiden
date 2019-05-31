#include "Ground2.h"



Ground2::Ground2(void) : GameObject()
{
}

Ground2::Ground2(float _posX, float _posY, int _width, int _height, EnumID _id) :
	GameObject(_posX, _posY, _id)
{
	width = _width;
	height = _height;
}

Ground2::~Ground2(void)
{
}