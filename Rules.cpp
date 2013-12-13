#include "Rules.h"

Rules::Rules(uint8_t xSize, uint8_t ySize, uint8_t zSize, uint8_t straightLength) {
	_straightLength = straightLength;
	_rulesArray = new Rule[_rulesCount];
	//2D
	_rulesArray[0]	= Rule(Coordinate(0, 0, 0),	Coordinate(xSize-1,	ySize,		zSize),		1);
	_rulesArray[1]	= Rule(Coordinate(0, 0, 0),	Coordinate(xSize,	ySize-1,	zSize),		xSize);
	_rulesArray[2]	= Rule(Coordinate(0, 0, 0),	Coordinate(xSize-1,	ySize-1,	zSize),		xSize+1);
	_rulesArray[3]	= Rule(Coordinate(1, 0, 0),	Coordinate(xSize,	ySize-1,	zSize),		xSize-1);
	//3D
	_rulesArray[4]	= Rule(Coordinate(0, 0, 0),	Coordinate(xSize,	ySize,		zSize-1),	xSize*ySize);
	_rulesArray[5]	= Rule(Coordinate(0, 0, 0),	Coordinate(xSize-1,	ySize,		zSize-1),	xSize*ySize+1);
	_rulesArray[6]	= Rule(Coordinate(1, 0, 0),	Coordinate(xSize,	ySize,		zSize-1),	xSize*ySize-1);
	_rulesArray[7]	= Rule(Coordinate(0, 0, 0),	Coordinate(xSize,	ySize-1,	zSize-1),	xSize*(ySize+1));
	_rulesArray[8]	= Rule(Coordinate(0, 1, 0),	Coordinate(xSize,	ySize,		zSize-1),	xSize*(ySize-1));
	_rulesArray[9]	= Rule(Coordinate(0, 0, 0),	Coordinate(xSize-1,	ySize-1,	zSize-1),	xSize*(ySize+1)+1);
	_rulesArray[10]	= Rule(Coordinate(1, 0, 0),	Coordinate(xSize,	ySize-1,	zSize-1),	xSize*(ySize+1)-1);
	_rulesArray[11]	= Rule(Coordinate(0, 1, 0),	Coordinate(xSize-1,	ySize,		zSize-1),	xSize*(ySize-1)+1);
	_rulesArray[12]	= Rule(Coordinate(1, 1, 0),	Coordinate(xSize,	ySize,		zSize-1),	xSize*(ySize-1)-1);
}

Rules::~Rules() {
	delete [] _rulesArray;
}

void Rules::findStraights(GameField* gamefield) {
	for (uint8_t p = 0; p < gamefield->getPlayersCount(); p++) {
		if (gamefield->getPlayer((Color)p)->getStraightsCount() != 0) {
			return;
		}
		for (uint8_t r = 0; r < _rulesCount; r++) {
			for (uint8_t z = _rulesArray[r].getStart()->getZ(); z < _rulesArray[r].getEnd()->getZ(); z++) {
				for (uint8_t y = _rulesArray[r].getStart()->getY(); y < _rulesArray[r].getEnd()->getY(); y++) {
					for (uint8_t x = _rulesArray[r].getStart()->getX(); x < _rulesArray[r].getEnd()->getX(); x++) {
						if (gamefield->getCell(x, y, z)->getOwner() == gamefield->getPlayer((Color)p)) {
							uint8_t rootIndex = gamefield->index(x, y, z);
							uint8_t nodeIndex = rootIndex + _rulesArray[r].getStraightStep();
							int straightLength = 1;
							while ( gamefield->getCell(rootIndex)->getOwner() == gamefield->getCell(nodeIndex)->getOwner() 
							&& nodeIndex < gamefield->getCubeSize() ) {
								straightLength++;
								rootIndex = nodeIndex;
								nodeIndex += _rulesArray[r].getStraightStep();
							}
							if (straightLength == _straightLength) {
								gamefield->getPlayer((Color)p)->addStraight(gamefield->index(x, y, z), _rulesArray[r].getStraightStep(), straightLength);
								/*Serial.print("p=");Serial.print(p);Serial.print(" ");
								Serial.print("r=");Serial.print(r);Serial.print(" ");
								Serial.print("z=");Serial.print(z);Serial.print(" ");
								Serial.print("y=");Serial.print(y);Serial.print(" ");
								Serial.print("x=");Serial.println(x);*/
							}
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