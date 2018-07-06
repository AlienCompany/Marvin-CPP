//
// Created by ferna on 09/06/2018.
//

#include "Leg.h"

Leg::Leg(Side side): side(side){

}

Leg::~Leg() {

}

float Leg::getDegHip() const {
    return degHip;
}

void Leg::setDegHip(float degHip) {
    Leg::degHip = degHip;
}

float Leg::getDegKnee() const {
    return degKnee;
}

void Leg::setDegKnee(float degKnee) {
    Leg::degKnee = degKnee;
}

float Leg::getDegAnkle() const {
    return degAnkle;
}

void Leg::setDegAnkle(float degAnkle) {
    Leg::degAnkle = degAnkle;
}

float Leg::getDegFoot() const {
    return degFoot;
}

void Leg::setDegFoot(float degFoot) {
    Leg::degFoot = degFoot;
}

void Leg::init() {}

Side Leg::getSide() const {
    return side;
}



