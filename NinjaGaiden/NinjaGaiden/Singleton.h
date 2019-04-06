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

	static Singleton *single;
	Singleton();

public:
	static Singleton* getInstance();
	~Singleton();
	CTexture* getTexture(EnumID id);
};

#endif#pragma once
