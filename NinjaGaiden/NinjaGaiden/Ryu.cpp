#include "Ryu.h"

#define SPEED_X 0.5f
#define SPEED_Y 0.8f
#define MAX_HEIGHT 120.0f
#define HURT_STATE 25
bool isCol = false;
bool isAtk = false;
int timec = 0;

Ryu::Ryu(void) : DynamicObject() {

}

Ryu::Ryu(int _posX, int _posY) : DynamicObject(_posX, _posY, 0, -SPEED_Y, EnumID::Ryu_ID) 
{
	_action = Action::Idle;
	_vLast = 0.2f;
	_allowPress = true;
	_lastCollidedGround = nullptr;
	_hasJump = false;
	_hasAttack = false;
	_hasAttack2 = false;
	_hasClimb = false;
	_hasSit = false;
	_isFall = false;
	_heightJump = 0.0f;
	ryuLife = 3;
	ryuScore = 0;
	ryuSpiri = 0;
	ryuHp = 16;
	isHurt = false;
	onLand = false;
	_weapon = new list<Weapon*>();
	items = new list<Items*>();
	_weaponID = EnumID::None_ID;
	isFreeze = false;
	timeCounter = 0;
	bossHp = 16;

	ryuRun = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuRun_ID), 0, 2, 18);
	ryuJump = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuJump1_ID), 0, 3, 18);
	ryuClimb = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuClimb_ID), 0, 1, 50);
	ryuAttack = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuAttack_ID), 0, 2, 40);
	ryuAttack2 = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuAttack2_ID), 0, 2, 40);
	ryuSit = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuSit_ID), 1);
	ryuSitAttack = new CSprite(Singleton::getInstance()->getTexture(EnumID::RyuSitAttack_ID), 0, 2, 40);
	explosion = new Explosion(_posX, _posY, EnumID::Explosion_ID);
	Initialize();
}

void Ryu::Update(int dt) {
	list<Weapon*>::iterator it = _weapon->begin();
	while (it != _weapon->end())
	{
		if (!(*it)->active)
			_weapon->erase(it++);
		else
		{
			(*it)->Update(dt);
			++it;
		}
	}
	list<Items*>::iterator it2 = items->begin();
	while (it2 != items->end())
	{
		if (!(*it2)->active)
			items->erase(it2++);
		else
		{
			(*it2)->Update(dt);
			++it2;
		}
	}
	switch (_action)
	{
		case Action::Run_Left:
		case Action::Run_Right:
			ryuRun->Update(dt);
			break;
		case Action::Jump1:
			ryuJump->Update(dt);
			break;
		case Action::Attack:
			ryuAttack->Update(dt);
			break;
		case Action::Attack2:
			ryuAttack2->Update(dt);
			break;
	}
	//freeze
	if (isFreeze) 
	{
		timeCounter += dt;
		if (timeCounter >= 1000)
		{
			isFreeze = false;
			timeCounter = 0;
		}
	}

	if (!_hasClimb)
	{
		posX += vX * dt;
	}
	if (!onLand || _hasJump || _hasClimb)
	{
		posY += vY * dt;
	}
	if (_hasJump) {
		if (!bActiveHurt)
		{
			ryuJump->Update(dt);
			_heightJump += vY * dt;
			if (_heightJump >= MAX_HEIGHT)
			{
				vY = -SPEED_Y;
			}
		}
		else
		{
			if (_heightJump < 0)
				_heightJump = 0;
			_heightJump += vY * dt;
			if (_heightJump >= 80)
			{
				vY = -SPEED_Y;
			}
		}
	}
	if (_hasClimb && vY != 0)
	{
		ryuClimb->Update(dt);
	}
	if (_hasAttack)
	{	
		if (!_hasSit)
		{
			ryuAttack->Update(dt);
			if (ryuAttack->GetIndex() == 0 && isAtk) {
				_hasAttack = false;
				isAtk = false;
				return;
			}
			if (ryuAttack->GetIndex() == 1) {
				isAtk = true;
			}
			_heightJump += vY * dt;
			int maxHeight;
			if (!_isFall)
				maxHeight = MAX_HEIGHT;
			else
				maxHeight = 300.0f;
			if (_heightJump >= maxHeight)
			{
				vY = -SPEED_Y;
			}
		}
		else
		{
			ryuSitAttack->Update(dt);
			if (ryuSitAttack->GetIndex() == 0 && isAtk) {
				_hasAttack = false;
				isAtk = false;
				return;
			}
			if (ryuSitAttack->GetIndex() == 1) {
				isAtk = true;
			}
			vX = 0;
			vY = -SPEED_Y;
		}
	}
	if (ryuSpiri <= 0)
		_hasAttack2 = false;
	if (_hasAttack2 && _weaponID != EnumID::None_ID)
	{
		ryuAttack2->Update(dt);
		if (ryuAttack2->GetIndex() == 0 && isAtk) {
			_hasAttack2 = false;
			isAtk = false;
			return;
		}
		if (ryuAttack2->GetIndex() == 1) {
			isAtk = true;
		}
		_heightJump += vY * dt;
		int maxHeight;
		if (!_isFall)
			maxHeight = MAX_HEIGHT;
		else
			maxHeight = 300.0f;
		if (_heightJump >= maxHeight)
		{
			vY = -SPEED_Y;
		}
	}
	if (_hasSit && !_hasAttack)
	{
		ryuSit->Update(dt);
		vX = 0;
		vY = -SPEED_Y;
	}
	//nhay len sau khi rot dat
	if (posY < -80)
	{
		if (ryuLife > 0)
		{
			ryuLife--;
			posY = 250;
			_isFall = true;
			_hasJump = true;
			Jump();
			onLand = false;
			//vY = SPEED_Y;
			vX = _vLast;
		}
	}
	if (explosion->active)
		explosion->Update(dt);
	if (ryuLife == 0)
	{
		ryuLife = 3;
		ryuHp = 16;
	}
}

