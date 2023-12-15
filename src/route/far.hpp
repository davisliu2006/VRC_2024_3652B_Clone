#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    inline void far_1() {
        // score triball
        auton::advance_dist(TILE*2); // go to
        auton::turn_to(-90);
        intake.move(-MTR_MAX); // outtake
        auton::wait(0.5);
        intake.move(0);

        // load from match loading zone
        auton::turn_to(0); // go to
        auton::advance_dist(-TILE);
        auton::turn_to(45);
        auton::advance_dist(-TILE*M_SQRT1_2);
        wing.set_value(true); // wing
        auton::wait(0.5);
        auton::turn_to(135);
        auton::turn_to(-135);
        wing.set_value(false);

        // touch elevation bar
        auton::turn_to(135*M_SQRT1_2); // reposition
        auton::advance_dist(TILE);
        auton::turn_to(90); // go to
        cata::release();
        auton::advance_dist(TILE*1.5);
    }
}