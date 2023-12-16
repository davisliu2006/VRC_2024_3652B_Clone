#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    inline void close_1() {
        // score triball
        auton::advance_dist(TILE*2-2); // go to
        auton::turn_to(90);
        intake.move(-MTR_MAX); // outtake
        auton::wait(0.5);
        intake.move(0);
        auton::turn_to(-90); // back in
        auton::advance_time(-WHEEL_RPM, 0.3);
        auton::advance_dist(TILE*0.3);

        // load from match loading zone
        auton::turn_to(0); // go to
        auton::advance_dist(-TILE);
        auton::turn_to(-4);
        auton::advance_dist(-TILE*M_SQRT1_2);
        wing.set_value(true); // wing
        auton::wait(0.5);
        auton::turn_to(135, 1);
        wing.set_value(false);

        // touch elevation bar
        auton::turn_to(-135); // reposition
        auton::advance_dist(TILE*M_SQRT1_2);
        auton::turn_to(-90); // go to
        cata::release();
        auton::advance_dist(TILE*1.5);
    }
}
