#ifndef _ROCKETMAN_H_
#define _ROCKETMAN_H_

#include "DynamicObject.h"
#include "CEnum.h"
#include "Bullet.h"

class RocketMan : public DynamicObject
{
public:
	//bool hasAttack;
	bool active;

	list<Bullet*> *bullet;

	RocketMan(void);
	RocketMan(float x, float y);

	void Update(int dt, D3DXVECTOR2* ryuPos);
	void Draw(CCamera* camera);
	void Collision(list<GameObject*> obj, int dt);
	void SetActive(float x, float y);
	//Box GetBox();

	~RocketMan(void);
};
#endif
