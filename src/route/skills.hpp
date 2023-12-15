#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    inline void skills() {
        // match loads
        auton::turn_to(deg(atan(2/3))); // aim
        for (int i = 1; i <= 40; i++) { // shoot
            cata::release();
            auton::wait_until([]() {return !cata::is_moving();});
            cata::load();
            auton::wait_until([]() {return !cata::is_moving();});
        }

        // push
        auton::turn_to(180); // go to
        auton::advance_dist(TILE*3);
        auton::turn_to(-90);
        intake.move(-MTR_MAX); // outtake
        auton::advance_dist(TILE); // go to
        wing.set_value(true); // wing
        auton::wait(0.5);
        auton::advance_dist(TILE);
        auton::turn_to(180);
        auton::advance_dist(TILE);
        wing.set_value(false);
        intake.move(0);

        // elevation
        auton::turn_to(90); // go to
        auton::advance_dist(TILE*2);
        auton::turn_to(0);
        cata::release();
        auton::advance_dist(TILE*1.5);
    }
}