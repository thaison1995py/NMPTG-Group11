#ifndef _FLYINGBLOCK_H_
#define _FLYINGBLOCK_H_

#include "DynamicObject.h"

class Flyingblock : public DynamicObject
{
public:
	int smx, smy;
	Flyingblock(void);
	void Update(int dt);
	void SetActive(float x, float y);
	Flyingblock(float x, float y);
	~Flyingblock(void);
};

#endif