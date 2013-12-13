#ifndef _STRAIGHT_H_
#define _STRAIGHT_H_

#include <inttypes.h>

class Straight {
public:
	Straight();
	Straight(uint8_t cubeTripStart, uint8_t straightStep, uint8_t straightLength);
private:
	uint8_t _cubeTripStart;
	uint8_t _straightStep;
	uint8_t _straightLength;	
};

#endif