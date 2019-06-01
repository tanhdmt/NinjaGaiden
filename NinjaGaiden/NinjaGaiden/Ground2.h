
#include "GameObject.h"
#include "CEnum.h"

class Ground2 : public GameObject
{
public:
	Ground2(void);
	Ground2(float _posX, float _posY, int _width, int _height, EnumID _id);
	~Ground2(void);
};
