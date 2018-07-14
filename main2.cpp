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

const uint8_t PIN_BUTTON_MATRIX2 = 2;
bool stateButtonMatrix2;
bool oldStateButtonMatrix2;

const uint8_t PIN_BUTTON_WALK = 7;
bool stateButtonWalk;
bool oldStateButtonWalk;

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
    pinMode(PIN_BUTTON_WALK, INPUT_PULLUP);
    pinMode(4, OUTPUT);

    digitalWrite(4,LOW);

}

void onReceive(Commande &commande) {
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

    checkReceive();

    stateButtonMatrix = (bool) digitalRead(PIN_BUTTON_MATRIX);
   // stateButtonMatrix2 = (bool) digitalRead(PIN_BUTTON_MATRIX2);
    stateButtonWalk = (bool) digitalRead(PIN_BUTTON_WALK);


    if(stateButtonMatrix == LOW && oldStateButtonMatrix == HIGH){

        sendCommande(COMMANDE_BUTTON,BUTTON_MATRIX);

    }

   if(stateButtonMatrix2 == LOW && oldStateButtonMatrix2 == HIGH){

        sendCommande(COMMANDE_BUTTON,BUTTON_MATRIX2);

    }

    if(stateButtonWalk == LOW && oldStateButtonWalk == HIGH){

        sendCommande(COMMANDE_BUTTON,BUTTON_MOTOR);

    }

    oldStateButtonMatrix = stateButtonMatrix;
    oldStateButtonMatrix2 = stateButtonMatrix2;
    oldStateButtonWalk = stateButtonWalk;
}