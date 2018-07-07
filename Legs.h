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


    Legs(Leg *legLeft, Leg *legRight) : legLeft(legLeft), legRight(legRight) {
        legControllerLeft = new LegController(legLeft, NONE);
        legControllerRight = new LegController(legRight, NONE);
    }

    void init(){
        legLeft->init();
        legRight->init();
    }

    void refresh(){
        legControllerRight->refrest();
        legControllerLeft->refrest();
        if(nextStepIndex >= 0){
            legStep step = currentAnnimation->steps[nextStepIndex];
            if((!step.waitSideLeft || legControllerLeft->isFix()) && (!step.waitSideRight || legControllerRight->isFix())){
                if(step.vitesseRight)legControllerRight->setState(step.stateRight, step.vitesseRight);
                if(step.vitesseLeft)legControllerLeft->setState(step.stateLeft, step.vitesseLeft);
                nextStepIndex ++;
                if(nextStepIndex >= currentAnnimation->nbStep) nextStepIndex = loopAnnimation ? 0 : -1;
            }
        }
    }

    void changeAnnimation(const legAnnim *newAnnimation, bool inloop){
        nextStepIndex = 0;
        currentAnnimation = newAnnimation;
        loopAnnimation = inloop;
    }

    Leg *getLegLeft() const {
        return legLeft;
    }

    Leg *getLegRight() const {
        return legRight;
    }

    const legAnnim *getCurrentAnnimation() const {
        return currentAnnimation;
    }

    bool isLoopAnnimation() const {
        return loopAnnimation;
    }

    int getNextStepIndex() const {
        return nextStepIndex;
    }

    virtual ~Legs() {
        delete legControllerRight;
        delete legControllerLeft;
    }

};


#endif //MARVIN_LEGS_H
