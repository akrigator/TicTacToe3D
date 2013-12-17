#include "Decoder.h"
#include "Setup.h"
#include "Arduino.h"

Decoder::Decoder(uint8_t colorsPerLed, uint8_t xSize, uint8_t decoderPinsCount, uint8_t* decoderPins, uint8_t cathodePinsCount, uint8_t* cathodePins) {
	_colorsPerLed = colorsPerLed;
	_xSize = xSize;
	_decoderPinsCount = decoderPinsCount;
	_cathodePinsCount = cathodePinsCount;

	_decoderPins = new uint8_t[_decoderPinsCount];
	for (uint8_t pin = 0; pin < _decoderPinsCount; pin++) {
		_decoderPins[pin] = decoderPins[pin];
	}

	_cathodePins = new uint8_t[_cathodePinsCount];
	for (uint8_t pin = 0; pin < _cathodePinsCount; pin++) {
		_cathodePins[pin] = cathodePins[pin];
	}

	for (int pin = 0; pin < _decoderPinsCount; pin++) {
		pinMode(_decoderPins[pin], OUTPUT);
	}
	for (int pin = 0; pin < _cathodePinsCount; pin++) {
		pinMode(_cathodePins[pin], OUTPUT);
	}
}

Decoder::~Decoder() {
	delete[] _decoderPins;
	delete[] _cathodePins;
}

void Decoder::cathode(uint8_t layer) {
	for (int pin = 0; pin < _cathodePinsCount; pin++) {
		if (pin == layer || layer >= _cathodePinsCount) {
			digitalWrite(_cathodePins[pin], HIGH);
		}
		else {
			digitalWrite(_cathodePins[pin], LOW);
		}
	}
}

void Decoder::cathodesOff() {
	for (int pin = 0; pin < _cathodePinsCount; pin++) {
		digitalWrite(_cathodePins[pin], LOW);
	}
}

void Decoder::displayNum(int brightness, uint8_t ledNum) {
	ledNum = constrain(ledNum, 0, CUBE_SIZE);
	for (int weight = 1, pin = 0; pin < _decoderPinsCount; weight = weight << 1, pin++)
		digitalWrite(_decoderPins[pin], (ledNum & weight) >> pin);
	delayMicroseconds(brightness);
	cathodesOff();
}

void Decoder::display(int brightness, uint8_t color, uint8_t x, uint8_t y, uint8_t z) {
	int lednum = y * _xSize + x;
	cathode(z);
	displayNum(brightness, _colorsPerLed * lednum + color);
}
