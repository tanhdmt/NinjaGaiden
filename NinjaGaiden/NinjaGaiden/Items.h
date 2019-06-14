#ifndef _ITEMS_H_
#define _ITEMS_H_

#include "DynamicObject.h"

class Items : public DynamicObject
{
	int _timeSpawn;
public:
	int ryuScore;
	int ryuHp;
	int ryuSpiri;
	bool ryuFreeze;
	EnumID weaponID;
	Items(void);
	Items(float x, float y, EnumID id);
	virtual void Collision(list<GameObject*> &obj, int dt);
	virtual void Collision(Box ryuBox, list<GameObject*> &obj, int dt);
	ECollisionDirect GetCollisionDirect(GameObject* other);
	void Update(int dt);
	~Items(void);
};

#endif