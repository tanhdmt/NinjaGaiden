#include "Ground.h"

Ground::Ground(void) : GameObject()
{
}

Ground::Ground(float _posX, float _posY, int _width, int _height, EnumID _id) :
	GameObject(_posX, _posY, _id)
{
	width = _width;
	height = _height;
}

Ground::~Ground(void)
{
}
