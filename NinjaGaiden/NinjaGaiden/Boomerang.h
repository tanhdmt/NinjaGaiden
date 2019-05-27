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
public:
	Boomerang(void);
	Boomerang(float x, float y, float _huong);
	void Update(int dt);
	void Collision(Box simonBox);
	void Draw(CCamera*);
	~Boomerang(void);
};

#endif