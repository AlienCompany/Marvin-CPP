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
//const uint8_t CHAR_S[8] = {0x0, 0x46, 0x49, 0x49, 0x49, 0x49, 0x31, 0x0};
const uint8_t CHAR_S[8] = {0x0, 0x0, 0x46, 0x89, 0x89, 0x89, 0x72, 0x0};
const uint8_t CHAR_T[8] = {0x0, 0x1, 0x1, 0xFF, 0x1, 0x1, 0x0, 0x0};
const uint8_t CHAR_J[8] = {0x0, 0x40, 0x81, 0x81, 0x7F, 0x1, 0x1, 0x0};

const uint8_t CHAR_SMILE[8] = {0x0, 0x2, 0x4, 0x4, 0x4, 0x4, 0x2, 0x0};
const uint8_t CHAR_MOUTH[8] = {0x0, 0x0, 0x6, 0x9, 0x9, 0x6, 0x0, 0x0};

const uint8_t CHAR_B[8] = {0x0, 0x0, 0xFF, 0x89, 0x89, 0x89, 0x76, 0x0};
const uint8_t CHAR_O[8] = {0x0, 0x0, 0x7E, 0x81, 0x81, 0x81, 0x7E, 0x0};
const uint8_t CHAR_N[8] = {0x0, 0x0, 0xFF, 0x10, 0x8, 0x4, 0xFF, 0x0};
const uint8_t CHAR_U[8] = {0x0, 0x0, 0x7F, 0x80, 0x80, 0x80, 0x7F, 0x0};
const uint8_t CHAR_R[8] = {0x0, 0x0, 0xFF, 0x11, 0x31, 0x51, 0x8E, 0x0};
const uint8_t CHAR_M[8] = {0x0, 0x0, 0xFF, 0x2, 0x4, 0x2, 0xFF, 0x0};
const uint8_t CHAR_A[8] = {0x0, 0x0, 0xFE, 0x11, 0x11, 0x11, 0xFE, 0x0};
const uint8_t CHAR_V[8] = {0x0, 0x0, 0x7, 0x38, 0xC0, 0x30, 0xF, 0x0};
const uint8_t CHAR_E[8] = {0x0, 0x0, 0xFF, 0x89, 0x89, 0x89, 0x81, 0x0};

const uint8_t PIN_CS = 2;
const uint8_t PIN_CLK = 3;
const uint8_t PIN_DIN = 4;

const uint8_t PIN_MOTOR[] = {11, 10, 6, 5};
const int OFFSET_MOTOR[] = {6, 5, 36, -44};
const int ANGLE_MOTOR[] = {90, 90, 90, 90};

const uint8_t *DEFILEMENT_I_LOVE_PSTJ_CHARS[] = {CHAR_I, CHAR_HEART, CHAR_P, CHAR_S, CHAR_T, CHAR_J};
const uint8_t *DEFILEMENT_BONJOUR_JE_SUIS_MARVIN_CHARS[] = {CHAR_B, CHAR_O, CHAR_N, CHAR_J, CHAR_O, CHAR_U, CHAR_R, CHAR_EMPTY, CHAR_J, CHAR_E, CHAR_EMPTY, CHAR_S, CHAR_U, CHAR_I, CHAR_S, CHAR_EMPTY, CHAR_M, CHAR_A, CHAR_R, CHAR_V, CHAR_I, CHAR_N};

const defilement DEFILEMENT_I_LOVE_PSTJ = {DEFILEMENT_I_LOVE_PSTJ_CHARS, 6};
const defilement DEFILEMENT_BONJOUR_JE_SUIS_MARVIN = {DEFILEMENT_BONJOUR_JE_SUIS_MARVIN_CHARS, 22};

const defilement *currentDefilement = &DEFILEMENT_I_LOVE_PSTJ;

bool ledDislayAnnimation = false;

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


    myMatrix = new MAX7219(PIN_CLK, PIN_CS, PIN_DIN);
    myMatrix->init();
    myMatrix->setBrightness(4);
    myMatrix->writeCharacter(CHAR_SMILE);

}

void onReceive(Commande &commande) {
    switch (commande.id) {
        case COMMANDE_BUTTON:
            sendCommande(TEST_COMMANDE_RESAVE, 0xCC0500 + commande.data);
            digitalWrite(13,LOW);
            if(commande.data == BUTTON_MATRIX) {
                sendCommande(TEST_COMMANDE_RESAVE, 0xCC0400 + commande.data);
                // Check if DEFILEMENT_I_LOVE_PSTJ is the current annimation
                if(ledDislayAnnimation && currentDefilement == &DEFILEMENT_I_LOVE_PSTJ){
                    ledDislayAnnimation = false;
                    myMatrix->writeCharacter(CHAR_SMILE);
                }else{
                    currentDefilement = &DEFILEMENT_I_LOVE_PSTJ;
                    ledDislayAnnimation = true;
                    matrixAvancement = 0;
                    matrixAvancementDecalage = 0;
                    nextAvancement = millis() + matrixDeley;
                }
            }else if(commande.data == BUTTON_MOTOR) {
                sendCommande(TEST_COMMANDE_RESAVE, 0xCC0300 + commande.data);
                if(legs->getCurrentAnnimation() == &LEG_ANNIM_WORLK){
                    sendCommande(TEST_COMMANDE_RESAVE, 0xAA);
                    legs->changeAnnimation(&LEG_ANNIM_WAIT, false);
                }else{
                    sendCommande(TEST_COMMANDE_RESAVE, 0xBB);
                    legs->changeAnnimation(&LEG_ANNIM_WORLK, true);
                }
            }else if(commande.data == BUTTON_MATRIX2) {
                digitalWrite(13,HIGH);
                // Check if DEFILEMENT_BONJOUR_JE_SUIS_MARVIN is the current annimation
                if(ledDislayAnnimation && currentDefilement == &DEFILEMENT_BONJOUR_JE_SUIS_MARVIN){
                    sendCommande(TEST_COMMANDE_RESAVE, 0xCC0100 + commande.data);
                    // 1) we stop the annimation syteme
                    ledDislayAnnimation = false;
                    // 2) we display the smile :)

                    myMatrix->writeCharacter(CHAR_SMILE);
                }else{
                    sendCommande(TEST_COMMANDE_RESAVE, 0xCC0200 + commande.data);
                    digitalWrite(13,HIGH);
                    // 1) we define the annimation to show
                    currentDefilement = &DEFILEMENT_BONJOUR_JE_SUIS_MARVIN;
                    // 2) we set the position of annimation to 0
                    matrixAvancement = 0;
                    matrixAvancementDecalage = 0;
                    // 3) we defined when the annimation will start (don't forgot it)
                    nextAvancement = millis() + matrixDeley;
                    // 4) start the annimation system
                    ledDislayAnnimation = true;
                }
            }else{
                sendCommande(TEST_COMMANDE_RESAVE, 0xCC0000 + commande.data);
            }
            break;
        default:
            break;
    }

    pinMode(13, OUTPUT);
    digitalWrite(13,LOW);
}

void loop() {

    checkReceive();

    legs->refresh();

    if (ledDislayAnnimation)matrixRefresh();

}
