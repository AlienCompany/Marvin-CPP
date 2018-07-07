#include <Arduino.h>
#include "Legs.h"
#include "PhysicalLeg.h"
#include "RemoteLeg.h"
#include "Motor.h"
#include "Com.h"
#include "Max7219.h"
#include "Util.h"

struct defilement {
    const uint8_t **chars;
    const uint8_t longeur;
};


const uint8_t CHAR_EMPTY[8] = {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
const uint8_t CHAR_I[8] = {0x0, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x0, 0x0};
const uint8_t CHAR_HEART[8] = {0xC, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0xC};
const uint8_t CHAR_P[8] = {0x0, 0x0, 0xFF, 0x11, 0x11, 0x11, 0xE, 0x0};
const uint8_t CHAR_S[8] = {0x0, 0x46, 0x49, 0x49, 0x49, 0x49, 0x31, 0x0};
const uint8_t CHAR_T[8] = {0x0, 0x1, 0x1, 0xFF, 0x1, 0x1, 0x0, 0x0};
const uint8_t CHAR_J[8] = {0x0, 0x40, 0x81, 0x81, 0x7F, 0x1, 0x1, 0x0};
const uint8_t CHAR_SMILE[8] = {0x0, 0x2, 0x4, 0x4, 0x4, 0x4, 0x2, 0x0};
const uint8_t CHAR_MOUTH[8] = {0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0, 0x0};

const uint8_t PIN_CS = 2;
const uint8_t PIN_CLK = 3;
const uint8_t PIN_DIN = 4;

const uint8_t PIN_MOTOR[] = {10, 11, 6, 5};
const int OFFSET_MOTOR[] = {0, 11, 36, -44};
const int ANGLE_MOTOR[] = {90, 90, 90, 90};

const uint8_t *DEFILEMNT_I_LOVE_PSTJ_CHARS[] = {CHAR_I, CHAR_HEART, CHAR_P, CHAR_S, CHAR_T, CHAR_J};

const defilement DEFILEMNT_I_LOVE_PSTJ = {DEFILEMNT_I_LOVE_PSTJ_CHARS, 6};

const defilement *currentDefilement = &DEFILEMNT_I_LOVE_PSTJ;

bool stateDisplay = false;

Leg *leftLeg;
Leg *rightLeg;
Legs *legs;

MAX7219 *myMatrix;

uint8_t matrixAvancement = 0;
int8_t matrixAvancementDecalage = 0;
long nextAvancement = 0;
int matrixDeley = 100;

void matrixRefresh() {
    if (millis() > nextAvancement) {
        nextAvancement += matrixDeley;

        matrixAvancementDecalage++;
        if (matrixAvancementDecalage == 8) {
            matrixAvancement++;
            matrixAvancementDecalage = 0;
            if (matrixAvancement >= currentDefilement->longeur) {
                matrixAvancementDecalage = -8;
                matrixAvancement = 0;
                myMatrix->writeCharacter(CHAR_EMPTY);
            }
        }

        const uint8_t *currentChar = currentDefilement->chars[matrixAvancement];
        const uint8_t *nextChar = CHAR_EMPTY;

        if (matrixAvancement + 1 < currentDefilement->longeur) {
            nextChar = currentDefilement->chars[matrixAvancement + 1];
        }
        myMatrix->writeCharacter(currentChar, matrixAvancementDecalage);
        myMatrix->writeCharacter(nextChar, matrixAvancementDecalage - 8);
    }
}

void setup() {
    Serial.begin(9600);

    Motor *motorHip = new Motor(PIN_MOTOR[0], OFFSET_MOTOR[0], ANGLE_MOTOR[0]);
    Motor *motorKnee = new Motor(PIN_MOTOR[1], OFFSET_MOTOR[1], ANGLE_MOTOR[1]);
    Motor *motorAnkle = new Motor(PIN_MOTOR[2], OFFSET_MOTOR[2], ANGLE_MOTOR[2]);
    Motor *motorFoot = new Motor(PIN_MOTOR[3], OFFSET_MOTOR[3], ANGLE_MOTOR[3]);


    leftLeg = new PhysicalLeg(LEFT, motorHip, motorKnee, motorAnkle, motorFoot);
    rightLeg = new RemoteLeg(RIGHT);
    legs = new Legs(leftLeg, rightLeg);
    legs->init();

    motorHip->motorOff();
    motorKnee->motorOff();
    motorAnkle->motorOff();
    motorFoot->motorOff();


    myMatrix = new MAX7219(PIN_CLK, PIN_CS, PIN_DIN);
    myMatrix->init();
    myMatrix->setBrightness(4);
    myMatrix->writeCharacter(CHAR_SMILE);


}

void onReceive(Commande &commande) {
    switch (commande.id) {
        case COMMANDE_BUTTON:
            if(commande.data == BUTTON_MATRIX) {
                stateDisplay = !stateDisplay;
                if(!stateDisplay){
                    myMatrix->writeCharacter(CHAR_SMILE);
                }else{
                    matrixAvancement = 0;
                    matrixAvancementDecalage = 0;
                    nextAvancement = millis() + matrixDeley;
                }
            }else if(commande.data == BUTTON_MOTOR) {
                if(legs->getCurrentAnnimation() == &LEG_ANNIM_WORLK){
                    legs->changeAnnimation(&LEG_ANNIM_WAIT, false);
                }else{
                    legs->changeAnnimation(&LEG_ANNIM_WORLK, true);
                }
            }
            break;
        default:
            break;
    }
}

void loop() {

    checkReceive();

    if (stateDisplay)matrixRefresh();

}