Box Ryu::GetBox()
{
	if (_hasSit)
		return Box(posX - ryuSit->_texture->FrameWidth / 2, (posY + ryuSit->_texture->FrameHeight / 2), ryuSit->_texture->FrameWidth, ryuSit->_texture->FrameHeight, vX, vY);
	else if (_hasClimb)
		return Box(posX - ryuClimb->_texture->FrameWidth / 2, (posY + ryuClimb->_texture->FrameHeight / 2), ryuClimb->_texture->FrameWidth, ryuClimb->_texture->FrameHeight, vX, vY);
	if ((vX != 0 || (vY != 0 && _hasJump)) && !_hasClimb)
	{
		if (_hasJump)
			return Box(posX - ryuJump->_texture->FrameWidth / 2, (posY + ryuJump->_texture->FrameHeight / 2), ryuJump->_texture->FrameWidth, ryuJump->_texture->FrameHeight, vX, vY);
		return Box(posX - ryuRun->_texture->FrameWidth / 2, (posY + ryuRun->_texture->FrameHeight / 2), ryuRun->_texture->FrameWidth, ryuRun->_texture->FrameHeight, vX, vY);
	}
	if (_hasAttack)
	{
		return Box(posX - ryuAttack->_texture->FrameWidth / 2, (posY + ryuAttack->_texture->FrameHeight / 2), ryuAttack->_texture->FrameWidth, ryuAttack->_texture->FrameHeight, vX, vY);
	}
	return Box(posX - sprite->_texture->FrameWidth / 2 , (posY + sprite->_texture->FrameHeight / 2), sprite->_texture->FrameWidth, sprite->_texture->FrameHeight, vX, vY);
}

