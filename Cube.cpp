#include "Cube.h"
#include "Setup.h"
#include "Bounce.h"
#include "Arduino.h"

Cube::Cube() {
	_gameField = new GameField(X_SIZE, Y_SIZE, Z_SIZE, PLAYERS_COUNT);

	pCubeMethod* cbb = new pCubeMethod[BUTTONS_COUNT];
	cbb[xButton] = &Cube::manipulateX;
	cbb[yButton] = &Cube::manipulateY;
	cbb[zButton] = &Cube::manipulateZ;
	cbb[actionButton] = &Cube::manipulateAction;

	_manipulator = new Manipulator(BUTTONS_COUNT, cbb);

	delete [] cbb;

	_ledDrive = new LedDrive(_gameField, _manipulator);

	_currentPlayer = _gameField->getPlayer(BLUE);
	
	_rules = new Rules(X_SIZE, Y_SIZE, Z_SIZE, STRAIGHT_LENGTH);
}

Cube::~Cube() {
	delete _gameField;
	delete _manipulator;
	delete _ledDrive;
	delete _rules;
}

void Cube::meshButtonPress() {
	_buttonDrive.meshButtonPress(this, _manipulator);
}

void Cube::playerMove() {
	if (_gameField->isMoveAble() && _gameField->setOwner(_currentPlayer, _manipulator->getX(), _manipulator->getY(), _manipulator->getZ()) ) {
		_currentPlayer = _gameField->nextPlayer(_currentPlayer);
		if (!_gameField->isMoveAble()) {
			_rules->findStraights(_gameField);
			Serial.print("Blue: ");Serial.println(_gameField->getPlayer(BLUE)->getStraightsCount());
			Serial.print("Red: ");Serial.println(_gameField->getPlayer(RED)->getStraightsCount());
		}
	}
}

void Cube::show() {
	_ledDrive->show();
}

void Cube::manipulateX() {
	_manipulator->iterateX();
}

void Cube::manipulateY() {
	_manipulator->iterateY();
}

void Cube::manipulateZ() {
	_manipulator->iterateZ();
}

void Cube::manipulateAction() {
	playerMove();
}

void Cube::checkLeds() {
	_ledDrive->check();
}

// MANIPULATOR

Cube::Manipulator::Manipulator(uint8_t cbbSize, pCubeMethod* CBB) {
	_X = 0;
	_Y = 0;
	_Z = 0;
	_CBB = new pCubeMethod[BUTTONS_COUNT];
	for (uint8_t i = xButton; i < BUTTONS_COUNT; i++) {
		_CBB[i] = CBB[i];
	}
}

Cube::Manipulator::~Manipulator() {
	delete [] _CBB;
}

void Cube::Manipulator::iterateX() {
	if (_X < X_SIZE - 1)
		_X++;
	else
		_X = 0;
}

void Cube::Manipulator::iterateY() {
	if (_Y < Y_SIZE - 1)
		_Y++;
	else
		_Y = 0;
}

void Cube::Manipulator::iterateZ() {
	if (_Z < Z_SIZE - 1)
		_Z++;
	else
		_Z = 0;
}

pCubeMethod* Cube::Manipulator::getButtonsAction() const {
	return _CBB;
}

bool Cube::Manipulator::operator== (Coordinate& c) {
	if (this == &c)
		return true;
	else
		return this->_X == c.getX()
		&& this->_Y == c.getY()
		&& this->_Z == c.getZ();
}
// BUTTONDRIVE

Cube::ButtonDrive::ButtonDrive() {
	for (int i = 0; i < BUTTONS_COUNT; i++) {
		pinMode(BUTTONS[i].pin, INPUT);
	}

	_buttons = new Bounce[BUTTONS_COUNT];
	for (uint8_t b = xButton; b < BUTTONS_COUNT; b++) {
		_buttons[b] = Bounce(BUTTONS[b].pin, DEBONCE_INTERVAL);
	}
}

Cube::ButtonDrive::~ButtonDrive() {
	delete []_buttons;
}

void Cube::ButtonDrive::meshButtonPress(Cube* cube, Manipulator* manipulator) {
	for (uint8_t b = xButton; b < BUTTONS_COUNT; b++) {
		_buttons[b].update();
		if (_buttons[b].risingEdge()) {
			(cube->*manipulator->getButtonsAction()[b])();
		}
	}
}

const Button Cube::ButtonDrive::BUTTONS[BUTTONS_COUNT] = {
	{ X_ITERATOR_PIN,	xButton },
	{ Y_ITERATOR_PIN,	yButton },
	{ Z_ITERATOR_PIN,	zButton },
	{ ACTION_PIN,		actionButton },
};

// LEDDRIVE

Cube::LedDrive::LedDrive(GameField* gameField, Manipulator* manipulator) {
	_gameField = gameField;
	_manipulator = manipulator;
	_blindManipulator = false;
	_blindManipulatorTimer = 0;

	uint8_t decoderPins[DECODER_BITS] = { D0, D1, D2, D3, D4 };
	uint8_t cathodePins[CATHODE_PINS] = { C0, C1, C2 };
	_decoder = new Decoder(COLORS_PER_LED, X_SIZE, DPP, DECODER_BITS, decoderPins, CATHODE_PINS, cathodePins);
}

Cube::LedDrive::~LedDrive() {
	delete _decoder;
}

void Cube::LedDrive::show() {
	for (uint8_t z = 0; z < Z_SIZE; z++) {
		for (uint8_t y = 0; y < Y_SIZE; y++) {
			for (uint8_t x = 0; x < X_SIZE; x++) {
				Player* player = _gameField->getOwner(x, y, z);
				Coordinate coordinate(x, y, z);
				if (*_manipulator == coordinate)
					modeBlindManipulator(player, x, y, z);
				else
					modeLight(player, x, y, z);
			}
		}
	}
}

void Cube::LedDrive::modeBlindManipulator(Player* player, uint8_t x, uint8_t y, uint8_t z) {
	uint64_t timer = millis();

	if (timer - _blindManipulatorTimer > MANIPULATOR_BLIND_INTERVAL) {
		_blindManipulatorTimer = timer;

		_blindManipulator = !_blindManipulator;
	}

	if (_blindManipulator) {
		_decoder->display(BRIGHTNESS / COLORS_PER_LED, BLUE, x, y, z);
		_decoder->display(BRIGHTNESS / COLORS_PER_LED, RED, x, y, z);
	}
	else {
		modeLight(player, x, y, z);
	}
}

void Cube::LedDrive::modeLight(Player* player, uint8_t x, uint8_t y, uint8_t z) {
	if (player) {
		_decoder->display(BRIGHTNESS, player->getColor(), x, y, z);
	}
	else {
		modeOff();
	}
}

void Cube::LedDrive::modeOff() {
	delayMicroseconds(BRIGHTNESS);
}

void Cube::LedDrive::check() {
	for (uint8_t c = 0; c < COLORS_PER_LED; c++) {
		for (uint8_t z = 0; z < Z_SIZE; z++) {
			for (uint8_t y = 0; y < Y_SIZE; y++) {
				for (uint8_t x = 0; x < X_SIZE; x++) {
					_decoder->display(BRIGHTNESS, c, x, y, z);
					delay(50);
				}
			}
		}
	}
}