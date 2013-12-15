#ifndef _STRAIGHT_H_
#define _STRAIGHT_H_

#include <inttypes.h>
#include "Setup.h"

class Straight {
public:
	Straight();
	Straight(uint8_t cubeTripStart, uint8_t straightStep, uint8_t straightLength, Color color);
	uint8_t getCubeTripStart();
	uint8_t getStraightStep();
	uint8_t getStraightLength();
	Color getColor();
private:
	uint8_t _cubeTripStart;
	uint8_t _straightStep;
	uint8_t _straightLength;
	Color _color;
};

#endif