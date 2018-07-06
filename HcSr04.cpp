#include <Arduino.h>
#include "HcSr04.h"

HcSr04::HcSr04(uint8_t PIN_ECHO, uint8_t PIN_TRIGG) : PIN_ECHO(PIN_ECHO), PIN_TRIGG(PIN_TRIGG) {

}

HcSr04::~HcSr04() = default;

void HcSr04::init() {

    pinMode(PIN_TRIGG, OUTPUT);
    digitalWrite(PIN_TRIGG, LOW); // La broche TRIGGER doit être à LOW au repos
    pinMode(PIN_ECHO, INPUT);

}

const uint8_t HcSr04::getPIN_ECHO() const {
    return PIN_ECHO;
}

const uint8_t HcSr04::getPIN_TRIGG() const {
    return PIN_TRIGG;
}

float HcSr04::getLastDistance() const {
    return lastDistance;
}

float HcSr04::measureDistance() {

    /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
    digitalWrite(PIN_TRIGG, HIGH);
    delayMicroseconds(10);
    digitalWrite(PIN_TRIGG, LOW);

    /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
    long measure = pulseIn(PIN_ECHO, HIGH, MEASURE_TIMEOUT);

    /* 3. Calcul la distance à partir du temps mesuré */
    lastDistance = measure / 2.0 * SOUND_SPEED;

    return lastDistance;

}

