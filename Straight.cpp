#include "Straight.h"

Straight::Straight() {
	
}

Straight::Straight(uint8_t cubeTripStart, uint8_t straightStep, uint8_t straightLength) {
	_cubeTripStart = cubeTripStart;
	_straightStep = straightStep;
	_straightLength = straightLength;
}