#ifndef _DRAGONSKULLCANNON_H_
#define _DRAGONSKULLCANNON_H_

#include "DynamicObject.h"
#include "FireBall.h"

class DragonSkullCannon : public DynamicObject
{
	list<GameObject*> *fireBall;
public:
	int _huong;
	int smx, smy;
	DragonSkullCannon(void);
	DragonSkullCannon(float x, float y);
	void Update(int dt);
	list<GameObject*> getFireBall();
	void Draw(CCamera* camera);
	void SetActive(float x, float y);
	~DragonSkullCannon(void);
};

#endif