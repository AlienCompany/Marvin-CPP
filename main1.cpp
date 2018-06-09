#include <Arduino.h>
#include "Legs.h"
#include "PhysicalLeg.h"

const int PIN_DIN = 3;
const int PIN_CLK = 4;
const int PIN_CS = 5;

float radar();

PhysicalLeg *rightLeg;


enum PIN_MOTOR{
    PIN_A = 10,
    PIN_B = 11,
    PIN_C = 6,
    PIN_D = 5
};


void setup() {
}

void loop() {

}
