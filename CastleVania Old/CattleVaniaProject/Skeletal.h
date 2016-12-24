#ifndef _SKELETAL_H_
#define _SKELETAL_H_

#include "DynamicObject.h"

#define G 0.01f

class Skeletal : public DynamicObject
{

	float _alpha;
	int _timeSpawn;
	// vitri ban dau cuc xuong
	float _posX0;
	float _posY0;

public:
	Skeletal(void);
	Skeletal(float x, float y, float _huong, EnumID id);
	void Update(int dt);
	~Skeletal(void);
};

#endif