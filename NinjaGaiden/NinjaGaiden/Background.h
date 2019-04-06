#ifndef _QBACKGROUND_H_
#define _QBACKGROUND_H_


#include <list>
#include <map>
#include "Camera.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include "Tile.h"

using namespace std;

class Background
{
public:
	CSprite* bgSprite;
	map<int, Tile*> *listTile;

	Background(void);
	Background(int);
	void Draw(CCamera *camera);
	~Background(void);
};

#endif

