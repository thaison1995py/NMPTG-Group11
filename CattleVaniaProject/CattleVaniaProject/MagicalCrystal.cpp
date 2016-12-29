
#include "MagicalCrystal.h"


MagicalCrystal::MagicalCrystal(void) : DynamicObject()
{
}

MagicalCrystal::MagicalCrystal(float x, float y) : DynamicObject(x, y, 0, -0.3f, EnumID::MagicalCrystal_ID)
{
	active = false;
	type = ObjectType::Item_Type;
	damage = 0;

}

void MagicalCrystal::Collision(list<GameObject*> obj, int dt)
{
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		GameObject* other = (*_itBegin);

		if (other->id == EnumID::Brick_ID)
		{
			float moveX;
			float moveY;
			float normalx;
			float normaly;
			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				posY += moveY;
				vY = 0;
				return;
			}
		}
	}
}

MagicalCrystal::~MagicalCrystal(void)
{
}
