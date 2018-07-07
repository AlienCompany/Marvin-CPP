//
// Created by ferna on 09/06/2018.
//

#include "PhysicalLeg.h"


PhysicalLeg::~PhysicalLeg() {
    delete motorHip;
    delete motorKnee;
    delete motorAnkle;
    delete motorFoot;
}

LegState PhysicalLeg::getLegState() const {
}

void PhysicalLeg::init() {
    Leg::init();
    motorHip->init();
    motorKnee->init();
    motorAnkle->init();
    motorFoot->init();
}

PhysicalLeg::PhysicalLeg(Side side, Motor *motorHip, Motor *motorKnee, Motor *motorAnkle, Motor *motorFoot)
        : Leg(side), motorHip(motorHip), motorKnee(motorKnee), motorAnkle(motorAnkle), motorFoot(motorFoot) {}

int PhysicalLeg::getDegHip() const {
    return motorHip->getAngle();
}

void PhysicalLeg::setDegHip(int degHip) {
    motorHip->setAngle(degHip);
}

int PhysicalLeg::getDegKnee() const {
    return motorKnee->getAngle();
}

void PhysicalLeg::setDegKnee(int degKnee) {
    motorKnee->setAngle(degKnee);
}

int PhysicalLeg::getDegAnkle() const {
    return motorAnkle->getAngle();
}

void PhysicalLeg::setDegAnkle(int degAnkle) {
    motorAnkle->setAngle(degAnkle);
}

int PhysicalLeg::getDegFoot() const {
    return motorFoot->getAngle();
}

void PhysicalLeg::setDegFoot(int degFoot) {
    motorFoot->setAngle(degFoot);
}


