#ifndef _BROKENBRICK_H_
#define _BROKENBRICK_H_

#include "GameObject.h"
#include "CEnum.h"

class BrokenBrick : public GameObject
{
public:
	BrokenBrick(void);
	BrokenBrick(float x, float y);
	void SetActive(float x, float y);
	void Update(int del);
	~BrokenBrick(void);
};

#endif 