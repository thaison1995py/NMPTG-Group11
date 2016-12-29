#pragma once
#include "dynamicobject.h"
class LittleSnake :
	public DynamicObject
{
public:
	LittleSnake(void);
	LittleSnake(float posX, float posY, float vX, float vY, EnumID id);
	void Collision(list<GameObject*>, int);
	void Update(int deltatime);
	~LittleSnake(void);
};

