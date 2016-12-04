#ifndef _ZOMBIE_H_
#define _ZOMBIE_H_

#include "DynamicObject.h"
#include "CEnum.h"

class Zombie :public DynamicObject
{
public:
	Zombie(void);
	Zombie(float x, float y);
	~Zombie(void);
};

#endif