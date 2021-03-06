
#include "DragonSkullCannon.h"


DragonSkullCannon::DragonSkullCannon(void) : DynamicObject()
{
}

DragonSkullCannon::DragonSkullCannon(float x, float y) : DynamicObject(x, y, 0, 0, EnumID::DragonSkullCannon_ID)
{
	fireBall = new list<FireBall*>();
	type = ObjectType::Enemy_Type;
	point = 400;
	hp = 4;
}
void DragonSkullCannon::Update(int dt)
{
	list<FireBall*>::iterator i = fireBall->begin();
	while (i != fireBall->end())
	{ 
		if (!(*i)->active)
		{
				fireBall->erase(i++);
		}
		else
		{
			(*i)->Update(dt);
			++i;
		}	
	}
}

void DragonSkullCannon::SetActive(float x, float y)
{
	if ((abs(posX - x) <= 190))
	{
		if (posX < x)
		{
			_huong = 1;
		}
		else
		{
			_huong = -1;
		}
		if (fireBall->size() < 1)
		{
			fireBall->push_back(new FireBall(posX, posY + 16, _huong, EnumID::FireBall_ID));
		}
		active = true;
	}
}

void DragonSkullCannon::Draw(CCamera* camera)
{
	for (list<FireBall*>::iterator i = fireBall->begin(); i != fireBall->end(); i++)
	{
		if ((*i)->active)
			(*i)->Draw(camera);
	}
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (_huong == 1)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}



DragonSkullCannon::~DragonSkullCannon(void)
{
}