void Ryu::Collision(list<GameObject*> &obj, float dt, bool isDynamic)
{
	for (list<Weapon*>::iterator i = _weapon->begin(); i != _weapon->end(); i++)
	{
		if ((*i)->active)
		{
			if ((*i)->id == EnumID::Boomerang_ID || (*i)->id == EnumID::BoomerangS_ID)
				(*i)->Collision(this->GetBox(), obj, dt);
			(*i)->Collision(obj, dt);
			/*point += (*i)->point;
			(*i)->point = 0;*/
		}
	}
	for (list<Items*>::iterator i = items->begin(); i != items->end(); i++)
	{
		if ((*i)->active)
		{
			(*i)->Collision(this->GetBox(), obj, dt);
			ryuScore += (*i)->ryuScore;
			ryuSpiri += (*i)->ryuSpiri;
			ryuHp += (*i)->ryuHp;
			if ((*i)->weaponID != EnumID::None_ID)
				_weaponID = (*i)->weaponID;
			if (ryuHp > 16)
			{
				ryuHp = 16;
			}
			if ((*i)->ryuFreeze)
				isFreeze = true;
			//ryuHp = 
			/*point += (*i)->point;
			(*i)->point = 0;*/
		}
	}
	int countCollis = 0;
	for (list<GameObject*>::iterator _itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);
		
		if (other->type == ObjectType::Enemy_Type)
		{
			other->SetActive(this->posX, this->posY);
		}
		if (!other->active)
		{

		}
		else 
		{
			float moveX;
			float moveY;
			float normalx;
			float normaly;

			Box boxRyu = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(boxRyu, boxOther, moveX, moveY) == true)
			{
				float collisiontime = SweptAABB(boxRyu, boxOther, normalx, normaly, dt);
				ECollisionDirect dir = this->GetCollisionDirect(other);
				switch (other->id)
				{
				case EnumID::Ground1_ID:
				{
					countCollis++;
					if (!_isFall)
					{
						//va cham canh
						if (dir == ECollisionDirect::Colls_Left || dir == ECollisionDirect::Colls_Right)
						{
							vX = 0;
							if (dir == ECollisionDirect::Colls_Right && _action == Action::Run_Right)
							{
								vX = SPEED_X;
							}
							else if (dir == ECollisionDirect::Colls_Left && _action == Action::Run_Left)
							{
								vX = -SPEED_X;
							}
						}
						//va cham tren
						else if (dir == ECollisionDirect::Colls_Top)
						{
							if (!_hasClimb)
							{
								vY = -(SPEED_Y);
								onLand = false;
							}
							else
							{
								vY = -(SPEED_Y) * 0.1;
								//if (_action != Action::Climb)
								//{
								//	vX = SPEED_X;
								//}
								onLand = false;
							}
						}
					}


					//xet cham dat
					if (vY < 0  && dir == ECollisionDirect::Colls_Bot)
					{
						//posY += moveY;
						onLand = true;
						_hasJump = false;
						_isFall = false;
					}
					if (_hasClimb && dir == ECollisionDirect::Colls_Bot)
					{
						vY = (SPEED_Y) * 0.1;
					}
					/*if (vX != 0 && moveX != 0)
					{
						posX += moveX;
					}*/
					break;
				}
				case EnumID::Ground2_ID:
				{
					countCollis++;
					if (dir == ECollisionDirect::Colls_Bot && vY < 0 && !_hasClimb)
					{
						onLand = false;
						_hasJump = false;
						_hasClimb = false;
					}
					break;
				}
				case EnumID::Ground4_ID:
				{
					if (countCollis>0)
					{
						if (vY < 0 && !_hasClimb)
						{
							onLand = true;
							_hasJump = false;
							_hasClimb = false;
						}
						else 
						{
							onLand = false;
							_hasJump = true;
							_hasClimb = false;
						}
					}
					else
					{
						onLand = false;
					}
					break;
				}
				case EnumID::Stair_ID:
				{
					//va cham canh
					if (dir == ECollisionDirect::Colls_Left)
					{
						if (_hasJump && vX < 0)
						{
							_hasClimb = false;
						}
						else {
							_hasJump = false;
							_hasClimb = true;

						}
					}
					break;
				}
				case EnumID::Boss_ID:
				{
					if (_hasAttack || (_hasAttack2 && _weaponID != EnumID::None_ID))
					{
						int enemyPosX = other->getX();
						int enemyPosY = other->getY();
						//other->active = false;
						//explosion->setX(enemyPosX);
						//explosion->setY(enemyPosY);
						//explosion->active = true;
						timec += dt;
						if (timec > 100)
						{
							bossHp -=5;
							other->bossHp = bossHp;
							timec = 0;
						}
					}
					else
					{
						//if ((!bActiveHurt && other->bossHp > 0))
						//{
						//	bActiveHurt = true;
						//	_allowPress = false;
						//	isHurt = true;
						//	_localHurtTime = GetTickCount();
						//	isCol = true;
						//	_hasJump = true;
						//	ryuJump->SelectIndex(0);
						//	if (dir == ECollisionDirect::Colls_Left)
						//	{
						//		vX = -0.3f;
						//		//isColRight = false;
						//	}
						//	else if (dir == ECollisionDirect::Colls_Right)
						//	{
						//		vX = 0.3f;
						//		//_vLast = vX;
						//		//isColRight = true;
						//	}
						//	vY = 0.4f;

						//	if (ryuHp > 0)
						//		ryuHp--;
						//	else {
						//		ryuHp = 16;
						//		ryuLife--;
						//	}
						//	
						//	//vY = 1.5f;
						//}
					}
				}
				break;
				default:
					break;
				}
				if ((other->type == ObjectType::Enemy_Type && other->id != EnumID::Boss_ID))
				{
					if (_hasAttack || (_hasAttack2 && _weaponID != EnumID::None_ID))
					{
						if ((_vLast > 0 && (other->vX < 0 || (other->vX > 0 && posX < other->getX()))) || (_vLast < 0 && (other->vX > 0 || (other->vX < 0 && posX > other->getX()))))
						{
							int enemyPosX = other->getX();
							int enemyPosY = other->getY();
							other->active = false;
							explosion->setX(enemyPosX);
							explosion->setY(enemyPosY);
							explosion->active = true;
							ryuScore += 100;
						}
					}
					else
					{
						//if (!bActiveHurt)
						//{
						//	bActiveHurt = true;
						//	_allowPress = false;
						//	isHurt = true;
						//	_localHurtTime = GetTickCount();
						//	isCol = true;
						//	_hasJump = true;
						//	ryuJump->SelectIndex(0);
						//	if (dir == ECollisionDirect::Colls_Left)
						//	{
						//		vX = -0.3f;
						//		//isColRight = false;
						//	}
						//	else if (dir == ECollisionDirect::Colls_Right)
						//	{
						//		vX = 0.3f;
						//		//_vLast = vX;
						//		//isColRight = true;
						//	}
						//	vY = 0.4f;

						//	if (ryuHp > 0)
						//		ryuHp--;
						//	else {
						//		ryuHp = 16;
						//		ryuLife--;
						//	}
						//	
						//	//vY = 1.5f;
						//}
					}
				}
				else if (other->type == ObjectType::Item_Type)
				{
					if (_hasAttack || (_hasAttack2 && _weaponID != EnumID::None_ID))
					{
						if ((_vLast > 0 && (other->vX < 0 || (other->vX > 0 && posX < other->getX()))) || (_vLast < 0 && (other->vX > 0 || (other->vX < 0 && posX > other->getX()))))
						{
							int enemyPosX = other->getX();
							int enemyPosY = other->getY();
							other->active = false;
							explosion->setX(enemyPosX);
							explosion->setY(enemyPosY);
							explosion->active = true;
							switch (other->id)
							{
							case EnumID::Butterfly_BlueStrengthItem_ID:
							case EnumID::Bird_BlueStrengthItem_ID:
							{
								items->push_back(new Items(enemyPosX, enemyPosY, EnumID::SpititualBlue_ID));
							}
							break;
							case EnumID::Butterfly_RedStrengthItem_ID:
							case EnumID::Bird_RedStrengthItem_ID:
							{
								items->push_back(new Items(enemyPosX, enemyPosY, EnumID::SpiritualRed_ID));
							}
							break;
							case EnumID::Butterfly_TimeItem_ID:
							{
								items->push_back(new Items(enemyPosX, enemyPosY, EnumID::TimeFreeze_ID));
							}
							break;
							case EnumID::Butterfly_ThrowingItem_ID:
							case EnumID::Bird_ThrowingItem_ID:
							{
								items->push_back(new Items(enemyPosX, enemyPosY, EnumID::ThrowStar_ID));
							}
							break;
							case EnumID::Butterfly_RedBonusItem_ID:
							case EnumID::Bird_RedBonusItem_ID:
							{
								items->push_back(new Items(enemyPosX, enemyPosY, EnumID::BonusRed_ID));
							}
							break;
							case EnumID::Butterfly_BlueBonusItem_ID:
							case EnumID::Bird_BlueBonusItem_ID:
							{
								items->push_back(new Items(enemyPosX, enemyPosY, EnumID::BonusBlue_ID));
							}
							break;
							case EnumID::Butterfly_FireWheelItem_ID:
							case EnumID::Bird_FireWheelItem_ID:
							{
								items->push_back(new Items(enemyPosX, enemyPosY, EnumID::FireWheel_ID));
							}
							break;
							case EnumID::Butterfly_RestoringItem_ID:
							{
								items->push_back(new Items(enemyPosX, enemyPosY, EnumID::RestoreStrength_ID));
							}
							break;
							}
							//ryuScore += 100;

						}
					}
				}
			}
			else
			{
				if (other->id == EnumID::Boss_ID)
				{
					if (other->ryuHurt && !bActiveHurt)
					{
						ECollisionDirect dir = this->GetCollisionDirect(other);
						bActiveHurt = true;
						_allowPress = false;
						isHurt = true;
						_localHurtTime = GetTickCount();
						isCol = true;
						_hasJump = true;
						ryuJump->SelectIndex(0);
						if (dir == ECollisionDirect::Colls_Left)
						{
							vX = -0.3f;
							//isColRight = false;
						}
						else if (dir == ECollisionDirect::Colls_Right)
						{
							vX = 0.3f;
							//_vLast = vX;
							//isColRight = true;
						}
						vY = 0.4f;

						if (ryuHp > 0)
							ryuHp--;
						else {
							ryuHp = 16;
							ryuLife--;
						}
						other->ryuHurt = false;
					}
				}
			}
		}
	}
	if (countCollis == 0 && onLand == true && !isDynamic)
	{
		onLand = false;
	}
}

