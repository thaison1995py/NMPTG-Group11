#ifndef _BROKENBRICK_H_
#define _BROKENBRICK_H_

#include "DynamicObject.h"
#include "CEnum.h"

class BrokenBrick : public DynamicObject
{
public:
	BrokenBrick(void);
	BrokenBrick(float x, float y);
	void SetActive(float x, float y);
	~BrokenBrick(void);
};

#endif 