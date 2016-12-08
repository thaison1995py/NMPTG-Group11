#include "QBackground.h"

QBackground::QBackground(void)
{
	tree = NULL;
	myObject = NULL;
	nodeOfTree = NULL;
	listTile = NULL;
}

QBackground::QBackground(int level)
{
	string fileName;
	string _fileName;
	/*switch (level)
	{
	case 1:
	fileName = "Resources\\Maps\\Level1.txt";
	break;
	case 2:
	fileName = "Resources\\Maps\\Level2.txt";
	break;
	case 3:
	fileName = "Resources\\Maps\\Level3.txt";
	break;
	}*/
	if (level == 1)
	{
		fileName = "Resources\\Maps\\MatrixTile.txt";
		_fileName = "Resources\\Maps\\QuadTree.txt";
	}


	ifstream map(fileName);

	myObject = new list<int>();

	// ma trận tile
	if (map.is_open())
	{
		int posX, posY;
		int value;
		int count;
		int countWidth, countHeight;
		map >> count;
		if (level == 1)
		{
			bgSprite = new CSprite(new CTexture("Resources\\Maps\\TileInMap.png", count, 1, count), 1000);
		}

		/*switch (level)
		{
		case 1:
		bgSprite = new CSprite(new CTexture("Resources\\Maps\\Level1.png", count, 1, count), 1000);
		break;
		case 2:
		bgSprite = new CSprite(new CTexture("Resources\\Maps\\Level2.png", count, 1, count), 1000);
		break;
		case 3:
		bgSprite = new CSprite(new CTexture("Resources\\Maps\\Level3.png", count, 1, count), 1000);
		break;
		}*/
		map >> countHeight >> countWidth;
		int id = 0;
		listTile = new std::map<int, Tile*>();

		Tile* _obj;
		for (int i = countHeight; i > 0; i--)
		{
			for (int j = 0; j < countWidth; j++)
			{
				map >> value;
				posX = j * 16;
				posY = i * 16;
				id = i*count + j;
				listTile->insert(pair<int, Tile*>(id, new Tile(value, posX, posY)));
			}
		}

		map.close();
	}

	ifstream _map(_fileName);

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

}

void QBackground::GetTreeObject(int viewportX, int viewportY)
{
	myObject->clear();

	GetNodeObject(viewportX, viewportY, tree);
}

void QBackground::GetNodeObject(int viewportX, int viewportY, QNode* _node)
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

void QBackground::LoadTree()
{
	Load(0, tree);
}

void QBackground::Load(int id, QNode *& _nodeTree)
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

void QBackground::Draw(CCamera *camera)
{
	//for (list<int>::iterator _itBegin = _listTile->begin(); _itBegin != _listTile->end(); _itBegin++)
	map<int, Tile*>::iterator _itBegin;
	for (_itBegin = listTile->begin(); _itBegin != listTile->end(); _itBegin++)

		//list<Tile*>::iterator _itBegin;
		//for (_itBegin = _listMatrix->begin(); _itBegin != _listMatrix->end(); _itBegin++)
	{
		//Tile* obj = _myObject->find(*_itBegin)->second;	
		Tile* obj = _itBegin->second;
		D3DXVECTOR2 t = camera->Transform(obj->posX, obj->posY);
		bgSprite->DrawIndex(obj->ID, t.x, t.y);
		//bgSprite->DrawIndex(obj->ID, obj->posX, obj->posY);
	}
}

QBackground::~QBackground(void)
{
}