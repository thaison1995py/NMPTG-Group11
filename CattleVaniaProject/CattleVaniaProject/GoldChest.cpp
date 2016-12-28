#include "GoldChest.h"


GoldChest::GoldChest(void) : DynamicObject()
{
}

GoldChest::GoldChest(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::GoldChest_ID)
{
	type = ObjectType::Item_Type;
	hp = 1;
	damage = 0;
	start = 0;
	now = 0;
	active = false;
}
GoldChest::~GoldChest(void)
{
}
void GoldChest::SetActive(float x, float y)
{
	if (!active)
	{

		if ((x > 2120) && (x<2136)&&(y>702)&&(y<752))
		{
			if (start == 0)
				start = GetTickCount();
			else
				now = GetTickCount();
			int temp = now - start;
			if (temp>2500)
				active = true;
		}
	}
}
void GoldChest::Update(int deltaTime)
{
	dtt = deltaTime;
	if (posY<656)
	{
		vY = 0.5;
	}
	else vY = 0;
	posY += vY * 10;
	sprite->Update(deltaTime);
}
