#ifndef _RULES_H_
#define _RULES_H_

#include <inttypes.h>
#include "GameField.h"
#include "Coordinate.h"

class Rules {
public:
	Rules(uint8_t xSize, uint8_t ySize, uint8_t zSize, uint8_t straightLength);
	~Rules();
	void findStraights(GameField* gamefield);
private:
	class Rule {
	public:
		Rule();
		Rule(Coordinate cubeTripStart, Coordinate cubeTripEnd, uint8_t straightStep);
		Coordinate* getStart();
		Coordinate* getEnd();
		uint8_t getStraightStep();
	private:
		Coordinate _cubeTripStart;
		Coordinate _cubeTripEnd;
		uint8_t _straightStep;
	};
	Rule* _rulesArray;
	static const uint8_t _rulesCount = 13;
	uint8_t _straightLength;
};

#endif