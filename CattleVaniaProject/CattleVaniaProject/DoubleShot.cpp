#include "DoubleShot.h"


DoubleShot::DoubleShot(void) : DynamicObject()
{
}

DoubleShot::DoubleShot(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::DoubleShot_ID)
{
	type = ObjectType::Item_Type;
	active = false;
}
DoubleShot::~DoubleShot(void)
{
}
