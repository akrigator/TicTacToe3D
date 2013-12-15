#include "Rules.h"

Rules::Rules(uint8_t x, uint8_t y, uint8_t z, uint8_t l) {
	_straightLength = l;
	_rulesArray = new Rule[_rulesCount];
	//2D
	_rulesArray[0]	= Rule(Coordinate(0,		0,		0), Coordinate(x-l+1,	y,		z),		1);
	_rulesArray[1]	= Rule(Coordinate(0,		0,		0), Coordinate(x,		y-l+1,	z),		x);
	_rulesArray[2]	= Rule(Coordinate(0,		0,		0), Coordinate(x-l+1,	y-l+1,	z),		x+1);
	_rulesArray[3]	= Rule(Coordinate(l-1,		0,		0), Coordinate(x,		y-l+1,	z),		x-1);
	//3D
	_rulesArray[4]	= Rule(Coordinate(0,		0,		0),	Coordinate(x,		y,		z-l+1),	x*y);
	_rulesArray[5]	= Rule(Coordinate(0,		0,		0),	Coordinate(x-l+1,	y,		z-l+1),	x*y+1);
	_rulesArray[6]	= Rule(Coordinate(l-1,		0,		0),	Coordinate(x,		y,		z-l+1),	x*y-1);
	_rulesArray[7]	= Rule(Coordinate(0,		0,		0),	Coordinate(x,		y-l+1,	z-l+1),	x*(y+1));
	_rulesArray[8]	= Rule(Coordinate(0,		l-1,	0),	Coordinate(x,		y,		z-l+1),	x*(y-1));
	_rulesArray[9]	= Rule(Coordinate(0,		0,		0),	Coordinate(x-l+1,	y-l+1,	z-l+1),	x*(y+1)+1);
	_rulesArray[10]	= Rule(Coordinate(l-1,		0,		0),	Coordinate(x,		y-l+1,	z-l+1),	x*(y+1)-1);
	_rulesArray[11]	= Rule(Coordinate(0,		1,		0),	Coordinate(x-l+1,	y,		z-l+1),	x*(y-1)+1);
	_rulesArray[12]	= Rule(Coordinate(l-1,		l-1,	0),	Coordinate(x,		y,		z-l+1),	x*(y-1)-1);
}

Rules::~Rules() {
	delete [] _rulesArray;
}

void Rules::findStraights(GameField* gamefield) {
	for (uint8_t p = 0; p < gamefield->getPlayersCount(); p++) {
		for (uint8_t r = 0; r < _rulesCount; r++) {
			for (uint8_t z = _rulesArray[r].getStart()->getZ(); z < _rulesArray[r].getEnd()->getZ(); z++) {
				for (uint8_t y = _rulesArray[r].getStart()->getY(); y < _rulesArray[r].getEnd()->getY(); y++) {
					for (uint8_t x = _rulesArray[r].getStart()->getX(); x < _rulesArray[r].getEnd()->getX(); x++) {
						uint8_t index = gamefield->index(x, y, z);
						int straightLength = 0;
						while (gamefield->getCell(index)->getOwner()->getColor() == p && straightLength < _straightLength && index < gamefield->getCubeSize()) {
							index += _rulesArray[r].getStraightStep();
							straightLength++;
						}
						if (straightLength == _straightLength) {
							gamefield->getPlayer((Color)p)->addStraight(gamefield->index(x, y, z), _rulesArray[r].getStraightStep(), straightLength);
						}
					}
				}
			}
		}
	}
}

Rules::Rule::Rule() {
	
}

Rules::Rule::Rule(Coordinate cubeTripStart, Coordinate cubeTripEnd, uint8_t straightStep) {
	_cubeTripStart = cubeTripStart;
	_cubeTripEnd = cubeTripEnd;
	_straightStep = straightStep;
}

Coordinate* Rules::Rule::getStart() {
	return &_cubeTripStart;
}

Coordinate* Rules::Rule::getEnd() {
	return &_cubeTripEnd;
}

uint8_t Rules::Rule::getStraightStep() {
	return _straightStep;
}