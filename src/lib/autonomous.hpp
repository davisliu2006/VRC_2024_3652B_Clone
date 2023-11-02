#pragma once

#include "../globals.hpp"
#include "sensing.hpp"

namespace auton {
    // initialize
    inline bool did_init = false;
    inline bool need_sensreset = false;
    /*
    Runs at the beginning of autonomous before any route.
    For any initializations that cannot occur during initialize().
    */
    inline void init() {
        did_init = true;
        // sensing
        if (need_sensreset && pros::competition::is_autonomous()) {
            sens::reset();
        }
        need_sensreset = false;
    }
}