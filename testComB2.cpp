//
// Created by hugues on 07/07/2018.
//


#include <Arduino.h>
#include "Com.h"


const uint8_t PIN_LED = 13;
const long COMMANDE_INTERVAL = 200;

long nextSend = 1000;
long endLedTime = 0;

void onResave(Commande &c){
    switch(c.id){
        case COMMANDE_ALLUMER_LED:
            endLedTime = millis() + c.data;
            break;
    }
}

void setup(){
    pinMode(PIN_LED, OUTPUT);
}

void loop(){
    if(nextSend >= millis()){
        nextSend += COMMANDE_INTERVAL;
        sendCommande(COMMANDE_ALLUMER_LED, 100);
    }

    digitalWrite(PIN_LED, endLedTime < millis());
}