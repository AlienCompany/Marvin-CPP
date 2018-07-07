//
// Created by ferna on 09/06/2018.
//

#ifndef MARVIN_LEG_H
#define MARVIN_LEG_H


#include "LegState.h"
#include "Side.h"

class Leg {
private:
    const Side side;
public:
    Leg(Side side);
    virtual ~Leg();

    virtual int getDegHip() const =0;
    virtual void setDegHip(int degHip) =0;

    virtual int getDegKnee() const =0;
    virtual void setDegKnee(int degKnee) =0;

    virtual int getDegAnkle() const =0;
    virtual void setDegAnkle(int degAnkle) =0;

    virtual int getDegFoot() const =0;
    virtual void setDegFoot(int degFoot) =0;

    virtual void init();

    Side getSide() const;
};


#endif //MARVIN_LEG_H
