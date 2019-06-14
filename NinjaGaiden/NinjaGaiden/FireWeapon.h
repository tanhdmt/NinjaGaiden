#ifndef _FIREWEAPON_H_
#define _FIREWEAPON_H_

#include "DynamicObject.h"
#include "Fire.h"

class FireWeapon : public DynamicObject
{
	int _timeSpawn;
public:
	Fire* fire;
	FireWeapon(void);
	FireWeapon(float x, float y, float _huong, EnumID id);
	void Update(int dt);
	void Draw(CCamera* camera);
	~FireWeapon(void);
};

#endif