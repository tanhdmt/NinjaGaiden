#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include "Texture.h"
#include "CEnum.h"

class Singleton
{
private:
	CTexture* ryu;
	CTexture* ryuRun;
	CTexture* ryuDeath;
	CTexture* ryuJump1;
	CTexture* ryuJump2;
	CTexture* ryuClimb;
	CTexture* ryuAttack;
	CTexture* ryuAttack2;
	CTexture* ryuSit;
	CTexture* ryuSitAttack;

	CTexture* hp;
	CTexture* gameScore;
	CTexture* fire;
	CTexture* explosion;
	CTexture* bullet;
	CTexture* boomerang;
	CTexture* sword;
	CTexture* bonusBlue;
	CTexture* bonusRed;
	CTexture* throwStar;
	CTexture* windmillThrowStar;
	CTexture* timeFreeze;
	CTexture* spititualBlue;
	CTexture* spiritualRed;
	CTexture* restoreStrength;
	CTexture* fireWheel;

	//CTexture* sword;

	CTexture* swordMan;
	CTexture* rocketMan;
	CTexture* banshee;
	CTexture* butterfly;
	CTexture* bird;
	CTexture* bat;
	CTexture* yellowDog;
	CTexture* machineGunGuy;
	CTexture* runner;
	CTexture* boss;
	CTexture* brownBrid;

	static Singleton *single;
	Singleton();

public:
	static Singleton* getInstance();
	~Singleton();
	CTexture* getTexture(EnumID id);
};

#endif#pragma once
