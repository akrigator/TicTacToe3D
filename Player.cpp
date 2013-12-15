#include "Player.h"

Player::Player() {

}

Player::Player(Color color) {
	_color = color;
}

Color Player::getColor() {
	return _color;
}

void Player::addStraight(uint8_t cubeTripStart, uint8_t straihtStep, uint8_t straightLength) {
	_straights.push(Straight(cubeTripStart, straihtStep, straightLength, getColor()));
}

uint8_t Player::getStraightsCount() {
	return _straights.count();
}

QueueList<Straight>* Player::getStraights() {
	return &_straights;
}
