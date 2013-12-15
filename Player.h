#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <inttypes.h>
#include "Straight.h"
#include "QueueList.h"
#include <vector>
#include "Setup.h"

class Player {
public:
	Player();
	Player(Color color);
	Color getColor();
	void addStraight(uint8_t cubeTripStart, uint8_t straightStep, uint8_t straightLength);
	uint8_t getStraightsCount();
	QueueList<Straight>* getStraights();

private:
	Color _color;
	QueueList<Straight> _straights;
};

#endif