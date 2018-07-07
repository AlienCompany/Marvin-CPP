#include <Arduino.h>
#include "PhysicalLeg.h"

const int PIN_GND_1 = 4;

const int PIN_TRIG = 12;
const int PIN_ECHO = 13;



PhysicalLeg *rightLeg;




void setup() {
    rightLeg = new PhysicalLeg(10, 11, 6, 5);
    rightLeg->init();



}

void loop() {




}