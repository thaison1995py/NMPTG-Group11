#include "GoldChest.h"


GoldChest::GoldChest(void) : DynamicObject()
{
}

GoldChest::GoldChest(float x, float y) : DynamicObject(x, y, 0.09f, 0, EnumID::GoldChest_ID)
{
	type = ObjectType::Item_Type;
	hp = 1;
	damage = 0;
	active = true;
}
GoldChest::~GoldChest(void)
{
}
void GoldChest::SetActive(float x, float y)
{
	active = true;
}
