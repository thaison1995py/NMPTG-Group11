#include "QGameObject.h"


QGameObject::QGameObject(void)
{
}

void QGameObject::GetTreeObject(int viewportX, int viewportY)
{
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

int QGameObject::RemoveAllObjectInCamera(D3DXVECTOR2 viewport)
{
	int score = 0;
	list<GameObject*>::iterator it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		GameObject* other = (*it);
		if (other->active && !(other->posX + other->width / 2 <= viewport.x
			|| other->posX - other->width / 2 >= viewport.x + G_ScreenWidth
			|| other->posY + other->height / 2 <= viewport.y - G_ScreenHeight
			|| other->posY - other->height / 2 >= viewport.y))
		{
			if (other->type == ObjectType::Enemy_Type)
			{
				switch (other->id)
				{
				case EnumID::PhantomBat_ID:
				case EnumID::QueenMedusa_ID:
					if (other->sprite->GetIndex() != 0)
						other->point -= 4;
					++it;
					break;
				default:
					score += other->point;
					_dynamicObject->erase(it++);
					break;
				}
			}
			else ++it;
		}
		else ++it;
	}
	return score;
}


QGameObject::QGameObject(string fileName, string _fileName)
{
	ifstream map(fileName);

	_staticObject = new list<GameObject*>();
	_dynamicObject = new list<GameObject*>();

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
				_staticObject->push_back(new Brick(posX, posY, width, height));
				break;
			case 1:
				_staticObject->push_back(new Stair(posX, posY, width, height, EnumID::StairUpLeft_ID));
				break;
			case 2:
				_staticObject->push_back(new Stair(posX, posY, width+32, height, EnumID::StairUpRight_ID));
				break;
			case 3:
				_staticObject->push_back(new Stair(posX, posY, width, height, EnumID::StairDownRight_ID));
				break;
			case 4:
				_staticObject->push_back(new Stair(posX, posY, width+32, height, EnumID::StairDownLeft_ID));
				break;
			case 10:
				_dynamicObject->push_back(new VampireBat(posX, posY));
				break;
			case 12:
				_dynamicObject->push_back(new Medusa(posX, posY));
				break;
			case 11:
				_dynamicObject->push_back(new BlackKnight(posX, posY));
				posBlackKnight.x = posX;
				posBlackKnight.y = posY;
				break;
			case 13:
				_dynamicObject->push_back(new DragonSkullCannon(posX, posY));
				break;
			case 14:
				_dynamicObject->push_back(new Flyingblock(posX, posY));
				break;
			case 15:
				_queenMedusa = new QueenMedusa(posX, posY, EnumID::QueenMedusa_ID);
				_dynamicObject->push_back(_queenMedusa);
				break;
			case 18:
				srand(time(0));									  //ymax ymin   vUp    vDown 
				_staticObject->push_back(new StupidDoor(posX, posY, 1040, 910, 0.09, 0.1));
				break;
			case 20:
				_staticObject->push_back(new Door(posX, posY, width, height, EnumID::DoorLeft_ID));
		
				break;
			case 21:
				_staticObject->push_back(new Door(posX, posY, width, height, EnumID::DoorRight_ID));
				
				break;
			case 23:
				_staticObject->push_back(new Door(posX, posY, width, height, EnumID::DoorUp_ID));
				break;
			case 22:
				_staticObject->push_back(new Door(posX, posY, width, height, EnumID::DoorDown_ID));
				break;
			case 17:
				_staticObject->push_back(new Candle(posX, posY));
				break;
			case 19:
				_dynamicObject->push_back(new MovingPlatform(posX, posY));
				break;
/*
			case 26:
				G_MinSize = posX;
				break;
			case 27:
				G_MaxSize = posX;
				break;
			default:
				break;
			}*/
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

D3DXVECTOR2 QGameObject::GetPosDoor()
{
	return posDoor;
}

void QGameObject::Draw(CCamera *camera)
{
	for (list<GameObject*>::iterator i = _staticObject->begin(); i != _staticObject->end(); i++)
	{
		GameObject* obj = (*i);
		if (obj->active)
		{
			obj->Draw(camera);
		}
	}

	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
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
	list<GameObject*>::iterator it = _staticObject->begin();
	while (it != _staticObject->end())
	{
		if ((*it)->death)
		{
			_staticObject->erase(it++);
		}
		else
		{
			(*it)->Update(deltaTime);
			++it;
		}
	}

	it = _dynamicObject->begin();
	while (it != _dynamicObject->end())
	{
		/*if (!IsHurt() || (IsHurt() && (*it)->type != ObjectType::Enemy_Type))
		{
			if ((*it)->id == EnumID::QueenMedusa_ID)
			{
				if (((QueenMedusa*)*it)->GetState())
				{
					_dynamicObject->push_back(new MagicalCrystal((*it)->posX, (*it)->posY));
					_dynamicObject->erase(it++);
				}
				else ++it;
			}
			else
				if ((*it)->id == EnumID::PhantomBat_ID)
				{
					if (((PhantomBat*)*it)->GetState())
					{
						_dynamicObject->push_back(new MagicalCrystal((*it)->posX, (*it)->posY));
						_dynamicObject->erase(it++);
					}
					else ++it;
				}
				else
				{
					if ((*it)->death)
					{
						_dynamicObject->erase(it++);
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
		else ++it;*/
		if ((*it)->death)
		{
			_dynamicObject->erase(it++);
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
	for (list<GameObject*>::reverse_iterator i = _staticObject->rbegin(); i != _staticObject->rend(); i++)
	{
		if ((*i)->canMove)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}

	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	{
		if((*i)->active && (*i)->id != EnumID::PhantomBat_ID && (*i)->id != EnumID::QueenMedusa_ID)
		{
			if(!IsHurt() || (IsHurt() && (*i)->type != ObjectType::Enemy_Type))
				(*i)->Collision((*_staticObject), dt);
		}
	}

	for (list<GameObject*>::iterator i = _dynamicObject->begin(); i != _dynamicObject->end(); i++)
	{
		if ((*i)->active)
		{
			(*i)->Collision((*_staticObject), dt);
		}
	}
}

QueenMedusa* QGameObject::getQueenMedusa()
{
	return _queenMedusa;
}

//PhantomBat* QGameObject::getPhantomBat()
//{
//	return _phantomBat;
//}

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

void QGameObject::RemoveAllObject()
{
	_dynamicObject->clear();
}
QGameObject::~QGameObject(void)
{
}
