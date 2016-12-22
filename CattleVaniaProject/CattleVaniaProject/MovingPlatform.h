#ifndef _MOVINGPLATFORM_H_
#define _MOVINGPLATFORM_H_

#include "DynamicObject.h"

class MovingPlatform : public DynamicObject
{
public:
	void Update(int deltaTime);
	MovingPlatform(void);
	MovingPlatform(float x, float y);
	void Draw(CCamera* camera);
	~MovingPlatform(void);
};

#endif