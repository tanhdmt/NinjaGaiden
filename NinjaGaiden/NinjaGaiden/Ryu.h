#ifndef _RYU_H_
#define _RYU_H_
#include "DynamicObject.h"

using namespace std;

class Ryu : public DynamicObject
{
public:
	CSprite* ryuIdle;
	CSprite* ryuRun;
	CSprite* ryuJump;
	CSprite* ryuClimb;

	float _vLast;
	Action _action;
	GameObject* _lastCollidedGround;
	ECollisionDirect _curCollideDir;
	GameObject* _sideCollidedGround;
	//dem so object va cham
	int _demVaCham;
	bool onLand;
	bool _hasJump;
	float _heightJump;

	Ryu(void);
	Ryu(int, int);
	~Ryu(void);

	void Update(int dt);
	void TurnLeft();
	void TurnRight();
	void Jump();
	void Climb();
	void Stop();
	void Draw(CCamera*);
	ECollisionDirect GetCollisionDirect(GameObject* other);
	Box GetBox();
	void Collision(list<GameObject*> &obj, float dt);

	void Initialize();
	D3DXVECTOR2* getPos();
	
};
#endif
