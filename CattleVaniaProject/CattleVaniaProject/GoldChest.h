#pragma once
#include "DynamicObject.h"
#include "CEnum.h"
#include <ctime>

class GoldChest : public DynamicObject
{
public:
	int dtt;
	GoldChest(void);
	int start, now;
	GoldChest(float x, float y);
	void Update(int deltaTime);
	void SetActive(float x, float y);
	~GoldChest(void);
};

