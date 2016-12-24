#include "SpikeTrap.h"


SpikeTrap::SpikeTrap(void) : DynamicObject()
{
}

SpikeTrap::SpikeTrap(float x, float y) : DynamicObject(x, y, 0.08f, 0, EnumID::SpikeTrap_ID)
{
	type = ObjectType::Enemy_Type;
	damage = 2;
}

SpikeTrap::~SpikeTrap(void)
{
}
