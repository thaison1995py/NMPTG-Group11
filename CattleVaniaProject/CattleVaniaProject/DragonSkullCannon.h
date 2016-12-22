#ifndef _DRAGONSKULLCANNON_H_
#define _DRAGONSKULLCANNON_H_

#include "DynamicObject.h"
#include "FireBall.h"

class DragonSkullCannon : public DynamicObject
{
	list<DynamicObject*> *_vFireBall;
	list<FireBall*> *fireBall;
public:
	int vfb;
	int smx, smy;
	DragonSkullCannon(void);
	DragonSkullCannon(float x, float y);
	void Update(int dt);
	void Draw(CCamera* camera);
	void SetActive(float x, float y);
	~DragonSkullCannon(void);
};

#endif