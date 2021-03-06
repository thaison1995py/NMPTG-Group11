﻿#include "QGameObject.h"


QGameObject::QGameObject(void)
{
}

QGameObject::QGameObject(string fileName, string _fileName)
{
	ifstream map(fileName);

	_listObjectGame = new std::map<int, GameObject*>();
	_listObjectInVP = new list<GameObject*>();
	_listDragonSkullCannon = new list<DragonSkullCannon*>();

	if (map.is_open())
	{
		float posX, posY; int width, height, value;
		int count;
		map >> count;
		int id;
		for (int i = 0; i < count; i++)
		{
			//so thu tu dong - idObj -...
			map >> id >> value >> posX >> posY >> width >> height;

			switch (value)
			{				
			case 0:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Brick(posX, posY, width, height)));
				break;
			case 100:
				_listObjectGame->insert(pair<int, GameObject*>(id, new BrokenBrick(posX, posY)));
				break;
			case 106:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Crown(posX, posY)));
				break;
			case 104:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Food(posX, posY)));
				break;
			case 102:
				_listObjectGame->insert(pair<int, GameObject*>(id, new DoubleShot(posX, posY)));
				break;
			case 107:
				_listObjectGame->insert(pair<int, GameObject*>(id, new GoldChest(posX, posY)));
				break;
			case 1:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Stair(posX, posY, width + 32, height, EnumID::StairUpLeft_ID)));
				break;
			case 2:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Stair(posX, posY, width + 32, height, EnumID::StairUpRight_ID)));
				break;
			case 3:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Stair(posX, posY, width + 32, height, EnumID::StairDownRight_ID)));
				break;
			case 4:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Stair(posX, posY, width + 32, height, EnumID::StairDownLeft_ID)));
				break;
			case 10:
				_listObjectGame->insert(pair<int, GameObject*>(id, new VampireBat(posX, posY)));
				break;
			case 12:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Medusa(posX, posY)));
				break;
			case 11:
				_listObjectGame->insert(pair<int, GameObject*>(id, new BlackKnight(posX, posY)));
				break;
			case 13:				
				_dragonCannon = new DragonSkullCannon(posX, posY);
				_listDragonSkullCannon->push_back(_dragonCannon);
				_listObjectGame->insert(pair<int, GameObject*>(id, _dragonCannon)); //new DragonSkullCannon(posX, posY)));
				break;
			case 14:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Flyingblock(posX, posY)));
				break;
			case 15:
				_queenMedusa = new QueenMedusa(posX, posY, EnumID::QueenMedusa_ID);
				_listObjectGame->insert(pair<int, GameObject*>(id, _queenMedusa));
				break;
				break;
			case 18:
				srand(time(0));									                            //ymax ymin  vUp  vDown 
				_listObjectGame->insert(pair<int, GameObject*>(id, new StupidDoor(posX, posY, 1040, 910, 0.09, 0.1)));
				break;
			case 20:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Door(posX, posY, width, height, EnumID::DoorLeft_ID)));
			
				break;
			case 21:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Door(posX, posY, width, height, EnumID::DoorRight_ID)));
				
				break;
			case 23:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Door(posX, posY, width, height, EnumID::DoorUp_ID)));
				break;
			case 22:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Door(posX, posY, width, height, EnumID::DoorDown_ID)));
				break;
			case 17:
				_listObjectGame->insert(pair<int, GameObject*>(id, new Candle(posX, posY)));
				break;
			case 19:
				_listObjectGame->insert(pair<int, GameObject*>(id, new MovingPlatform(posX, posY)));
				break;
			case 101:
				_listObjectGame->insert(pair<int, GameObject*>(id, new FireDie(posX, posY)));
				break;
			case 105:
				_magicalCrystal = new MagicalCrystal(posX, posY);
				_listObjectGame->insert(pair<int, GameObject*>(id, _magicalCrystal));
				break;
				
			default:
				break;
			}
		}
		map.close();
	}
	ifstream _map(_fileName);
	myObject = new list<int>();

	if (_map.is_open())
	{
		//Doc quadtree
		int posX, posY;
		int id;
		int width, height;
		string strobjID;
		int value;
		nodeOfTree = new std::map<int, QNode*>();
		while (!_map.eof())
		{
			// Đọc thông tin của Node
			_map >> id >> posX >> posY >> width >> height;
			posY = G_MapWidth - posY;

			//Doc id Object trong node
			getline(_map, strobjID);
			istringstream listObj(strobjID);
			list<int> *_objOfNode = new list<int>();
			while (listObj >> value)
			{
				_objOfNode->push_back(value);
			}

			QNode* _nodeTree = new QNode(posX, posY, width, height, *_objOfNode);

			//Dua node vao _myMap
			nodeOfTree->insert(pair<int, QNode*>(id, _nodeTree));
		}
	}
	Initialize();
}

void QGameObject::GetTreeObject(int viewportX, int viewportY)
{
	_listObjectInVP->clear();
	myObject->clear();
	GetNodeObject(viewportX, viewportY, tree);
}

