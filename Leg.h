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
protected:
    float degHip;
    float degKnee;
    float degAnkle;
    float degFoot;
public:
    Leg(Side side);
    virtual ~Leg();

    float getDegHip() const ;
    void setDegHip(float degHip);

    float getDegKnee() const;
    void setDegKnee(float degKnee);

    float getDegAnkle() const;
    void setDegAnkle(float degAnkle);

    float getDegFoot() const;
    void setDegFoot(float degFoot);

    virtual LegState getLegState() const = 0 ;

    virtual void init();

    Side getSide() const;
};


#endif //MARVIN_LEG_H
