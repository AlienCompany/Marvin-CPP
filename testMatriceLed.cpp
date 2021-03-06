#include <Arduino.h>
#include "Max7219.h"

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

MAX7219 *myMatrix;

const int PIN_BUTTON_MATRIX = 7;
bool stateButton1;
bool oldStateButtonMatrix;
bool stateDisplay = true;

void setup() {

    myMatrix = new MAX7219(PIN_CLK, PIN_CS, PIN_DIN);
    myMatrix->init();
    myMatrix->setBrightness(5);
    //myMatrix->setShutdown(true);

    pinMode(PIN_BUTTON_MATRIX, INPUT_PULLUP);


}

void loop() {

    stateButton1 = (bool) digitalRead(PIN_BUTTON_MATRIX);

    if(stateButton1 == LOW && oldStateButtonMatrix == HIGH) {

        //stateDisplay = !stateDisplay;

       // myMatrix->setShutdown(!stateDisplay);
    }

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
    oldStateButtonMatrix = stateButton1;
}