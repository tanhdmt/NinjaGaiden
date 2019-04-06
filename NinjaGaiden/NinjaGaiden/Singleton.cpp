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
}

CTexture* Singleton::getTexture(EnumID id)
{
	switch (id)
	{
		case EnumID::Ryu_ID:
			return ryu;
		case EnumID::RyuRun_ID:
			return ryuRun;
	}
}