void Ryu::Draw(CCamera* camera) {
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (explosion->active)
		explosion->Draw(camera);
	if (!IsHurt())
	{
		for (list<Weapon*>::iterator i = _weapon->begin(); i != _weapon->end(); i++)
		{
			if ((*i)->active)
				(*i)->Draw(camera);
		}
		for (list<Items*>::iterator i = items->begin(); i != items->end(); i++)
		{
			if ((*i)->active)
				(*i)->Draw(camera);
		}
		if ((vX != 0 || (vY != 0 && _hasJump)) && !_hasClimb)
		{
			if (_vLast > 0)
			{
				if (_hasJump)
				{
					ryuJump->Draw(center.x, center.y);
					return;
				}
				ryuRun->Draw(center.x, center.y);
			}
			else {
				if (_hasJump)
				{
					ryuJump->DrawFlipX(center.x, center.y);
					return;
				}
				ryuRun->DrawFlipX(center.x, center.y);
			}
		}
		else if (_hasClimb)
		{
			ryuClimb->Draw(center.x, center.y);
		}
		else if (_hasSit)
		{
			if (_hasAttack)
			{
				if (_vLast > 0)
				{
					ryuSitAttack->Draw(center.x + 23, center.y);
					return;
				}
				else {
					ryuSitAttack->DrawFlipX(center.x - 23, center.y);
					return;
				}
			}
			if (_vLast > 0)
			{
				ryuSit->Draw(center.x, center.y);
			}
			else {
				ryuSit->DrawFlipX(center.x, center.y);
			}
		}
		else
		{
			if (_vLast > 0)
			{
				if (_hasAttack)
				{
					ryuAttack->Draw(center.x + 23, center.y);

					return;
				}
				if (_hasAttack2 && _weaponID != EnumID::None_ID)
				{
					ryuAttack2->Draw(center.x + 23, center.y);

					return;
				}
				sprite->Draw(center.x, center.y);
			}
			else {
				if (_hasAttack)
				{
					ryuAttack->DrawFlipX(center.x - 23, center.y);
					return;
				}
				if (_hasAttack2 && _weaponID != EnumID::None_ID)
				{
					ryuAttack2->DrawFlipX(center.x + 23, center.y);

					return;
				}
				sprite->DrawFlipX(center.x, center.y);
			}
		}
	}
}

