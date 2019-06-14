#ifndef _BOOMERANG_H_
#define _BOOMERANG_H_

#include"Weapon.h"

class Boomerang : public Weapon
{
	float _length;
	int _timeSpawn;
	int count;
	float rad;
	float ryuX, ryuY;
	int ryuWidth;
public:
	Boomerang(void);
	Boomerang(float x, float y, float _huong, EnumID id);
	void Update(int dt);
	void Collision(Box ryuBox, list<GameObject*> &obj, int dt);
	void Draw(CCamera*);
	~Boomerang(void);
};

#endif