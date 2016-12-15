#include "Flyingblock.h"


Flyingblock::Flyingblock(void) : DynamicObject()
{
}

Flyingblock::Flyingblock(float x, float y) : DynamicObject(x, y, 0.08f, 0, EnumID::Flyingblock_ID)
{
	type = ObjectType::Enemy_Type;
	point = 300;
	hp = 2;
	damage = 2;
}

Flyingblock::~Flyingblock(void)
{
}
