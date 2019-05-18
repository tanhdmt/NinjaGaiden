#include "Cell.h"



vector<GameObject*> Cell::getObjects()
{
	return this->objects;
}

void Cell::add(GameObject * object)
{
	objects.push_back(object);
}

Cell::Cell()
{
}


Cell::~Cell()
{
}
