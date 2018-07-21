//
// Created by ferna on 05/07/2018.
//

#ifndef MARVINTEST_HCSR04_H
#define MARVINTEST_HCSR04_H


class HcSr04 {

private:

    const uint8_t PIN_ECHO;
    const uint8_t PIN_TRIGG;

     int lastDistance;

    const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s
    const float SOUND_SPEED = 340.0 / 1000; // en mm/microSec



public:
    HcSr04(uint8_t PIN_ECHO, uint8_t PIN_TRIGG);

    virtual ~HcSr04();

    void init();

    const uint8_t getPIN_ECHO() const;

    const uint8_t getPIN_TRIGG() const;

    /**
     * ca permet de générer un doc du programe et normalement tu peut plus facilement comprendre comment fonctionne un fonction quand tu veux l'utiliser
     * @return la derniére valeur mesurer pas measureDistance()
     */
    int getLastDistance() const;

    /**
     *
     * @return retourn la valeur mesurer en metre en jsp car ultra son mesure en mm
     */
    int measureDistance();


};


#endif //MARVINTEST_HCSR04_H
