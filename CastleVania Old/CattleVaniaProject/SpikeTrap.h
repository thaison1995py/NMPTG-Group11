#ifndef _SPIKE_TRAP
#define _SPIKE_TRAP
#include "DynamicObject.h"

class SpikeTrap :public DynamicObject
{
public:
	SpikeTrap(void);
	SpikeTrap(float x, float y);
	~SpikeTrap(void);
};

#endif // !_SPIKE_TRAP
