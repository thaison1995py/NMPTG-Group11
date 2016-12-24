#ifndef _QBACKGROUND_H_
#define _QBACKGROUND_H_

#include <list>
#include <map>
#include "Singleton.h"
#include "CCamera.h"
#include <fstream>
#include <iostream>
#include <conio.h>
#include <string>
#include <sstream>
#include "QNode.h"
#include "Tile.h"

using namespace std;

class QBackground
{
public:
	CSprite* bgSprite;
	map<int, Tile*> *listTile;

	QBackground(void);
	QBackground(int);	
	void Draw(CCamera *camera);
	~QBackground(void);
};

#endif

