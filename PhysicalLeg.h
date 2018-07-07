//
// Created by ferna on 09/06/2018.
//
#ifndef MARVIN_PHYSICAL_LEG_H
#define MARVIN_PHYSICAL_LEG_H

#include "LegState.h"
#include "Leg.h"
#include "Motor.h"
#include <Servo.h>


class PhysicalLeg : public Leg {
private:

protected:

    Motor *motorHip;
    Motor *motorKnee;
    Motor *motorAnkle;
    Motor *motorFoot;

public:

    PhysicalLeg(Side side, Motor *motorHip, Motor *motorKnee, Motor *motorAnkle, Motor *motorFoot);

    virtual ~PhysicalLeg();

    virtual void init();

    virtual int getDegHip() const;
    virtual void setDegHip(int degHip);

    virtual int getDegKnee() const;
    virtual void setDegKnee(int degKnee);

    virtual int getDegAnkle() const;
    virtual void setDegAnkle(int degAnkle);

    virtual int getDegFoot() const;
    virtual void setDegFoot(int degFoot);

};


#endif //MARVIN_PHYSICAL_LEG_H
