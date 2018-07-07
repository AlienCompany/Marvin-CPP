//
// Created by ferna on 09/06/2018.
//

#ifndef MARVIN_LEGSTATE_H
#define MARVIN_LEGSTATE_H

#include <stdint.h>
#include <USBAPI.h>
#include "Side.h"

enum LegState {
    NONE = 0,
    FLEXION = 1,
    EXTENSION = 2,
    TILT = 3
};

struct LegStateAngle{
    int degHip, degKnee, degAnkle, degFoot;
};

struct legStep{
    boolean waitSideLeft;
    boolean waitSideRight;
    float vitesseLeft; // set to 0 for ignor Step for this side
    float vitesseRight;
    LegState stateRight;
    LegState stateLeft;
};

struct legAnnim{
    const legStep* steps;
    const uint8_t nbStep;
};

const LegStateAngle LEG_STATES_MOTORS_DATA[4] = {
    {90, 90, 90, 90},      // NONE
    {-28, -13, 90, 90},      // FLEXION
    {30, 15, 90, 90},      // EXTENSION
    {90, 90, 90, -16}       // TILT
};

const legStep LEG_ANNIM_WAIT_STEPS[] = {
//     |wail L?|wait R?|  speed L |  speed R  | State L | State R |
        {true,  true,   1. / 500,   1. / 500,   NONE,       NONE     },
};

const legStep LEG_ANNIM_WORLK_STEPS[] = {
//     |wail L?|wait R?|  speed L |  speed R  | State L | State R |
        {true,  true,   1. / 500,   1. / 500,   NONE,       NONE     },
        {true,  true,   1. / 500,   0,          TILT,       NONE     },
        {true,  false,  0,          1. / 500,   TILT,       EXTENSION}
};

const legAnnim LEG_ANNIM_WORLK = {LEG_ANNIM_WORLK_STEPS, sizeof(LEG_ANNIM_WORLK_STEPS) / sizeof(legStep)};
const legAnnim LEG_ANNIM_WAIT = {LEG_ANNIM_WAIT_STEPS, sizeof(LEG_ANNIM_WAIT_STEPS) / sizeof(legStep)};

LegStateAngle legStateRevertAngler(LegStateAngle legState);



#endif //MARVIN_LEGSTATE_H
