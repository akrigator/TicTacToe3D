#include "GameField.h"
#include "Setup.h"

GameField::GameField() {

}

GameField::GameField(uint8_t xSize, uint8_t ySize, uint8_t zSize, uint8_t playersCount) {
	_xSize = xSize;
	_ySize = ySize;
	_zSize = zSize;
	_cubeSize = _xSize * _ySize * _zSize;
	_playersCount = playersCount;
	_field = new Cell[_cubeSize];
	_moveAbility = true;
	for (uint8_t z = 0; z < _zSize; z++) {
		for (uint8_t y = 0; y < _ySize; y++) {
			for (uint8_t x = 0; x < _xSize; x++) {
				_field[index(x, y, z)] = Cell(x, y, z);
			}
		}
	}

	_players = new Player[_playersCount];
	for (uint8_t p = (uint8_t) BLUE; p < _playersCount; p++) {
		_players[p] = Player((Color)p);
	}
}

GameField::~GameField() {
	delete[] _field;
	delete[] _players;
}

Player* GameField::getPlayer(Color color) {
	return &_players[color];
}

Player* GameField::getOwner(uint8_t x, uint8_t y, uint8_t z) {
	return _field[index(x,y,z)].getOwner();
}

bool GameField::setOwner(Player* player, uint8_t x, uint8_t y, uint8_t z) {
	return getCell(x, y, z)->setOwner(player);
}

Player* GameField::nextPlayer(Player* currentPlayer) {
	for (uint8_t p = BLUE; p < _playersCount; p++) {
		if (_players == currentPlayer && p < (_playersCount - 1))
			return &_players[p + 1];
		else
			return &_players[BLUE];
	}
}

Cell* GameField::getCell(uint8_t x, uint8_t y, uint8_t z) {
	return &_field[index(x, y, z)];
}

Cell* GameField::getCell(uint8_t index) {
	return &_field[index];
}

uint8_t GameField::index(uint8_t x, uint8_t y, uint8_t z) {
	return x + _xSize * (y + z * _ySize);
}

bool GameField::getMoveAbility() {
	return _moveAbility;
}

bool GameField::isMoveAble() {
	uint8_t counter = 0;
	for (uint8_t i = 0; i < _cubeSize; i++) {
		if (_field[i].getOwner())
			counter++;
	}
	return _moveAbility = ( _cubeSize - counter > _cubeSize % _playersCount );
}

uint8_t GameField::getPlayersCount() {
	return _playersCount;
}

uint8_t GameField::getCubeSize() {
	return _cubeSize;
}

/*
 * bool GameField::animate()
 * Returns:
 *         'false' if straights of all players are animated.
 *         'true' if at least one straight is not animated yet.
 */
bool GameField::animate() {
	clearOwners();
	bool allIsEmpty;
	for (uint8_t p = 0; p < _playersCount; p++) {
		bool isEmpty = _players[p].getStraights()->isEmpty();
		
		if (p == 0)
			allIsEmpty = isEmpty;
		else
			allIsEmpty = allIsEmpty && isEmpty;
			
		if (!isEmpty)
			addStraight(_players[p].getStraights()->pop());
	}
	return allIsEmpty;
}

void GameField::reset() {
	clearOwners();
	_moveAbility = true;
}

void GameField::clearOwners() {
	for (uint8_t i = 0; i < _cubeSize; i++) {
		_field[i].removeOwner();
	}
}

void GameField::addStraight(Straight straight) {
	for (uint8_t length = 0, i = straight.getCubeTripStart(); length < straight.getStraightLength(); length++, i += straight.getStraightStep()) {
		_field[i].setOwner(&_players[straight.getColor()]);
	}
}