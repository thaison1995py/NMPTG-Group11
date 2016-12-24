#include "VampireBat.h"


VampireBat::VampireBat(void) : DynamicObject()
{
}

VampireBat::VampireBat(float x, float y) : DynamicObject(x, y, 0.4f, -0.6f, EnumID::VampireBat_ID)
{
	type = ObjectType::Enemy_Type;
	point = 200;
	active = true;
	getUp = false;
}

VampireBat::~VampireBat(void)
{
}

void VampireBat::Move(int deltaTime)
{
	if (posY>smy)
	{
		posX += vX * deltaTime;
		posY += vY*deltaTime;
	}
	else
		posX += vX * deltaTime;
	
}

void VampireBat::Draw(CCamera* camera)
{
	if (sprite == NULL || !active)
		return;
	/*if (posX + width / 2 <= camera->viewport.x || posX - width / 2 >= camera->viewport.x + G_ScreenWidth)
	{
		active = false;
		return;
	}*/
	D3DXVECTOR2 center = camera->Transform(posX, posY);
	if (vX > 0)
		sprite->DrawFlipX(center.x, center.y);
	else
		sprite->Draw(center.x, center.y);
}

void VampireBat::Update(int deltaTime)
{
	if (getUp)
	{
		Move(deltaTime);
		sprite->Update(deltaTime);
	}
}

void VampireBat::Collision(list<GameObject*> obj, int dt) {}

void VampireBat::SetActive(float x, float y)
{
	smx = x;
	smy = y;
	if (abs(posX - x) <= 180 && abs(posY - y) <= 150)
	{
		if (posX - x > 0)
		{
			vX = -0.5f;	
		}
		else
		{
			vX = 0.5f;
		}
		getUp = true;
		sprite->_start = 1;
	}
}