void QGameObject::GetNodeObject(int viewportX, int viewportY, QNode* _node)
{
	if (_node->leftTop != NULL)
	{
		if (viewportX < _node->rightTop->posX && viewportY > _node->leftBottom->posY)
			GetNodeObject(viewportX, viewportY, _node->leftTop);
		if (viewportX + G_ScreenWidth > _node->rightTop->posX && viewportY > _node->rightBottom->posY)
			GetNodeObject(viewportX, viewportY, _node->rightTop);
		if (viewportX < _node->rightBottom->posX && viewportY - G_ScreenHeight < _node->leftBottom->posY)
			GetNodeObject(viewportX, viewportY, _node->leftBottom);
		if (viewportX + G_ScreenWidth > _node->rightBottom->posX && viewportY - G_ScreenHeight < _node->rightBottom->posY)
			GetNodeObject(viewportX, viewportY, _node->rightBottom);
	}
	else
	{
		for (list<int>::iterator _itBegin = _node->listObject.begin(); _itBegin != _node->listObject.end(); _itBegin++)
		{
			myObject->push_back(*_itBegin);
		}
	}
}

void QGameObject::LoadTree()
{
	Load(0, tree);
}

void QGameObject::Load(int id, QNode *& _nodeTree)
{
	map<int, QNode*>::iterator _node = nodeOfTree->find(id);
	if (_node != nodeOfTree->end())
	{
		_nodeTree = new QNode(_node->second->posX, _node->second->posY, _node->second->width, _node->second->height, _node->second->listObject);
		Load(_node->first * 10 + 1, _nodeTree->leftTop);
		Load(_node->first * 10 + 2, _nodeTree->rightTop);
		Load(_node->first * 10 + 3, _nodeTree->leftBottom);
		Load(_node->first * 10 + 4, _nodeTree->rightBottom);
	}
}

void QGameObject::GetObjecttInVP()
{
	for (list<int>::iterator i = myObject->begin(); i != myObject->end(); i++)
	{
			
		auto obj = _listObjectGame->find(*i);
		if (obj != _listObjectGame->end())
		{
			auto obj1 = std::find(_listObjectInVP->begin(), _listObjectInVP->end(), obj->second);
			if (obj1 == _listObjectInVP->end())
			{
				_listObjectInVP->push_back(obj->second);
			
			}
		}
	}
}

void QGameObject::SetObjectActiveInVP(float x, float y)
{
	for (list<GameObject*>::iterator i = _listObjectInVP->begin(); i != _listObjectInVP->end(); i++)
	{
		
		if ((*i)->type != Item_Type)
			(*i)->SetActive(x, y);
		else if ((*i)->type == Item_Type)
		{
			if ((*i)->id == Crown_ID || (*i)->id == GoldChest_ID)
			{
				(*i)->SetActive(x, y);
			}
		}
		
			
	}
}

int QGameObject::RemoveAllObjectInCamera(D3DXVECTOR2 viewport)
{
	int score = 0;
	list<GameObject*>::iterator it = _listObjectInVP->begin();
	while (it != _listObjectInVP->end())
	{
		GameObject* other = (*it);
		if (other->type == ObjectType::Enemy_Type)
		{
			
				score += other->point;
				(*it)->Remove();
				_listObjectInVP->erase(it++);						
		}
		else ++it;
	}
	return score;
}



void QGameObject::Draw(CCamera *camera)
{
	for (list<GameObject*>::iterator i = _listObjectInVP->begin(); i != _listObjectInVP->end(); i++)
	{
		GameObject* obj = (*i);
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}
}
void QGameObject::Update(int deltaTime)
{
	list<GameObject*>::iterator it = _listObjectInVP->begin();
	while (it != _listObjectInVP->end())
	{
		if ((*it)->death)
		{

			_listObjectInVP->erase(it++);
		}
		else
		{
			if ((*it)->active)
			{
				(*it)->Update(deltaTime);
			}
			++it;
		}
	}

	
}

void QGameObject::Collision(int dt)
{
	

	for (list<GameObject*>::iterator i = _listObjectInVP->begin(); i != _listObjectInVP->end(); i++)
	{
		if ((*i)->active && (*i)->id != EnumID::QueenMedusa_ID)
		{
			if (!IsHurt() || (IsHurt() && (*i)->type != ObjectType::Enemy_Type))
				(*i)->Collision((*_listObjectInVP), dt);
		}
	}

	for (list<GameObject*>::iterator i = _listObjectInVP->begin(); i != _listObjectInVP->end(); i++)
	{
		if ((*i)->active)
		{
			(*i)->Collision((*_listObjectInVP), dt);
		}
	}
}

QueenMedusa* QGameObject::getQueenMedusa()
{
	return _queenMedusa;
}

DragonSkullCannon* QGameObject::getDragonSkullCannon()
{
	return _dragonCannon;
}

MagicalCrystal* QGameObject::getMagicalCrystal()
{
	return _magicalCrystal;
}



void QGameObject::Initialize()
{
	bActiveHurt = false;
	_localHurtTime = 0;
}

bool QGameObject::IsHurt()
{
	if (!bActiveHurt)
		return false;
	DWORD now = GetTickCount();
	DWORD deltaTime = now - _localHurtTime;
	if (deltaTime >= 600)
	{
		bActiveHurt = false;
		return false;
	}
	return true;
}

void QGameObject::PauseUpdate()
{
	bActiveHurt = true;
	_localHurtTime = GetTickCount();
}


QGameObject::~QGameObject(void)
{
}
