//
// Created by hugues on 07/07/2018.
//

#include <Arduino.h>
#include "Com.h"


const uint8_t PIN_LED = 13;
const long COMMANDE_INTERVAL = 1000;

long nextSend = 1000;
long endLedTime = 0;

void onResave(Commande &c){
    switch(c.id){
        case TEST_COMMANDE_ALLUMER_LED:
            endLedTime = millis() + c.data;
            sendCommande(COMMANDE_RESAVE, c.data);
            break;
        default:
            break;
    }
}

void setup(){
    Serial.begin(9600);
    pinMode(PIN_LED, OUTPUT);
}

void loop(){
    checkResave();

    if(nextSend <= millis()){
        nextSend += COMMANDE_INTERVAL;
        sendCommande(TEST_COMMANDE_ALLUMER_LED, 750);
    }
    
    digitalWrite(PIN_LED, endLedTime > millis());
}