void Ryu::TurnLeft()
{
	if (_allowPress)
	{
		vX = -SPEED_X;
		_vLast = vX;
		_action = Action::Run_Left;
		_hasClimb = false;
		_hasSit = false;
		onLand = false;
	}
}

void Ryu::TurnRight() 
{
	if (_allowPress)
	{
		vX = SPEED_X;
		_vLast = vX;
		_action = Action::Run_Right;
		_hasClimb = false;
		_hasSit = false;
		onLand = false;
	}
}

void Ryu::Climb(bool isUp)
{
	if (_allowPress)
	{
		if (_hasClimb)
		{
			if (isUp)
				vY = SPEED_Y * 0.5;
			else
				vY = -(SPEED_Y * 0.5);
			vX = 0;
			_action = Action::Climb;
		}
	}
}

void Ryu::Sit()
{
	if (_allowPress)
	{
		if (!_hasSit)
		{
			_hasSit = true;
			if (!_hasAttack)
				_action = Action::Sit;
			else
				_action = Action::SitAttack;
			onLand = false;
		}
	}
}
void Ryu::Jump()
{
	if (_allowPress)
	{
		if (!_hasJump)
		{
			vX = 0;
			vY = SPEED_Y;
			_heightJump = 0;
			ryuJump->SelectIndex(0);
			_action = Action::Jump1;
			_hasJump = true;
			_hasClimb = false;
			_hasSit = false;
			onLand = false;
		}
	}
}
void Ryu::Attack(bool isUseWeapon)
{
	if (_allowPress)
	{
		if (!isUseWeapon)
		{
			if (!_hasAttack)
			{
				_hasJump = false;
				ryuAttack->SelectIndex(0);
				_action = Action::Attack;
				_hasAttack = true;
			}
		}
		else
		{
			if (!_hasAttack2 && ryuSpiri > 0 && _weapon->size() == 0)
			{
				useWeapon = true;
				_hasJump = false;
				ryuAttack2->SelectIndex(0);
				_action = Action::Attack2;
				_hasAttack2 = true;
				//_weaponID = EnumID::BoomerangS_ID;
				this->SetWeapon();
			}
		}
	}
}
void Ryu::UseWeapon()
{
	if (_weaponID != EnumID::None_ID)
	{
		if (!useWeapon)
		{
			useWeapon = true;
		}
	}
}

