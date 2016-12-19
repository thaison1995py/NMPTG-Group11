#ifndef _QGAMEOBJECT_H_
#define _QGAMEOBJECT_H_

#include <list>
#include <map>
#include "HeaderObj.h"
#include "Singleton.h"
#include "CCamera.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include <time.h>
#include <random>
#include "QueenMedusa.h"
#include "GameObject.h"
#include "QNode.h"
#include <string>
#include <sstream>

//using namespace std;

class QGameObject
{
protected:
	/*PhantomBat* _phantomBat;*/
	QueenMedusa* _queenMedusa;
	QNode *tree;
	map<int, QNode*> *nodeOfTree;
	list<int> *myObject;
	void Load(int, QNode*&);
	void GetNodeObject(int, int, QNode*);

	D3DXVECTOR2 posDoor;
public:
	DWORD _localHurtTime;
	DWORD _deltaHurtTime;
	bool bActiveHurt;
	bool IsHurt();
	void Initialize();

	list<GameObject*> *_staticObject;
	list<GameObject*> *_dynamicObject;

	QGameObject(void);
	~QGameObject(void);

	QGameObject(string, string);
	D3DXVECTOR2 GetPosDoor();	//Lay vi tri de ve canh cua qua stage
	void LoadTree();
	void GetTreeObject(int, int);
	void Draw(CCamera *camera);
	void Update(int deltaTime);
	void Collision(int dt);
	int RemoveAllObjectInCamera(D3DXVECTOR2);
	void RemoveAllObject();
	QueenMedusa* getQueenMedusa();
	//PhantomBat* getPhantomBat();
	void PauseUpdate();
};

#endif#ifndef _QGAMEOBJECT_H_
