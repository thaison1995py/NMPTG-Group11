#include "QNode.h"


QNode::QNode(void)
{
	posX = 0;
	posY = 0;
	width = 0;
	height = 0;
	leftTop = NULL;
	rightBottom = NULL;
	leftBottom = NULL;
	rightTop = NULL;
}

QNode::QNode(int _left, int _top, int _width, int _height, list<int> _list)
{
	posX = _left;
	posY = _top;
	width = _width;
	height = _height;
	leftTop = NULL;
	rightBottom = NULL;
	leftBottom = NULL;
	rightTop = NULL;
	listObject = _list;
}

void QNode::Insert(int key)
{
	listObject.push_back(key);
}

QNode::QNode(const QNode& _node)
{
	posX = _node.posX;
	posY = _node.posY;
	width = _node.width;
	height = _node.height;
	leftTop = _node.leftTop;
	leftBottom = _node.leftBottom;
	rightTop = _node.rightTop;
	rightBottom = _node.rightBottom;
	listObject = _node.listObject;
}

QNode::~QNode(void)
{
}
