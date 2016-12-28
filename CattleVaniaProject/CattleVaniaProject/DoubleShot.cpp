#include "DoubleShot.h"


DoubleShot::DoubleShot(void) : DynamicObject()
{
}

DoubleShot::DoubleShot(float x, float y) : DynamicObject(x, y, 0.09f, 0, EnumID::DoubleShot_ID)
{
	type = ObjectType::Item_Type;
	hp = 1;
	damage = 0;
	active = true;
}
DoubleShot::~DoubleShot(void)
{
}
void DoubleShot::SetActive(float x, float y)
{
	active = true;
}
