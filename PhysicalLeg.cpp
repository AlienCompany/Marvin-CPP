//
// Created by ferna on 09/06/2018.
//

#include "PhysicalLeg.h"

PhysicalLeg::PhysicalLeg(int PIN_HIP, int PIN_KNEE, int PIN_ANKLE, int PIN_FOOT, Side side)
        : Leg(side), PIN_HIP(PIN_HIP), PIN_KNEE(PIN_KNEE), PIN_ANKLE(PIN_ANKLE), PIN_FOOT(PIN_FOOT) {

    servoHip = new Servo();
    servoKnee = new Servo();
    servoAnkle = new Servo();
    servoFoot = new Servo();
}

PhysicalLeg::~PhysicalLeg() {
    delete servoHip;
    delete servoKnee;
    delete servoAnkle;
    delete servoFoot;
}

LegState PhysicalLeg::getLegState() const {
}

void PhysicalLeg::init() {
    Leg::init();
    servoHip->attach(PIN_HIP);
    servoKnee->attach(PIN_KNEE);
    servoAnkle->attach(PIN_ANKLE);
    servoFoot->attach(PIN_FOOT);
}


