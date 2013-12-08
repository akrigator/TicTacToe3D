#include "Player.h"

Player::Player() {

}

Player::Player(Color color) {
	_color = color;
}

Color Player::getColor() {
	return _color;
}