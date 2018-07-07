//
// Created by ferna on 09/06/2018.
//

#include "Legs.h"

Legs::Legs(Leg *legLeft, Leg *legRight) : legLeft(legLeft), legRight(legRight) {
    legControllerLeft = new LegController(legLeft, NONE);
    legControllerRight = new LegController(legRight, NONE);
}

void Legs::init() {
    legLeft->init();
    legRight->init();
}

void Legs::refresh() {
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

void Legs::changeAnnimation(const legAnnim *newAnnimation, bool inloop) {
    nextStepIndex = 0;
    currentAnnimation = newAnnimation;
    loopAnnimation = inloop;
}

Leg *Legs::getLegLeft() const {
    return legLeft;
}

Leg *Legs::getLegRight() const {
    return legRight;
}

const legAnnim *Legs::getCurrentAnnimation() const {
    return currentAnnimation;
}

bool Legs::isLoopAnnimation() const {
    return loopAnnimation;
}

int Legs::getNextStepIndex() const {
    return nextStepIndex;
}

Legs::~Legs() {
    delete legControllerRight;
    delete legControllerLeft;
}