void Ryu::SetWeapon()
{
	switch (_weaponID)
	{
	case EnumID::Boomerang_ID:
	{
		_weapon->push_back(new Boomerang(posX, posY, _vLast, EnumID::Boomerang_ID));
		ryuSpiri -= 5;
	}
		break;
	case EnumID::BoomerangS_ID:
	{
		_weapon->push_back(new Boomerang(posX, posY, _vLast, EnumID::BoomerangS_ID));
		ryuSpiri -= 3;
	}
		break;
		/*case EnumID::FireWeapon_ID:
			_weapon->push_back(new Boomerang(posX, posY, _vLast));
			break;
		}*/
	}
	if (ryuSpiri < 0)
		ryuSpiri = 0;
	//_hasWeapon = false;
}

void Ryu::ChangeWeapon(EnumID idWeapon)
{
	_weaponID = idWeapon;
}

void Ryu::Initialize()
{
	sprite->SelectIndex(0);
	_bHurt = false;
}

bool Ryu::IsHurt()
{
	if (!bActiveHurt)
		return false;
	bool result = _bHurt;
	DWORD now = GetTickCount();
	DWORD deltaTime = now - _localHurtTime;
	if (deltaTime >= 1000)
	{
		bActiveHurt = false;
		isCol = false;
		_allowPress = true;
		isHurt = false;
	}
	if (deltaTime % (int)(1000 / HURT_STATE) < 15)
	{
		_bHurt = !_bHurt;
	}
	return result;
}

