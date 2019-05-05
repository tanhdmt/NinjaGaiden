#ifndef _SWORDMAN_H_
#define _SWORDMAN_H_

#include "DynamicObject.h"
#include "CEnum.h"

class SwordMan : public DynamicObject
{
public:
	bool hasAttack;
	bool active;

	GameObject* _lastCollidedGround;
	GameObject* _sideCollidedGround;
	ECollisionDirect _curCollideDir;

	SwordMan(void);
	SwordMan(float x, float y);
	void Update(int dt);
	//void Draw(CCamera* camera);
	void Collision(list<GameObject*> obj, int dt);
	ECollisionDirect GetCollisionDirect(GameObject* other);
	void SetActive(float x, float y);
	Box GetBox();

	~SwordMan(void);
};
#endif
