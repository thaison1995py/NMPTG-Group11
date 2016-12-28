#include "Crown.h"

Crown::Crown(void) : DynamicObject()
{
}

Crown::Crown(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::Crown_ID)
{
	type = ObjectType::Item_Type;
	hp = 1;
	damage = 0;
}
Crown::~Crown(void)
{
}
int Crown::wait()
{
	clock_t endwait;
	endwait = clock() + 2 * CLOCKS_PER_SEC;
	while (clock() < endwait) {}

	return 2;
}
void Crown::Update(int deltaTime)
{
	if (posY<80)
	{
		vY = 0.5;
	}
	else vY = 0;
	posY += vY*10;
	sprite->Update(deltaTime);
}
void Crown::SetActive(float x, float y)
{
	if (x > 4040)
	{
			active = true;
	}
}
