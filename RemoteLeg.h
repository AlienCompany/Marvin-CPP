//
// Created by ferna on 09/06/2018.
//

#ifndef MARVIN_REMOTELEG_H
#define MARVIN_REMOTELEG_H

#include "Leg.h"

class RemoteLeg: public Leg {
private:

protected:
    int degHip, degKnee, degAnkle, degFoot;
public:
    RemoteLeg(Side side);
    virtual ~RemoteLeg();

    virtual LegState getLegState() const ;

    virtual int getDegHip() const{}
    virtual void setDegHip(int degHip);

    virtual int getDegKnee() const;
    virtual void setDegKnee(int degKnee);

    virtual int getDegAnkle() const;
    virtual void setDegAnkle(int degAnkle);

    virtual int getDegFoot() const;
    virtual void setDegFoot(int degFoot);
};


#endif //MARVIN_REMOTELEG_H
