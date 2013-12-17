#ifndef _DECODER_H_
#define _DECODER_H_

#include <inttypes.h>

class Decoder {
public:
	Decoder(uint8_t colorsPerLed, 
		uint8_t xSize, 
		uint8_t decoderPinsCount, 
		uint8_t* decoderPins, 
		uint8_t cathodePinsCount, 
		uint8_t* cathodePins);
	~Decoder();
	void display(int brightness, uint8_t color, uint8_t x, uint8_t y, uint8_t z);
private:
	uint8_t _colorsPerLed;
	uint8_t _xSize;
	uint8_t _decoderPinsCount;
	uint8_t _cathodePinsCount;
	uint8_t* _decoderPins;
	uint8_t* _cathodePins;
	void cathode(uint8_t layer);
	void cathodesOff();
	void displayNum(int brightness, uint8_t ledNum);
};

#endif