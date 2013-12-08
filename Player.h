#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <inttypes.h>

enum Color { BLUE = 0, RED };

class Player {
public:
	Player();
	Player(Color color);
	Color getColor();

private:
	Color _color;
};

#endif