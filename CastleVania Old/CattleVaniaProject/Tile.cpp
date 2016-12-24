#include "Tile.h"


Tile::Tile()
{
	ID = -1;
}

Tile::Tile(int id, int posX, int posY)
{
	ID = id;
	this->posX = posX;
	this->posY = posY;
}

void Tile::setID(int id)
{
	ID = id * 10 + 1;
}

Tile::~Tile()
{

}
