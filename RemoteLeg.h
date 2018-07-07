//
// Created by ferna on 09/06/2018.
//

#ifndef MARVIN_REMOTELEG_H
#define MARVIN_REMOTELEG_H

#include "Leg.h"
#include "Com.h"

class RemoteLeg: public Leg {
private:

protected:
    int degHip, degKnee, degAnkle, degFoot;
public:
    RemoteLeg(Side side);
    virtual ~RemoteLeg();

    virtual LegState getLegState() const ;

    virtual int getDegHip() const{
        return degHip;
    }
    virtual void setDegHip(int degHip_){
        degHip = degHip_;
        sendCommande(COMMANDE_LEG, MOTOR_HIP, (uint16_t)degHip_);
    }

    virtual int getDegKnee() const{
        return degKnee;
    }
    virtual void setDegKnee(int degKnee_){
        degKnee = degKnee_;
        sendCommande(COMMANDE_LEG, MOTOR_KNEE, (uint16_t)degKnee_);

    }

    virtual int getDegAnkle() const{
        return degAnkle;
    }
    virtual void degAnkle_(int degAnkle_){
        degAnkle = degAnkle_;
        sendCommande(COMMANDE_LEG, MOTOR_ANKLE, (uint16_t)degAnkle_);

    }

    virtual int getDegFoot() const{
        return  degFoot;
    }
    virtual void setDegFoot(int degFoot_){
        degFoot = degFoot_;
        sendCommande(COMMANDE_LEG, MOTOR_FOOT, (uint16_t)degFoot_);
    }
};


#endif //MARVIN_REMOTELEG_H
