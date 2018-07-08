//
// Created by hugues on 07/07/2018.
//

#include "LegController.h"

Leg *LegController::getLeg() const {
    return leg;
}

LegState LegController::getState() const {
    return state;
}

double LegController::getAvancement() const {
    return avancement;
}

double LegController::getVitesse() const {
    return vitesse;
}

LegController::LegController(Leg *leg, LegState state) : leg(leg), state(state) {

}

LegController::~LegController() {

}

void LegController::setState(LegState newState, float vitesse_) {
    vitesse = vitesse_;
    state = newState;
    startMove = millis();
    avancement = 0;
}

void LegController::refrest() {
    if(isFix())return;

    double oldAvancement = avancement;
    avancement = min((millis() - startMove) * vitesse, 1);
    double ratioNew = (avancement - oldAvancement)/(1 - oldAvancement);
    double ratioOld = 1-ratioNew;

    LegStateAngle targetAngles = LEG_STATES_MOTORS_DATA[state];

    if(leg->getSide() == RIGHT){
        targetAngles = legStateRevertAngler(targetAngles);
    }

    leg->setDegHip((int)round(leg->getDegHip()*ratioOld + targetAngles.degHip*ratioNew));
    leg->setDegKnee((int)round(leg->getDegKnee()*ratioOld + targetAngles.degKnee*ratioNew));
    leg->setDegAnkle((int)round(leg->getDegAnkle()*ratioOld + targetAngles.degAnkle*ratioNew));
    leg->setDegFoot((int)round(leg->getDegFoot()*ratioOld + targetAngles.degFoot*ratioNew));

}

bool LegController::isFix() {
    return avancement >= 1;
}
