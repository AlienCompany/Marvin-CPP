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
    FLEXION2 = 2,
    EXTENSION = 3,
    TILT = 4
};

struct LegStateAngle {
    int degHip, degKnee, degAnkle, degFoot;
};

struct legStep {
    boolean waitSideLeft;
    boolean waitSideRight;
    double vitesseLeft; // set to 0 for ignor Step for this side
    double vitesseRight;
    LegState stateRight;
    LegState stateLeft;
};

struct legAnnim {
    const legStep *steps;
    const uint8_t nbStep;
};

const LegStateAngle LEG_STATES_MOTORS_DATA[] = {
        {90,       90,    90, 90},      // NONE
        {90-45, 90, 90, 90},      // FLEXION
        //{90-45,    90-15, 90, 90},      // FLEXION2
        {90+15, 90+15, 90, 90},      // EXTENSION
        {90,  90,      90, 90-30}    // TILT
};

const legStep LEG_ANNIM_WAIT_STEPS[] = {
//     |wail L?|wait R?|  speed L |  speed R  | State L | State R |
        {true, true, 1. / 500, 1. / 500, NONE, NONE},
};

const legStep LEG_ANNIM_WORLK_STEPS[] = {
//     |wait L?|wait R?|  speed L |  speed R  | State L | State R |
        {true, true, 1. / 5000, 1. / 5000, NONE,      NONE},
        {true, true, 1. / 5000, 0,         TILT,      NONE},
        {true, true, 0,         1. / 5000, TILT,      FLEXION},
       // {true, true, 0,         1. / 5000, TILT,      FLEXION2},
        //{true, true, 1. / 5000, 0,         EXTENSION, FLEXION2},
        {true, true, 1. / 5000, 1. / 8000, NONE,      TILT},
        {true, true, 1. / 5000, 0,         FLEXION,   TILT},
      //  {true, true, 1. / 5000, 0,         FLEXION2,  TILT},
       // {true, true, 0,         1. / 5000, FLEXION2,  EXTENSION},
        {true, true, 1. / 8000, 1. / 5000, TILT,      NONE},
};

const legAnnim LEG_ANNIM_WORLK = {LEG_ANNIM_WORLK_STEPS, sizeof(LEG_ANNIM_WORLK_STEPS) / sizeof(legStep)};
const legAnnim LEG_ANNIM_WAIT = {LEG_ANNIM_WAIT_STEPS, sizeof(LEG_ANNIM_WAIT_STEPS) / sizeof(legStep)};

LegStateAngle legStateRevertAngler(LegStateAngle legState);


#endif //MARVIN_LEGSTATE_H
