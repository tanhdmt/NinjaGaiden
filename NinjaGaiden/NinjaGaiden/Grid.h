#pragma once
#include "Cell.h"
#include "Camera.h"
#include "Global.h"

class Grid
{
	int widthLevel, heightLevel;
	int rowCells, columnCells;
	int cellWidth, cellHeight;
	Cell** gridData;
	vector<GameObject*> objectActive;
	static Grid* instance;
	CCamera* camera;
	static int prevLevel;

public:
	static Grid* getInstance(int level);
	void addObject(list<GameObject*> *lstObject);
	vector<GameObject*> getObjectInCameraCells();
	//Hàm này đóng vai trò là bao chứa các object đã đang hoạt động trong camera và các object mới được camera quét qua
	vector<GameObject*> getObjectActive(CCamera* camera);
	Grid(int level);
	~Grid();
};

