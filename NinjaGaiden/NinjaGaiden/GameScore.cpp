#include "GameScore.h"


void GameScore::_initialize()
{
	// init weaponSprite
	/*_vWeaponSprite = vector<CSprite*>();
	_vWeaponSprite.push_back(new CSprite(Singleton::getInstance()->getTexture(EnumID::WatchItem_ID), 1));
	_vWeaponSprite.push_back(new CSprite(Singleton::getInstance()->getTexture(EnumID::DaggerItem_ID), 1));
	_vWeaponSprite.push_back(new CSprite(Singleton::getInstance()->getTexture(EnumID::FireBombItem_ID), 1));
	_vWeaponSprite.push_back(new CSprite(Singleton::getInstance()->getTexture(EnumID::BoomerangItem_ID), 1));
	_vWeaponSprite.push_back(new CSprite(Singleton::getInstance()->getTexture(EnumID::AxeItem_ID), 1));*/

	// init hp sprite
	_hpSprite = new CSprite(Singleton::getInstance()->getTexture(EnumID::Hp_ID), 1);
	_hp2Sprite = new CSprite(Singleton::getInstance()->getTexture(EnumID::Hp2_ID), 1);

	_gameTimer = 0;
	finalScore = 0;
}

void GameScore::drawTable()
{
	// draw table
	_sprite->Draw(256, 40);
	if (weaponId != EnumID::None_ID)
	{
		switch (weaponId)
		{
		case EnumID::Boomerang_ID:
			_weaponsprite = new CSprite(Singleton::getInstance()->getTexture(weaponId), 3, 4, 0);
			break;
		case EnumID::BoomerangS_ID:
			_weaponsprite = new CSprite(Singleton::getInstance()->getTexture(weaponId), 2, 3, 0);
			break;
		case EnumID::FireWeapon_ID:
			_weaponsprite = new CSprite(Singleton::getInstance()->getTexture(weaponId), 5, 6, 0);
			break;
		}
		_weaponsprite->Draw(201, 50);
	}
	else
	{
		_weaponsprite = new CSprite();
	}
	// draw hp
	//ryu
	for (int i = 0; i < 16; i++)
	{
		_hp2Sprite->DrawIndex(0, 345 + 10 * i, 40);
	}
	for (int i = 0; i < _ryuHP; i++)
	{
		_hpSprite->DrawIndex(0, 345 + 10 * i, 40);
	}
	//// boss
	for (int i = 0; i < 16; i++)
	{
		_hp2Sprite->DrawIndex(0, 345 + 10 * i, 66);
	}
	for (int i = 0; i < _enemyHP; i++)
	{
		_hpSprite->DrawIndex(0, 345 + 10 * i, 66);
	}
	//for (int i = _enemyHP; i < MAX_HP; i++)
	//{
	//	_hpSprite->DrawIndex(1, 120 + 10 * i, 80);
	//}


	// draw weapon
	/*if (_currentWeapon != -1)
	{
		_vWeaponSprite.at(_currentWeapon)->Draw(367, 64);
	}*/
}

void GameScore::drawScore()
{
	_arial->onLost();
	//_arial->render((char*)"SCORE", 5, 10);
	_arial->render(_ryuScore, 105, 3);
	//_arial->render((char*)"TIME", 200, 10);
	_arial->render(_gameTimer / 1000, 105, 28);
	//_arial->render((char*)"STAGE", 380, 10);
	_arial->render((char*)"3-", 345, 3);
	_arial->render(_gameStage, 379, 3);
	//_arial->render((char*)"PLAYER", 5, 40);
	//_arial->render((char*)"ENEMY", 5, 70);
	//_arialSmall->render(_weaponCount, 440, 47);
	_arial->render(_liveCount, 50, 54);
	_arial->render(_ryuSpiri, 136, 54);
}

void GameScore::initTimer(int deltaTime_)
{
	_gameTimer = deltaTime_ * 1000;
}

int GameScore::getTimer()
{
	return _gameTimer / 1000;
}

void GameScore::SetTimer(int x)
{
	_gameTimer += x;
}

int GameScore::GetWeaponCount()
{
	return _weaponCount;
}

void GameScore::SetWeaponCount(int x)
{
	_weaponCount += x;
}

void GameScore::SetRyuScore(int x)
{
	_ryuScore += x;
}

GameScore::GameScore(void)
{

}

GameScore::GameScore(LPDIRECT3DDEVICE9 d3ddev_, int size_, int screenWidth_, int screenHeight_)
{
	this->_initialize();
	_sprite = new CSprite(Singleton::getInstance()->getTexture(EnumID::GameScore_ID), 1);
	_arial = new CText(d3ddev_, size_, screenWidth_, screenHeight_ / 2);
	_arialSmall = new CText(d3ddev_, size_ - 3, screenWidth_, screenHeight_ / 2);
}


void GameScore::updateScore(int gameStage_, int ryuScore_, int deltaTime_, int ryuHP_, int liveCount_, EnumID weaponID_, int weaponCount_, int enemyHP_, int ryuSpiri_)
{
	_gameStage = gameStage_;
	if (enemyHP_ <= 0 && _gameTimer > 0)
	{
		finalScore += 200;
	}
	_ryuScore = ryuScore_ +  finalScore;
	_ryuSpiri = ryuSpiri_;
	weaponId = weaponID_;
	if (_gameTimer <= 0)
	{
	}
	else
		_gameTimer = _gameTimer - deltaTime_;
	_weaponCount = weaponCount_;
	_ryuHP = ryuHP_;
	_enemyHP = enemyHP_;
	_liveCount = liveCount_;

	switch (weaponID_)
	{
	/*case Watch_ID:
		_currentWeapon = 0;
		break;
	case Dagger_ID:
		_currentWeapon = 1;
		break;
	case FireBomb_ID:
		_currentWeapon = 2;
		break;
	case Boomerang_ID:
		_currentWeapon = 3;
		break;
	case Axe_ID:
		_currentWeapon = 4;
		break;*/
	default:
		_currentWeapon = -1;
		break;
	}

}


GameScore::~GameScore(void)
{
}
