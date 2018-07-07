#include <Arduino.h>
#include "Legs.h"
#include "PhysicalLeg.h"
#include "RemoteLeg.h"
#include "Motor.h"
#include "Com.h"
#include "Max7219.h"
#include "Util.h"

const uint8_t CHAR_I[8] = {0x0, 0x81, 0x81, 0xFF, 0x81, 0x81, 0x0, 0x0};
const uint8_t CHAR_HEART[8] = {0xC, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0xC};
const uint8_t CHAR_P[8] = {0x0, 0x0, 0xFF, 0x11, 0x11, 0x11, 0xE, 0x0};
const uint8_t CHAR_S[8] = {0x0, 0x46, 0x49, 0x49, 0x49, 0x49, 0x31, 0x0};
const uint8_t CHAR_T[8] = {0x0, 0x1, 0x1, 0xFF, 0x1, 0x1, 0x0, 0x0};
const uint8_t CHAR_J[8] = {0x0, 0x40, 0x81, 0x81, 0x7F, 0x1, 0x1, 0x0};
const uint8_t CHAR_SMILE[8] = {0x0, 0x1, 0x2, 0x2, 0x2, 0x2, 0x1, 0x0};
const uint8_t CHAR_MOUTH[8] = {0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0, 0x0};

const uint8_t PIN_CS = 2;
const uint8_t PIN_CLK = 3;
const uint8_t PIN_DIN = 4;

const uint8_t PIN_MOTOR[] = {10, 11, 6, 5};
const int ANGLE_MOTOR[] = {90, 90, 90, 90};
const int OFFSET_MOTOR[] = {-25, 10, 37, -22};

float radar();

bool stateDisplay;

PhysicalLeg *leftLeg;
RemoteLeg *rightLeg;

MAX7219 *myMatrix;


void setup() {

    leftLeg = new PhysicalLeg(10, 11, 6, 5, LEFT);
    leftLeg->init();

    myMatrix = new MAX7219(PIN_CLK, PIN_CS, PIN_DIN);
    myMatrix->init();
    myMatrix->setBrightness(5);
    myMatrix->setShutdown(true);


}

void onResave(Commande &commande){
    switch(commande.id){
        case COMMANDE_BUTTON:
            stateDisplay = !stateDisplay;
            myMatrix->setShutdown(!stateDisplay);
            break;
        default:
            break;
    }
}

void loop() {

    checkResave();

    if(stateDisplay) {

        myMatrix->writeCharacter(CHAR_I);
        delay(500);
        myMatrix->writeCharacter(CHAR_HEART);
        delay(500);
        myMatrix->writeCharacter(CHAR_P);
        delay(500);
        myMatrix->writeCharacter(CHAR_S);
        delay(500);
        myMatrix->writeCharacter(CHAR_T);
        delay(500);
        myMatrix->writeCharacter(CHAR_J);
        delay(500);
    }

}
