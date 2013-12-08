#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include <inttypes.h>

class Coordinate {
public:
	Coordinate();
	Coordinate(uint8_t X, uint8_t Y, uint8_t Z);

	uint8_t getX();
	uint8_t getY();
	uint8_t getZ();

protected:
	uint8_t _X;
	uint8_t _Y;
	uint8_t _Z;
};

#endif