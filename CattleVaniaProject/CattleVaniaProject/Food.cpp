#include "Food.h"


Food::Food(void) : DynamicObject()
{
}

Food::Food(float x, float y) : DynamicObject(x, y, 0.09f, 0, EnumID::Food_ID)
{
	type = ObjectType::Item_Type;
	hp = 1;
	damage = 0;
	active = true;
}
Food::~Food(void)
{
}
void Food::SetActive(float x, float y)
{
	active = true;
}
