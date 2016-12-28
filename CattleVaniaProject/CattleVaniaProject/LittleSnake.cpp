#include "LittleSnake.h"


LittleSnake::LittleSnake(void)
{
}

LittleSnake::LittleSnake(float _posX, float _posY, float _vX, float _vY, EnumID _id)
	: DynamicObject(_posX, _posY, _vX, _vY, _id)
{
	type = ObjectType::Enemy_Type;
	active = true;
	damage = 1;
}

void LittleSnake::Collision(list<GameObject*> obj, int dt)
{
	list<GameObject*>::iterator _itBegin;
	for (_itBegin = obj.begin(); _itBegin != obj.end(); _itBegin++)
	{
		float moveX;
		float moveY;
		GameObject* other = (*_itBegin);
		if (other->id == EnumID::Brick_ID)
		{
			Box box = this->GetBox();
			Box boxOther = other->GetBox();

			if (AABB(box, boxOther, moveX, moveY) == true)
			{
				if (vY < 0)
				{
					posY += moveY;
					vY = 0;
					return;
				}
				//va chạm vào bên phải hoặc bên trái brick thì hủy đối tượng little snake
				if (moveX != 0)
					this->active = false;
			}
		}
	}
}

LittleSnake::~LittleSnake(void)
{
}
