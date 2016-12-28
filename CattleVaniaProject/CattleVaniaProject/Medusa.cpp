#include "Medusa.h"
Medusa::Medusa(void) : DynamicObject()
{
}

Medusa::Medusa(float _x, float _y) : DynamicObject(_x, _y, 0.3f, 0, EnumID::Medusa_ID)
{
	type = ObjectType::Enemy_Type;
	point = 300;
}

Medusa::~Medusa(void)
{
}

void Medusa::MoveSinPath(int deltaTime)
{
	float nextX = vX * deltaTime + posX;
	float nextY = 10 * sin(nextX / 20);
	vY = nextY;
	posX += vX * deltaTime;
	posY += vY;
}

void Medusa::Collision(list<GameObject*> obj, int dt) {}

void Medusa::Update(int deltaTime)
{

	MoveSinPath(deltaTime);
	sprite->Update(deltaTime);
}
void Medusa::SetActive(float x, float y)
{
	if (!active)
	{

		if (x < posX)
			vX = -0.3;
		else
			vX = 0.3;
		if (abs(y - posY) < 70)
			active = true;
	}
}