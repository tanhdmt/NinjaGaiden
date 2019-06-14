#include "Grid.h"
#include <algorithm>
#include <iterator>

#define CAMERA CCamera::getInstance()

Grid * Grid::instance = NULL;
int Grid::prevLevel = 1;

Grid * Grid::getInstance(int level)
{
	if (instance == NULL || level != prevLevel)
	{
		instance = new Grid(level);
		prevLevel = level;
	}
	return instance;
}

Grid::Grid(int level)
{
	switch (level)
	{
	case 1:
	{
		widthLevel = 4096;
		heightLevel = 416;
		cellWidth = 128;
		cellHeight = 52;
		rowCells = 8;
		columnCells = 32;
	}
	break;
	case 2:
	{
		widthLevel = 6144;
		heightLevel = 416;
		cellWidth = 96;
		cellHeight = 52;
		rowCells = 8;
		columnCells = 64;
	}
	break;
	case 3:
	{
		widthLevel = 512;
		heightLevel = 352;
		cellWidth = 128;
		cellHeight = 88;
		rowCells = 4;
		columnCells = 4;
	}
	break;
	}

	gridData = new Cell*[rowCells];
	for (int rowIndex = 0; rowIndex < rowCells; rowIndex++)
	{
		gridData[rowIndex] = new Cell[columnCells];
	}
}


void Grid::addObject(list<GameObject*> *lstObject)
{
	int temp = 0;
	for (list<GameObject*>::iterator i = lstObject->begin(); i != lstObject->end(); i++)
	{
		GameObject* object = (*i);
		int beginCol = object->getX() / cellWidth;
		int endCol = (object->getX() + object->getWidth()) / cellWidth;
		int beginRow = (object->getY() - object->getHeight()) / cellHeight;
		int endRow = object->getY() / cellHeight;

		if (beginCol == endCol || (endCol - beginCol == 1))
			gridData[beginRow][beginCol].add(object);
	}
}

vector<GameObject*> Grid::getObjectInCameraCells()
{
	
	vector<GameObject*> result;
	int beginCol = (camera->viewport.x+50) / cellWidth;
	int endCol = (camera->viewport.x + G_ScreenWidth + 50) / cellWidth;
	int beginRow = (camera->viewport.y - (G_ScreenHeight+4)) / cellHeight;
	int endRow = camera->viewport.y / cellHeight;
	for (int i = beginRow; i < endRow; i++) {
		for (int j = beginCol; j < endCol; j++)
		{
			vector<GameObject*> b = gridData[i][j].getObjects();
			result.insert(std::end(result), std::begin(b), std::end(b));
		}
	}
	if (result.size() > 0)
	{
		return result;
	}
	return result;
}

vector<GameObject*> Grid::getObjectActive(CCamera* _camera)
{
	camera = _camera;
	vector<GameObject*> objectsInCamera = this->getObjectInCameraCells();

	//reset object về vị trí ban đầu khi ra khỏi camera
	for (int i = 0; i < objectActive.size(); i++) {
		int x = objectActive[i]->getX();
		int y = objectActive[i]->getY();
		int initX = objectActive[i]->getInitX();
		int initY = objectActive[i]->getInitY();

		if ((x < (camera->viewport.x - 10) || x >(camera->getRight() + 10))&&(initX <= camera->viewport.x - 10 || initX >= (camera->getRight() + 10))) {
			objectActive[i]->onReborn();
			objectActive.erase(objectActive.begin() + i);
		}
	}

	list<GameObject*> newObjects;
	std::sort(objectsInCamera.begin(), objectsInCamera.end());
	std::sort(objectActive.begin(), objectActive.end());
	objectsInCamera.erase(std::unique(objectsInCamera.begin(), objectsInCamera.end()), objectsInCamera.end());
	objectActive.erase(std::unique(objectActive.begin(), objectActive.end()), objectActive.end());
	//so sánh, nếu có object nào khác với object đang có sẵn thì thêm vô newObjects
	std::set_difference(objectsInCamera.begin(), objectsInCamera.end(),
		objectActive.begin(), objectActive.end(),
		std::back_inserter(newObjects));
	objectActive.insert(std::end(objectActive), std::begin(newObjects), std::end(newObjects));

	return objectActive;
}

Grid::~Grid()
{

}
