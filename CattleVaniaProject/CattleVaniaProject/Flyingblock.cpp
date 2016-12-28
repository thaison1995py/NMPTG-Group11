#include "Flyingblock.h"


Flyingblock::Flyingblock(void) : DynamicObject()
{
}

Flyingblock::Flyingblock(float x, float y) : DynamicObject(x, y, 0.2f, 0, EnumID::Flyingblock_ID)
{
	type = ObjectType::Enemy_Type;
	point = 300;
	hp = 2;
	damage = 2;
}
void Flyingblock::Update(int deltaTime)
{
	if (sprite == NULL || !active)
		return;
	if (posY < (smy - 16)) vY = 0.3;

	if ((posY>(smy - 16)) && (posY < smy)) vY = 0;
	
	if (posY > (smy-16)) vY = -0.3;
	if (posX>smx)
	{
		vX = -0.3;
	}
	else
	{
		vX = 0.3;
	}
	posX += vX*deltaTime;
	posY += vY*deltaTime;
	sprite->Update(deltaTime);
}
Flyingblock::~Flyingblock(void)
{
}
void Flyingblock::SetActive(float x, float y)
{
	smx = x;
	smy = y;
	if (active) return;
	if (abs(posX - x) <= 150 && abs(posY - y) <= 50)
	{
		if (posX - x > 0)
		{
			vX = -vX;
		}
		active = true;
	}
}
