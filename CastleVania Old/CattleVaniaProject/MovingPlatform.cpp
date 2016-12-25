
#include "MovingPlatform.h"


MovingPlatform::MovingPlatform(void) : DynamicObject()
{
}

MovingPlatform::MovingPlatform(float x, float y) : DynamicObject(x, y, 0.1f, 0, EnumID::MovingPlatform_ID)
{
	active = true;
}

void MovingPlatform::Draw(CCamera* camera)
{
	if (sprite != NULL)
	{
		D3DXVECTOR2 center = camera->Transform(posX, posY);
		sprite->Draw(center.x, center.y);
	}
}

MovingPlatform::~MovingPlatform(void)
{
}
void MovingPlatform::Update(int deltaTime)
{

	if (sprite == NULL || !active)
		return;
	posX += vX*deltaTime;
	if (posY == 630)
	{
		if ((posX<3166) || (posX>3232))
			vX = -vX;
		
	}
	if ((posX >= 2047) && (posX <= 2240) && (posY == 1016))
	{
		if ((posX<2080) || (posX>2208))
			vX = -vX;
		
	}
	if ((posX >= 2272) && (posX <= 2496) && (posY == 1016))
	{
		if ((posX<2334) || (posX>2464))
			vX = -vX;
		
	}
	//posY += vY*deltaTime;
	sprite->Update(deltaTime);
}
