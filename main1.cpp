#include <Arduino.h>
#include "Legs.h"
#include "PhysicalLeg.h"
#include "RemoteLeg.h"
#include "Motor.h"
#include "Com.h"
#include "Max7219.h"
#include "Util.h"

const int PIN_DIN = 3;
const int PIN_CLK = 4;
const int PIN_CS = 5;

const int PIN_MOTOR[] = {10, 11, 6, 5};
const int ANGLE_MOTOR[] = {90, 90, 90, 90};
const int OFFSET_MOTOR[] = {-25, 10, 37, -22};

float radar();

PhysicalLeg *leftLeg;
RemoteLeg *rightLeg;


void setup() {
    leftLeg = new PhysicalLeg(10, 11, 6, 5, LEFT);
    leftLeg->init();



}

void loop() {



}
