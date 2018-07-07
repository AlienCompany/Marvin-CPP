#include <Arduino.h>
#include "PhysicalLeg.h"
#include "Com.h"
#include "HcSr04.h"
#include "Util.h"

const int PIN_GND_1 = 4;

const int PIN_TRIG = 12;
const int PIN_ECHO = 13;

const uint8_t PIN_MOTOR[] = {11, 10, 6, 5};
const int OFFSET_MOTOR[] = {-9, -10, 78, -16};
const int ANGLE_MOTOR[] = {90, 90, 90, 90};

const uint8_t PIN_BUTTON_MATRIX = 8;
bool stateButtonMatrix;
bool oldStateButtonMatrix;

PhysicalLeg *rightLeg;

void setup() {
    Serial.begin(9600);

    Motor* motorHip = new Motor(PIN_MOTOR[0], OFFSET_MOTOR[0], ANGLE_MOTOR[0]);
    Motor* motorKnee = new Motor(PIN_MOTOR[1], OFFSET_MOTOR[1], ANGLE_MOTOR[1]);
    Motor* motorAnkle = new Motor(PIN_MOTOR[2], OFFSET_MOTOR[2], ANGLE_MOTOR[2]);
    Motor* motorFoot = new Motor(PIN_MOTOR[3], OFFSET_MOTOR[3], ANGLE_MOTOR[3]);
    rightLeg = new PhysicalLeg(RIGHT, motorHip, motorKnee, motorAnkle, motorFoot);
    rightLeg->init();

    pinMode(PIN_BUTTON_MATRIX, INPUT_PULLUP);

}

void onResave(Commande &commande) {
    switch (commande.id) {
        case COMMANDE_LEG:
            Commande_16 commande_16 = to_16(commande);
            switch (commande_16.data0){
                case MOTOR_HIP:
                    rightLeg->setDegHip(commande_16.data1);
                    break;
                case MOTOR_KNEE:
                    rightLeg->setDegKnee(commande_16.data1);
                    break;
                case MOTOR_ANKLE:
                    rightLeg->setDegAnkle(commande_16.data1);
                    break;
                case MOTOR_FOOT:
                    rightLeg->setDegFoot(commande_16.data1);
                    break;
            }
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