#include "Decoder.h"
#include "Setup.h"
#ifdef ARDUINO_CODE
#include "Arduino.h"
#else
#include <iostream>
#endif

Decoder::Decoder(uint8_t colorsPerLed, uint8_t xSize, uint8_t decoderPowerPin, uint8_t decoderPinsCount, uint8_t* decoderPins, uint8_t cathodePinsCount, uint8_t* cathodePins) {
	_colorsPerLed = colorsPerLed;
	_xSize = xSize;
	_decoderPowerPin = decoderPowerPin;
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

#ifdef ARDUINO_CODE
	pinMode(_decoderPowerPin, OUTPUT);
	for (int pin = 0; pin < _decoderPinsCount; pin++) {
		pinMode(_decoderPins[pin], OUTPUT);
	}
	for (int pin = 0; pin < _cathodePinsCount; pin++) {
		pinMode(_cathodePins[pin], OUTPUT);
	}
#else
	std::cout << "The pins of decoder and cathode are initialized\n";
#endif
}

Decoder::~Decoder() {
	delete[] _decoderPins;
	delete[] _cathodePins;
#ifndef ARDUINO_CODE
	std::cout << "The pins of decoder and cathode are destroied\n";
#endif
}

void Decoder::cathode(uint8_t layer) {
#ifdef ARDUINO_CODE
	for (int pin = 0; pin < _cathodePinsCount; pin++) {
		if (pin == layer || layer >= _cathodePinsCount) {
			digitalWrite(_cathodePins[pin], HIGH);
		}
		else {
			digitalWrite(_cathodePins[pin], LOW);
		}
	}
#endif
}

void Decoder::displayNum(int brightness, uint8_t ledNum) {
#ifdef ARDUINO_CODE
	digitalWrite(_decoderPowerPin, HIGH);
	ledNum = constrain(ledNum, 0, CUBE_SIZE);
	for (int weight = 1, pin = 0; pin < _decoderPinsCount; weight = weight << 1, pin++)
		digitalWrite(_decoderPins[pin], (ledNum & weight) >> pin);
	delayMicroseconds(brightness);
	digitalWrite(_decoderPowerPin, LOW);
#endif
}

void Decoder::display(int brightness, uint8_t color, uint8_t x, uint8_t y, uint8_t z) {
	int lednum = y * _xSize + x;
	cathode(z);
	displayNum(brightness, _colorsPerLed * lednum + color);
}
