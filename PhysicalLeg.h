//
// Created by ferna on 09/06/2018.
//
#ifndef MARVIN_LEG_H
#define MARVIN_LEG_H

#include "LegState.h"

class PhysicalLeg {
private:

protected:
    int PIN_HIP;
    int PIN_KNEE;
    int PIN_ANKLE;
    int PIN_FOOT;


    float degHip;
    float degKnee;
    float degAnkle;
    float degFoot;
public:

    PhysicalLeg();
    virtual ~PhysicalLeg();

};


#endif //MARVIN_LEG_H
