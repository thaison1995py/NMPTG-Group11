#ifndef _BLACKNIGHT_H_
#define _BLACKNIGHT_H_

#include "DynamicObject.h"
#include "QGameObject.h"

class BlackKnight : public DynamicObject
{
public:
	BlackKnight(void);
	BlackKnight(float x, float y);
	void Update(int deltaTime);
	~BlackKnight(void);
};

#endif