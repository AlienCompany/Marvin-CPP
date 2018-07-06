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
    {0, 0, 0, 0},   // NONE
    {0, 0, 0, 0},      // FLEXION
    {0, 0, 0, 0},      // EXTENSION
    {0, 0, 0, 0}       // TILT
};
#endif //MARVIN_LEGSTATE_H
