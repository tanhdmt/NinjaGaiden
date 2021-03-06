#ifndef _RYU_H_
#define _RYU_H_
#include "DynamicObject.h"
#include "Explosion.h"
#include "Boomerang.h"
#include "Items.h"

using namespace std;

class Ryu : public DynamicObject
{
public:
	CSprite* ryuIdle;
	CSprite* ryuRun;
	CSprite* ryuJump;
	CSprite* ryuClimb;
	CSprite* ryuAttack;
	CSprite* ryuAttack2;
	CSprite* ryuSit;
	CSprite* ryuSitAttack;

	float _vLast;
	Action _action;
	GameObject* _lastCollidedGround;
	ECollisionDirect _curCollideDir;
	GameObject* _sideCollidedGround;
	Explosion* explosion;
	list<Items*> *items;
	list<Weapon*> *_weapon;
	EnumID _weaponID;
	//dem so object va cham
	int _demVaCham;
	int timeCounter;
	bool onLand;
	bool _hasJump;
	float _heightJump;
	bool _hasAttack2;
	bool _hasClimb;
	bool _hasSit;
	bool _isFall;
	bool useWeapon;
	bool isFreeze;
	int ryuLife;
	int ryuHp;
	int ryuSpiri;
	int ryuScore;
	bool _allowPress;
	bool bActiveHurt;
	bool _bHurt;
	bool isHurt;
	int bossHp;
	int leftTimer;

	Ryu(void);
	Ryu(int, int);
	~Ryu(void);

	void Update(int dt);
	void TurnLeft();
	void TurnRight();
	void Jump();
	void Climb(bool isUp);
	void Attack(bool isUseWeapon);
	void Sit();
	void SitAttack();
	void Stop();
	void Draw(CCamera*);
	bool IsHurt();
	void UseWeapon();
	void SetWeapon();
	void ChangeWeapon(EnumID idWeapon);
	ECollisionDirect GetCollisionDirect(GameObject* other);
	Box GetBox();
	void Collision(list<GameObject*> &obj, float dt, bool isDynamic);

	void Initialize();
	D3DXVECTOR2* getPos();
	int getWidth();
	int getHeight();
	void Reset();
	
};
#endif
