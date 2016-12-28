
#include "MovingPlatform.h"


MovingPlatform::MovingPlatform(void) : DynamicObject()
{
}

MovingPlatform::MovingPlatform(float x, float y) : DynamicObject(x, y, 0.1f, 0, EnumID::MovingPlatform_ID)
{
}

MovingPlatform::~MovingPlatform(void)
{
}
void MovingPlatform::Update(int deltaTime)
{

	if (sprite == NULL || !active)
		return;
	posX += vX*deltaTime;
	
	if (posY == 632)
	{
		if ((posX<3166) || (posX>3232))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
	if ((posY == 1017))
	{
		if ((posX<2080) || (posX>2208))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
	if (posY == 1016)
	{
		if ((posX<2334) || (posX>2464))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
}
