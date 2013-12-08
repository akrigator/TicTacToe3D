#include "Cube.h"

Cube cube;

void setup() {
  // put your setup code here, to run once:
  cube.checkLeds();
}

void loop() {
  // put your main code here, to run repeatedly: 
  cube.show();
  cube.meshButtonPress();
}
