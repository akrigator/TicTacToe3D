#ifndef _SETUP_H_
#define _SETUP_H_

#define X_SIZE						3
#define Y_SIZE						3
#define Z_SIZE						3
#define CUBE_SIZE					X_SIZE * Y_SIZE * Z_SIZE
#define STRAIGHT_LENGTH				X_SIZE

#define PLAYERS_COUNT				2	

#define COLORS_PER_LED				2
enum Color { BLUE = 0, RED };
#define BRIGHTNESS					500	// Time interval (microseconds) in which ONLY an one led is light
#define MANIPULATOR_BLINK_INTERVAL	500
#define ANIMATE_INTERVAL			3000

#define DEBONCE_INTERVAL			20	// Time interval (milliseconds) of the buttons debonce
#define BUTTONS_COUNT				4
#define X_ITERATOR_PIN				A5
#define Y_ITERATOR_PIN				A4
#define Z_ITERATOR_PIN				A3
#define ACTION_PIN					A2

#define DPP							10	// Decoder power pin
#define DECODER_BITS				5	// log2 (X_SIZE * Y_SIZE * COLORS_PER_LED)
#define D0							2
#define D1							3
#define D2							4
#define D3							5
#define D4							6

#define CATHODE_PINS				Z_SIZE
#define C0							7
#define C1							8
#define C2							9

#endif