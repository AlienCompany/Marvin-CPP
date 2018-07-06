//
// Created by ferna on 09/06/2018.
//
#ifndef MARVIN_PHYSICAL_LEG_H
#define MARVIN_PHYSICAL_LEG_H

#include "LegState.h"
#include "Leg.h"
#include <Servo.h>


class PhysicalLeg : public Leg {
private:

protected:

    Servo *servoHip;
    Servo *servoKnee;
    Servo *servoAnkle;
    Servo *servoFoot;

    const int PIN_HIP;
    const int PIN_KNEE;
    const int PIN_ANKLE;
    const int PIN_FOOT;

public:

    PhysicalLeg(int PIN_HIP, int PIN_KNEE, int PIN_ANKLE, int PIN_FOOT, Side side);

    virtual ~PhysicalLeg();

    virtual LegState getLegState() const;

    virtual void init();

};


#endif //MARVIN_PHYSICAL_LEG_H
