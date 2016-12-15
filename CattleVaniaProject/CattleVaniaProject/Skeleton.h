#ifndef _SKELETON_H_
#define _SKELETON_H_

#include "DynamicObject.h"
#include "Skeletal.h"

class Skeleton : public DynamicObject
{
	list<Skeletal*> *Skeletal;
public:
	Skeleton(void);
	Skeleton(float x, float y);
	void Update(int dt);
	void Draw(CCamera* camera);
	void SetActive(float x, float y);
	~Skeleton(void);
};
#endif