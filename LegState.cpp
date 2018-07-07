//
// Created by hugues on 07/07/2018.
//

#include "LegState.h"

LegStateAngle legStateRevertAngler(LegStateAngle legState) {
    return {
            180 - legState.degHip,
            180 - legState.degKnee,
            180 - legState.degAnkle,
            180 - legState.degFoot
    };
}
