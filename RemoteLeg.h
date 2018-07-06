//
// Created by ferna on 09/06/2018.
//

#ifndef MARVIN_REMOTELEG_H
#define MARVIN_REMOTELEG_H

#include "Leg.h"

class RemoteLeg: public Leg {
private:

protected:

public:
    RemoteLeg(Side side);
    virtual ~RemoteLeg();

    virtual LegState getLegState() const ;
};


#endif //MARVIN_REMOTELEG_H
