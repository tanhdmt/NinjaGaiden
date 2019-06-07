#include <list>
#include <map>
#include "Ryu.h"
#include "SwordMan.h"
#include "RocketMan.h"
#include "Banshee.h"
#include "Boss.h"
#include "Ground.h"
#include "Singleton.h"
#include "Camera.h"
#include "Butterfly.h"
#include "Banshee.h"
#include "Bat.h"
#include "BrownBird.h"
#include "MachineGunGuy.h"
#include "YellowDog.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <time.h>
#include <random>

//using namespace std;

class QGameObject
{
protected:
	D3DXVECTOR2 posDoor;
public:
	void Initialize();

	list<GameObject*> *_staticObject;
	list<GameObject*> *_dynamicObject;

	QGameObject(void);
	~QGameObject(void);

	QGameObject(string);
	void Draw(CCamera *camera);
	void Update(int deltaTime);
	void Update(int deltaTime, D3DXVECTOR2* ryuPos);
	void Collision(int dt);
	void RemoveAllObject();
};