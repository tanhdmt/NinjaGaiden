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
	ryuAttack2 = new CTexture("Resources/ryuAttack2.png", 3, 1, 3);
	ryuSit = new CTexture("Resources/ryuSit.png", 1, 1, 1);
	ryuSitAttack = new CTexture("Resources/ryuSitAttack.png", 3, 1, 3);

	hp = new CTexture("Resources/Items/HP.png", 1, 1, 1);
	gameScore = new CTexture("Resources/Items/GameScore.png", 1, 1, 1);
	fire = new CTexture("Resources/Enemy/Fire_x2.png", 1, 1, 1);
	explosion = new CTexture("Resources/Enemy/explosion_x2.png", 1, 1, 1);
	bullet = new CTexture("Resources/Enemy/Bullet_x2.png", 1, 1, 1);
	boomerang = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
	sword = new CTexture("Resources/Enemy/Bullet_x2.png", 1, 1, 1);

	swordMan = new CTexture("Resources/Enemy/Sword_Man_x2.png", 3, 1, 3);
	rocketMan = new CTexture("Resources/Enemy/Bazoka_Man_x2.png", 1, 1, 1);
	banshee = new CTexture("Resources/Enemy/Banshee_x2.png", 3, 1, 3);
	boss = new CTexture("Resources/Enemy/Final_Boss_x2.png", 2, 1, 2);
	butterfly = new CTexture("Resources/Enemy/Butterfly_x2.png", 2, 1, 2);
	bird = new CTexture("Resources/Enemy/Bird_x2.png", 2, 1, 2);
	bat = new CTexture("Resources/Enemy/Grey_Bat_x2.png", 2, 1, 2);
	yellowDog = new CTexture("Resources/Enemy/Yellow_Dog_x2.png", 2, 1, 2);
	machineGunGuy = new CTexture("Resources/Enemy/machingunguy_x2.png", 2, 1, 2);
	runner = new CTexture("Resources/Enemy/Runner_x2.png", 2, 1, 2);
	brownBrid = new CTexture("Resources/Enemy/Brown_Bird_x2.png", 2, 1, 2);

	bonusBlue = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
	bonusRed = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
	throwStar = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
	windmillThrowStar = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
	timeFreeze = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
	spititualBlue = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
	spiritualRed = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
	restoreStrength = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
	fireWheel = new CTexture("Resources/Enemy/items_x2.png", 16, 1, 16);
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
		case EnumID::RyuAttack2_ID:
			return ryuAttack2;
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
		case EnumID::Explosion_ID:
			return explosion;
		case EnumID::Boomerang_ID:
			return boomerang;
		case EnumID::SwordMan_ID:
			return swordMan;
		case EnumID::RocketMan_ID:
			return rocketMan;
		case EnumID::Banshee_ID:
			return banshee;
		case EnumID::Boss_ID:
			return boss;
		case EnumID::Butterfly_ID:
			return butterfly;
		case EnumID::Sword_ID:
			return sword;
		case EnumID::Bird_ID:
			return bird;
		case EnumID::BrownBird_ID:
			return brownBrid;
		case EnumID::Runner_ID:
			return runner;
		case EnumID::YellowDog_ID:
			return yellowDog;
		case EnumID::MachineGunGuy_ID:
			return machineGunGuy;
		case EnumID::Bat_ID:
			return bat;
		case EnumID::BonusBlue_ID:
			return bonusBlue;
		case EnumID::BonusRed_ID:
			return bonusRed;
		case EnumID::ThrowStar_ID:
			return throwStar;
		case EnumID::WindmillThrowStar_ID:
			return windmillThrowStar;
		case EnumID::TimeFreeze_ID:
			return timeFreeze;
		case EnumID::FireWheel_ID:
			return fireWheel;
		case EnumID::SpititualBlue_ID:
			return spititualBlue;
		case EnumID::SpiritualRed_ID:
			return spiritualRed;
		case EnumID::RestoreStrength_ID:
			return restoreStrength;
	}
}