#pragma once
#include "DynamicObject.h"
#include "CEnum.h"

class GoldChest : public DynamicObject
{
public:
	GoldChest(void);
	GoldChest(float x, float y);
	void SetActive(float x, float y);
	~GoldChest(void);
};

