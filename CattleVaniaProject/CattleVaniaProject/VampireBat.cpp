#include "VampireBat.h"


VampireBat::VampireBat(void) : DynamicObject()
{
}

VampireBat::VampireBat(float x, float y) : DynamicObject(x, y, 0.4f, -0.6f, EnumID::VampireBat_ID)
{
	type = ObjectType::Enemy_Type;
	point = 200;
	active = true;
	getUp = false;
}

VampireBat::~VampireBat(void)
{
}

void VampireBat::Move(int deltaTime)
{
	if (posY>smy)
	{
		posX += vX * deltaTime;
		posY += vY*deltaTime;
	}
	else
		posX += vX * deltaTime;

}

void VampireBat::Update(int deltaTime)
{
	if (getUp)
	{
		Move(deltaTime);
		sprite->Update(deltaTime);
	}
}

void VampireBat::Collision(list<GameObject*> obj, int dt) {}

void VampireBat::SetActive(float x, float y)
{
	smx = x;
	smy = y;
	if (abs(posX - x) <= 180 && abs(posY - y) <= 150)
	{
		
		getUp = true;
		sprite->_start = 1;
	}
}