#ifndef _CUBE_H_
#define _CUBE_H_

#include "GameField.h"
#include "Decoder.h"
#include "Setup.h"
#include "Bounce.h"
#include "Rules.h"

class Cube;
typedef void (Cube::*pCubeMethod)();

enum ButtonsAction { xButton = 0, yButton, zButton, actionButton };

struct Button {
	uint8_t pin;
	ButtonsAction action;
};

class Cube {
public:
	Cube();
	~Cube();
	void meshButtonPress();
	void playerMove();
	void show();
	void checkLeds();

	class Manipulator : public Coordinate {
	public:
		Manipulator(uint8_t cbbSize, pCubeMethod* CBB);
		~Manipulator();
		void iterateX();
		void iterateY();
		void iterateZ();
		pCubeMethod* getButtonsAction() const;
		bool operator == (Coordinate& coordinate);
		bool isVisible();
		void setVisibility(bool visibility);
		void reset();
	private:
		pCubeMethod* _CBB;
		bool _visibility;
	};

	class ButtonDrive {
	public:
		ButtonDrive();
		~ButtonDrive();
		void meshButtonPress(Cube* cube, Manipulator* manipulator);
		void lock();
		void unlock();
	private:
		Bounce* _buttons;
		bool _lock;
		static const Button BUTTONS[BUTTONS_COUNT];
	};

	class LedDrive {
	public:
		LedDrive(GameField* gameField, Manipulator* manipulator);
		~LedDrive();
		void update();
		void check();
		void show();
	private:
		GameField* _gameField;
		Manipulator* _manipulator;
		Decoder* _decoder;
		bool _blinkManipulator;
		uint64_t _blinkManipulatorTimer;
		void modeBlindManipulator(Player* player, uint8_t x, uint8_t y, uint8_t z);
		void modeLight(Player* player, uint8_t x, uint8_t y, uint8_t z);
		void modeOff();
	};

protected:	
	GameField* _gameField;
	Manipulator* _manipulator;
	ButtonDrive _buttonDrive;
	LedDrive* _ledDrive;
	Player* _currentPlayer;
	Rules* _rules;
	uint64_t _animateBlink;
	void manipulateX();
	void manipulateY();
	void manipulateZ();
	void manipulateAction();
	void showResult();
	void reset();
	void findStraights();
};

#endif