//
// Created by ferna on 09/06/2018.
//

#ifndef MARVIN_LEGSTATE_H
#define MARVIN_LEGSTATE_H

enum LegState {
    NONE = 0,
    FLEXION = 1,
    EXTENSION = 2,
    TILT = 3
};

const int LEG_STATES_MOTORS_DATA[4][4] = {
    {90, 90, 90, 90},      // NONE
    {-28, -13, 90, 90},      // FLEXION
    {30, 15, 90, 90},      // EXTENSION
    {90, 90, 90, -16}       // TILT
};
#endif //MARVIN_LEGSTATE_H
