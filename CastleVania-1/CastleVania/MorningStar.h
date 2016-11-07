#ifndef _MORNINGSTAR_H_
#define _MORNINGSTAR_H_

#include "GameObject.h"
#include "MorningStarSprite.h"
#include "FireDie.h"
#include "QueenMedusa.h"
#include <vector>
using namespace std;

class MorningStar :
	public GameObject
{
protected:
	MorningStarSprite* _morningStarSprite;

public:
	MorningStar(void);
	MorningStar(int posX_, int posY_, float vx_, float vy_, EnumID id_, int MorningStarRate_);
	void reset();
	virtual void Update(int deltaTime_);
	virtual void Draw(CCamera*);
	virtual Box GetBox();

	void updateXY(int posX_, int posY_);
	void updateVx(float vx_);
	void updateLevel();
	
	void Collision(list<GameObject*> &obj, int dt);
	~MorningStar(void);

	//for testing
	MorningStarSprite* getSprite();
};

#endif