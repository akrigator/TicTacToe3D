#ifndef _CELL_H_
#define _CELL_H_

#include "Coordinate.h"
#include "Player.h"

class Cell {
public:
	Cell();
	Cell(uint8_t x, uint8_t y, uint8_t z);
	bool setOwner(Player* player);
	Player* getOwner() const;

private:
	Coordinate _coordinate;
	Player* _owner;
};

#endif