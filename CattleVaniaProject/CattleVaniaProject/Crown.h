#pragma once
#include "DynamicObject.h"
#include "CEnum.h"
#include "time.h"
class Crown : public DynamicObject
{
public:
	int wait();
	Crown(void);
	Crown(float x, float y);
	void Update(int deltaTime);
	void SetActive(float x, float y);
	~Crown(void);
};

