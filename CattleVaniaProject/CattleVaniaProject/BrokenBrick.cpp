#include "BrokenBrick.h"


BrokenBrick::BrokenBrick(void) : GameObject()
{
}

BrokenBrick::BrokenBrick(float x, float y) : GameObject(x, y,EnumID::BrokenBrick_ID)
{
	type = ObjectType::None_Type;
	hp = 1;
	damage = 0;
	active = true;
}
BrokenBrick::~BrokenBrick(void)
{
}
void BrokenBrick::Update(int del)
{
}
void BrokenBrick::SetActive(float x, float y)
{
	active = true;
}
