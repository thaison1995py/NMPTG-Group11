#ifndef _TILE_H_
#define _TILE_H_

class Tile
{
public:
	int ID;
	int posX, posY;

	Tile(void);
	Tile(int id, int posX, int posY);
	void setID(int id);
	~Tile();
};

#endif