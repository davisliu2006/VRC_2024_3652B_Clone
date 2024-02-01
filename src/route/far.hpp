#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    // ROUTES

    inline void far_1() {
        // score triball
        auton::advance_dist(TILE*2.25); // go to
        auton::turn_to(-90);
        intake.move(-MTR_MAX); // outtake
        auton::wait(0.5);
        intake.move(0);
        auton::turn_to(90); // back in
        auton::advance_time(-WHEEL_RPM, 0.4);
        auton::advance_dist(TILE*0.3);

        // load from match loading zone
        auton::turn_to(15); // go to
        auton::advance_dist(-TILE*1.25);
        auton::turn_to(55);
        auton::advance_dist(-TILE*M_SQRT1_2-2);
        wing.set_value(true); // wing
        auton::wait(0.5);
        auton::turn_to(-135, 1);
        wing.set_value(false);

        // touch elevation bar
        auton::turn_to(135); // reposition
        auton::advance_dist(TILE*M_SQRT1_2-4);
        auton::turn_to(90); // go to
        cata::release();
        auton::advance_dist(TILE*1.5);
    }
}
