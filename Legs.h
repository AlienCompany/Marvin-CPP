//
// Created by ferna on 09/06/2018.
//

#ifndef MARVIN_LEGS_H
#define MARVIN_LEGS_H

#include "PhysicalLeg.h"
#include "LegController.h"

class Legs {
private:
    Leg* legLeft;
    Leg* legRight;

    const legAnnim *currentAnnimation = &LEG_ANNIM_WAIT;
    bool loopAnnimation = false;
    int nextStepIndex = 0;

    LegController* legControllerLeft;
    LegController* legControllerRight;

public:


    Legs(Leg *legLeft, Leg *legRight);

    void init();

    void refresh();

    void changeAnnimation(const legAnnim *newAnnimation, bool inloop);

    Leg *getLegLeft() const;

    Leg *getLegRight() const;

    const legAnnim *getCurrentAnnimation() const;

    bool isLoopAnnimation() const;

    int getNextStepIndex() const;

    virtual ~Legs();

};


#endif //MARVIN_LEGS_H
