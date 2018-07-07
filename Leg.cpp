//
// Created by ferna on 09/06/2018.
//

#include "Leg.h"

Leg::Leg(Side side): side(side){

}

Leg::~Leg() {

}

void Leg::init() {}

Side Leg::getSide() const {
    return side;
}



