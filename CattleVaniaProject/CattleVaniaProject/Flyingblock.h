#ifndef _FLYINGBLOCK_H_
#define _FLYINGBLOCK_H_

#include "DynamicObject.h"

class Flyingblock : public DynamicObject
{
public:
	Flyingblock(void);
	Flyingblock(float x, float y);
	~Flyingblock(void);
};

#endif