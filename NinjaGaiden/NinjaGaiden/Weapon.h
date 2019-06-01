#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "DynamicObject.h"
#include "Explosion.h"

class Weapon : public DynamicObject
{
public:
	Explosion* explosion;
	Weapon(void);
	Weapon(float x, float y, float _huong, EnumID id);
	virtual void Draw(CCamera*);
	virtual void Collision(list<GameObject*> &obj, int dt);
	virtual void Collision(Box ryuBox, list<GameObject*> &obj, int dt);
	void Update(int dt);
	~Weapon(void);
};

#endif