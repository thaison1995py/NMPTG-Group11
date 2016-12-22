#include "FireBall.h"

#define SPEED_X 0.3f

FireBall::FireBall(void) : DynamicObject()
{
}

FireBall::FireBall(float x, float y, float _huong, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	if (_huong > 0)
		vX = SPEED_X;
	else
	{
		vX = -SPEED_X;
	}
	active = true;
	_timeSpawn = 10;
}

void FireBall::Update(int dt)
{
	_timeSpawn += dt;
	posX += vX * dt;
	if (_timeSpawn >= 2000)
		active = false;
}

FireBall::~FireBall(void)
{
}
