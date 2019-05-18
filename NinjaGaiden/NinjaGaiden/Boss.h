#ifndef _BOSS_H_
#define _BOSS_H_

#include "DynamicObject.h"
#include "CEnum.h"

class Boss : public DynamicObject
{
public:
	bool hasAttack;
	bool active;
	bool hasJump;
	float _heightJump;
	int timeDelay;

	GameObject* _lastCollidedGround;
	GameObject* _sideCollidedGround;
	ECollisionDirect _curCollideDir;

	Boss(void);
	Boss(float x, float y);
	void Update(int dt);
	//void Draw(CCamera* camera);
	void Collision(list<GameObject*> obj, int dt);
	ECollisionDirect GetCollisionDirect(GameObject* other);
	void SetActive(float x, float y);
	Box GetBox();

	~Boss(void);
};
#endif
