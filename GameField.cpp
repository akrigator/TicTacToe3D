#include "GameField.h"

GameField::GameField() {

}

GameField::GameField(uint8_t xSize, uint8_t ySize, uint8_t zSize, uint8_t playersCount) {
	_xSize = xSize;
	_ySize = ySize;
	_zSize = zSize;
	_cubeSize = _xSize * _ySize * _zSize;
	_playersCount = playersCount;
	_field = new Cell[_cubeSize];
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

bool GameField::isMoveAble() {
	uint8_t counter = 0;
	for (uint8_t i = 0; i < _cubeSize; i++) {
		if (_field[i].getOwner())
			counter++;
	}
	return _cubeSize - counter > _cubeSize % _playersCount;
}

uint8_t GameField::getPlayersCount() {
	return _playersCount;
}

uint8_t GameField::getCubeSize() {
	return _cubeSize;
}