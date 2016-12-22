#include "BlackKnight.h"


BlackKnight::BlackKnight(void) : DynamicObject()
{
}

BlackKnight::BlackKnight(float x, float y) : DynamicObject(x, y, 0.3f, 0, EnumID::BlackKnight_ID)
{
	type = ObjectType::Enemy_Type;
	point = 400;
	hp = 2;
	damage = 2;
}
void BlackKnight::Update(int deltaTime)
{
	
	if (sprite == NULL || !active)
		return;
	posX += vX*deltaTime;
	if (posY==289)
	{
		if ((posX<3670) || (posX>3880))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
	if (posY == 544)
	{
		if ((posX<3727) || (posX>3757))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
	if ((posX>=3222)&&(posX<=3466)&&(posY == 671))
	{
		if ((posX<3278) || (posX>3376))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
	if ((posX >= 1645) && (posX <= 2129) && (posY == 671))
	{
		if ((posX<1680) || (posX>2093))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
	if ((posY == 927))
	{
		if ((posX<2386) || (posX>2672))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
	if ((posY == 1056))
	{
		if ((posX<2834) || (posX>2990))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
	if ((posY == 1057))
	{
		if ((posX<2512) || (posX>2672))
			vX = -vX;
		posY += vY*deltaTime;
		sprite->Update(deltaTime);
	}
}

BlackKnight::~BlackKnight(void)
{
}
