#pragma once
#include "dynamicobject.h"
class LittleSnake :
	public DynamicObject
{
public:
	LittleSnake(void);
	LittleSnake(float posX, float posY, float vX, float vY, EnumID id);
	void Draw(CCamera* camera);
	void Collision(list<GameObject*>, int);
	~LittleSnake(void);
};

