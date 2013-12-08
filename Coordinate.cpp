#include "Coordinate.h"

Coordinate::Coordinate()  {
	_X = 0;
	_Y = 0;
	_Z = 0;
}

Coordinate::Coordinate(uint8_t X, uint8_t Y, uint8_t Z) {
	_X = X;
	_Y = Y;
	_Z = Z;
}

uint8_t Coordinate::getX() {
	return this->_X;
}

uint8_t Coordinate::getY() {
	return this->_Y;
}

uint8_t Coordinate::getZ() {
	return this->_Z;
}
