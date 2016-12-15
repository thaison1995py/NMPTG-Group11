#include "Skeletal.h"

#define SPEED_X 0.2f

Skeletal::Skeletal(void) : DynamicObject()
{
	_alpha = 0;
	_posX0 = posX;
	_posY0 = posY;
}

Skeletal::Skeletal(float x, float y, float _huong, EnumID id) : DynamicObject(x, y, 0, 0, id)
{
	if (_huong > 0)
		vX = SPEED_X;
	else
	{
		vX = -SPEED_X;
	}
	active = true;
	_timeSpawn = 0;
}

void Skeletal::Update(int dt)
{
	_timeSpawn += dt;
	vX = cos(_alpha);
	vY = sin(_alpha) - G*dt;

	posX += vX*dt;

	float deltaPosX = posX - _posX0;

	posY = _posY0 + vY*deltaPosX / vX - 0.5*G*pow((deltaPosX / vX), 2);
	if (_timeSpawn >= 3000)
		active = false;
}

Skeletal::~Skeletal(void)
{
}
