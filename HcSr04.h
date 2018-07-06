//
// Created by ferna on 05/07/2018.
//

#ifndef MARVINTEST_HCSR04_H
#define MARVINTEST_HCSR04_H


class HcSr04 {

private:

    const uint8_t PIN_ECHO;
    const uint8_t PIN_TRIGG;

    float lastDistance;

    const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s
    const float SOUND_SPEED = 340.0 / 1000;



public:

    HcSr04(uint8_t PIN_ECHO, uint8_t PIN_TRIGG);

    virtual ~HcSr04();

    void init();

    const uint8_t getPIN_ECHO() const;

    const uint8_t getPIN_TRIGG() const;

    float getLastDistance() const;

    float measureDistance();


};


#endif //MARVINTEST_HCSR04_H
