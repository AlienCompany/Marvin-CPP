//
// Created by hugues on 07/07/2018.
//

#ifndef MARVIN_LEGCONTROLLER_H
#define MARVIN_LEGCONTROLLER_H


#include <Arduino.h>
#include "LegState.h"
#include "Leg.h"

class LegController {
private:
    Leg* leg;
    LegState state;
    float avancement = 0;
    float vitesse = 0.0005; // avancement/ms exemple 0.001 => 1000 ms pour lattindre la position final
    float startMove = millis();
public:

    LegController(Leg *leg, LegState state);

    void setState(LegState newState, float vitesse_);
    void refrest();
    bool isFix();

    Leg *getLeg() const;

    LegState getState() const;

    float getAvancement() const;

    float getVitesse() const;

    virtual ~LegController();

};


#endif //MARVIN_LEGCONTROLLER_H
