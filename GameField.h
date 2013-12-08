#ifndef _GAMEFIELD_H_
#define _GAMEFIELD_H_

#include "Cell.h"

class GameField {
public:
	GameField();
	GameField(uint8_t xSize, uint8_t ySize, uint8_t zSize, uint8_t playersCount);
	~GameField();
	Player* getPlayer(Color color);
	Player* getOwner(uint8_t x, uint8_t y, uint8_t z);
	bool setOwner(Player* player, uint8_t x, uint8_t y, uint8_t z);
	Player* nextPlayer(Player* currentPlayer);

private:
	Player* _players;
	uint8_t _xSize; 
	uint8_t _ySize;
	uint8_t _zSize;
	uint8_t _cubeSize;
	uint8_t _playersCount;
	Cell* _field;
	Cell* getCell(uint8_t x, uint8_t y, uint8_t z);
	uint8_t index(uint8_t x, uint8_t y, uint8_t z);
};

#endif