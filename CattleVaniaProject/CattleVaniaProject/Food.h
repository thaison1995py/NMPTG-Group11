#pragma once
#include "DynamicObject.h"
#include "CEnum.h"

class Food : public DynamicObject
{
public:
	Food(void);
	Food(float x, float y);
	void SetActive(float x, float y);
	~Food(void);
};

