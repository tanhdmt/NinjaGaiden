#ifndef _CENUM_H_
#define _CENUM_H_

enum Action
{
	Idle,
	Run_Right,
	Run_Left,
	Jump1,
	Jump2,
	Fight,
	Sit,
	Fall,
};

static enum ESceneState
{
	Menu_Scene,
	Game_Scene,
	EndGame_Scene
} EnumSceneState;


enum ObjectType
{
	None_Type,
	Item_Type,
	Enemy_Type,
	Other_Type
};

enum EKindStair
{
	UpRight,
	UpLeft,
	DownRight,
	DownLeft,
	None
};

enum EnumID
{
	//Weapon
	None_ID,
	//Action
	Ryu_ID,
	RyuRun_ID,
	RyuDeath_ID,
	RyuJump1_ID,
	RyuJump2_ID,
	//Ground
	Ground1_ID,
	//Enemy

};


enum EStateCamera
{
	Update_Camera,
	NoUpdate_Camera
};

enum EState
{
	None_State,
	NoUpdate_State
};

enum ECollisionDirect
{
	Colls_None,
	Colls_Left,
	Colls_Right,
	Colls_Bot,
	Colls_Top
};

enum EKind
{
	EDynamic,
	EStatic,
	ESolid,
	EScene
};
#endif