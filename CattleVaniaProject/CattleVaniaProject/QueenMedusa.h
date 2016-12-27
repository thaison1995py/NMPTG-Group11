#ifndef _QUEENMEDUSA_H_
#define _QUEENMEDUSA_H_

#include "DynamicObject.h"
//#include "MagicalCrystal.h"
#include <vector>
#include "LittleSnake.h"
using namespace std;

#define QUEEN_MEDUSA_STATE 20
#define QUEEN_MEDUSA_SLEEP_STATE 10
#define QUEEN_MEDUSA_STOP_STATE 2
#define QUEEN_MEDUSA_SPEED_X 0.3f
#define LITTLE_SNAKE_SPEED_X 0.5f
#define QUEEN_MEDUSA_DIE_RATE 10
#define DEAD_TIME 1500
#define PI 3.14f
#define T 1000
#define A 20
#define QUEEN_MEDUSA_INACTIVE_RATE 1

//
//enum ERouterType
//{
//	Parabol,
//	Line,
//	Horizontal,
//	Vertical
//};

enum EQueenMedusaState
{
	InActive,
	Stop,
	Moving,
	Dead,
	Cancel
};

class QueenMedusa : public DynamicObject
{
protected:
	CSprite* _sleepSprite;
	CSprite* _fightSprite;
	CSprite* _deadSprite;
	D3DXVECTOR2* _routerInfo;
	vector<D3DXVECTOR2*> _vStopPos;
	D3DXVECTOR2* _gold;
	int _previousStopPos;
	int _currentStopPos;
	//ERouterType _eRouterType;
	DWORD _localTime;

	list<GameObject*> *_vLittleSnake;

	EQueenMedusaState _state;
	D3DXVECTOR2* _simonPos;
	float _deltaPhi;
	float _posY0;


	void _initialize();
	void _onStop(int deltaTime_);
	void _onMoving(int deltaTime_);
	void _onDead(int deltaTime_);
	void _onInActive(int deltaTime_);

	bool _isKiss(D3DXVECTOR2 boss_, D3DXVECTOR2 gold_);
	void _drawSnakes(CCamera* camera_);
	void _updateSnakes(int deltaTime_);

public:
	bool _hasGetUp;
	//MagicalCrystal* magicalCrystal;
	QueenMedusa(void);
	QueenMedusa(float posX, float posY, EnumID id);
	virtual void Update(int deltaTime_);
	void Update(int deltaTime_, D3DXVECTOR2* simonPos_);
	virtual void Draw(CCamera* camera_);
	virtual void Collision(list<GameObject*> obj, int dt);
	list<GameObject*> getlistSnake();
	void getUp();
	void setDead();

	void ReceiveDamage(int damagePoint);
	bool GetState();
	~QueenMedusa(void);
public:

};

#endif

