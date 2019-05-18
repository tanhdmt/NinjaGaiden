#include "Singleton.h"
#include <string>
#include <sstream>
#include <windows.h>
#include <iostream>
#include <malloc.h>

using namespace std;

Singleton* Singleton::single = NULL;

Singleton* Singleton::getInstance()
{
	if (single == NULL)
		single = new Singleton();
	return single;
}

Singleton::Singleton()
{
	ryu = new CTexture("Resources/ryuIdle.png", 1, 1, 1);
	ryuRun = new CTexture("Resources/ryuRun.png", 3, 1, 3);
	ryuJump1 = new CTexture("Resources/ryuJump.png", 4, 1, 4);
	ryuClimb = new CTexture("Resources/ryuClimb.png", 2, 1, 2);
	ryuAttack = new CTexture("Resources/ryuAttack.png", 3, 1, 3);
	ryuSit = new CTexture("Resources/ryuSit.png", 1, 1, 1);
	ryuSitAttack = new CTexture("Resources/ryuSitAttack.png", 3, 1, 3);

	hp = new CTexture("Resources/Items/HP.png", 1, 1, 1);
	gameScore = new CTexture("Resources/Items/GameScore.png", 1, 1, 1);
	fire = new CTexture("Resources/Enemy/Fire_x2.png", 1, 1, 1);
	bullet = new CTexture("Resources/Enemy/Bullet_x2.png", 1, 1, 1);

	swordMan = new CTexture("Resources/Enemy/Sword_Man_x2.png", 3, 1, 3);
	rocketMan = new CTexture("Resources/Enemy/Bazoka_Man_x2.png", 1, 1, 1);
	banshee = new CTexture("Resources/Enemy/Banshee_x2.png", 3, 1, 3);
	boss = new CTexture("Resources/Enemy/Final_Boss_x2.png", 2, 1, 2);
}

CTexture* Singleton::getTexture(EnumID id)
{
	switch (id)
	{
		case EnumID::Ryu_ID:
			return ryu;
		case EnumID::RyuRun_ID:
			return ryuRun;
		case EnumID::RyuJump1_ID:
			return ryuJump1;
		case EnumID::RyuClimb_ID:
			return ryuClimb;
		case EnumID::RyuAttack_ID:
			return ryuAttack;
		case EnumID::RyuSit_ID:
			return ryuSit;
		case EnumID::RyuSitAttack_ID:
			return ryuSitAttack;
		case EnumID::Hp_ID:
			return hp;
		case EnumID::GameScore_ID:
			return gameScore;
		case EnumID::Bullet_ID:
			return bullet;
		case EnumID::Fire_ID:
			return fire;
		case EnumID::SwordMan_ID:
			return swordMan;
		case EnumID::RocketMan_ID:
			return rocketMan;
		case EnumID::Banshee_ID:
			return banshee;
		case EnumID::Boss_ID:
			return boss;
	}
}