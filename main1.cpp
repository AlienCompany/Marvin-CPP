#include <Arduino.h>
#include "Legs.h"
#include "PhysicalLeg.h"
#include "RemoteLeg.h"

const int PIN_DIN = 3;
const int PIN_CLK = 4;
const int PIN_CS = 5;

float radar();

PhysicalLeg *leftLeg;
RemoteLeg *rightLeg;


void setup() {
    leftLeg = new PhysicalLeg(10, 11, 6, 5);
    leftLeg->init();



}

void loop() {



}
