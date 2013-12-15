#include "Straight.h"

Straight::Straight() {
	
}

Straight::Straight(uint8_t cubeTripStart, uint8_t straightStep, uint8_t straightLength, Color color) {
	_cubeTripStart = cubeTripStart;
	_straightStep = straightStep;
	_straightLength = straightLength;
	_color = color;
}

uint8_t Straight::getCubeTripStart() {
	return _cubeTripStart;
}

uint8_t Straight::getStraightLength() {
	return _straightLength;
}

uint8_t Straight::getStraightStep() {
	return _straightStep;
}

Color Straight::getColor() {
	return _color;
}