void Ryu::Stop()
{
	if (!_hasClimb)
	{
		if (!_hasJump) vX = 0;
		_action = Action::Idle;
		//_hasAttack = false;
		//_hasSit = false;
	}
	else
	{
		ryuClimb->SelectIndex(0);
		vY = 0;
	}
}

ECollisionDirect Ryu::GetCollisionDirect(GameObject* other)
{
	/*float x = (this->posX) - (other->posX);
	float y = (this->posY) - (other->posY);*/
	float x = (this->posX-(this->getWidth()/2)) - (other->posX-(other->getWidth()/2));
	float y = (this->posY+ (this->getHeight() / 2)) - (other->posY+(other->getHeight() / 2));
	if (abs(x) > abs(y)) {
		if (x < 0)
			return ECollisionDirect::Colls_Left;
		else if (x > 0)
			return ECollisionDirect::Colls_Right;
	}
	else
	{
		if (y < 0)
			return ECollisionDirect::Colls_Top;
		else if (y > 0)
			return ECollisionDirect::Colls_Bot;
	}

	return ECollisionDirect::Colls_None;
}

D3DXVECTOR2* Ryu::getPos()
{
	return new D3DXVECTOR2(this->posX, this->posY);
}

int Ryu::getWidth()
{
	/*if (_hasSit)
		return ryuSit->_texture->FrameWidth;
	if ((vX != 0 || (vY != 0 && _hasJump)) && !_hasClimb)
	{
		if (_hasJump)
			return ryuJump->_texture->FrameWidth;
		return ryuRun->_texture->FrameWidth;
	}*/
	if (_hasJump)
		return ryuJump->_texture->FrameWidth;
	return sprite->_texture->FrameWidth;
}

int Ryu::getHeight()
{
	/*if (_hasSit)
		return ryuSit->_texture->FrameHeight;
	if ((vX != 0 || (vY != 0 && _hasJump)) && !_hasClimb)
	{
		if (_hasJump)
			return ryuJump->_texture->FrameHeight;
		return ryuRun->_texture->FrameHeight;
	}*/
	if (_hasJump)
		return ryuJump->_texture->FrameWidth;
	return sprite->_texture->FrameHeight;
}
void Ryu::Reset()
{
	_action = Action::Idle;
	_vLast = 0.2f;
	_allowPress = true;
	_lastCollidedGround = nullptr;
	_hasJump = false;
	_hasAttack = false;
	_hasAttack2 = false;
	_hasClimb = false;
	_hasSit = false;
	_isFall = false;
	_heightJump = 0.0f;
	//ryuLife = 3;
	ryuScore = 0;
	ryuHp = 16;
	isHurt = false;
	onLand = false;
	_weapon = new list<Weapon*>();
	items = new list<Items*>();
	_weaponID = EnumID::None_ID;
	Initialize();
	this->setX(100);
	this->setY(400);
}

Ryu::~Ryu(void)
{

}