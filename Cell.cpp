#include "Cell.h"

Cell::Cell() {

}

Cell::Cell(uint8_t x, uint8_t y, uint8_t z) {
	_coordinate = Coordinate(x, y, z);
	_owner = 0;
}

bool Cell::setOwner(Player* player) {
	if (_owner)
		return false;
	else
		_owner = player;
	return true;
}

void Cell::removeOwner() {
	_owner = NULL;
}

Player* Cell::getOwner() const {
	return _owner;
}