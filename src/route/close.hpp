#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    inline void close_1() {
        // score triball
        auton::advance_dist(TILE*2.5); // go to
        auton::turn_to(90);
        intake.move(-MTR_MAX); // outtake
        auton::wait(0.5);
        intake.move(0);

        // load from match loading zone
        auton::turn_to(0); // go to
        auton::advance_dist(-TILE*2.5);
        wing.set_value(true); // wing
        auton::wait(0.5);
        auton::turn_to(90);
        wing.set_value(false);

        // touch elevation bar
        auton::turn_to(-90); // go to
        cata::release();
        auton::advance_dist(TILE*1.5);
    }
}