#pragma once
#include <vector>
#include <iostream>
#include "GameObject.h"

using namespace std;

class Cell
{
	vector<GameObject*> objects;
public:
	vector<GameObject*> getObjects();
	void add(GameObject* object);
	Cell();
	~Cell();
};

