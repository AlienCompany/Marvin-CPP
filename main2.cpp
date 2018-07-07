#include <Arduino.h>
#include "PhysicalLeg.h"
#include "Com.h"
#include "HcSr04.h"
#include "Util.h"

const int PIN_GND_1 = 4;

const int PIN_TRIG = 12;
const int PIN_ECHO = 13;

const uint8_t PIN_MOTOR[] = {10, 11, 6, 5};
const int ANGLE_MOTOR[] = {90, 90, 90, 90};
const int OFFSET_MOTOR[] = {-23, -8, 78, -13};

const uint8_t PIN_BUTTON_MATRIX = 7;
bool stateButtonMatrix;
bool oldStateButtonMatrix;

PhysicalLeg *rightLeg;

void setup() {

   // rightLeg = new PhysicalLeg(10, 11, 6, 5, RIGHT);
   // rightLeg->init();

    pinMode(PIN_BUTTON_MATRIX, INPUT_PULLUP);

}

void onResave(Commande &commande) {
    switch (commande.id) {
        default:
            break;
    }
}

void loop() {

    checkResave();

    stateButtonMatrix = (bool) digitalRead(PIN_BUTTON_MATRIX);

    if(stateButtonMatrix == LOW && oldStateButtonMatrix == HIGH){

        sendCommande(COMMANDE_BUTTON,BUTTON_MATRIX);

    }

    oldStateButtonMatrix = stateButtonMatrix;
}