#include "BrokenBrick.h"


BrokenBrick::BrokenBrick(void) : DynamicObject()
{
}

BrokenBrick::BrokenBrick(float x, float y) : DynamicObject(x, y, 0.09f, 0, EnumID::BrokenBrick_ID)
{
	type = ObjectType::None_Type;
	hp = 1;
	damage = 0;
	active = true;
}
BrokenBrick::~BrokenBrick(void)
{
}
void BrokenBrick::SetActive(float x, float y)
{
	active = true;
}
