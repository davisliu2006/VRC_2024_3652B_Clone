#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    inline void skills() {
        sens::ROT_OFFSET = 34;

        // match loads
        for (int i = 1; i <= 40; i++) { // shoot
            cata::release();
            auton::wait_until([]() {return !cata::is_moving();});
            cata::load();
            auton::wait_until([]() {return !cata::is_moving();});
        }
        auton::advance_dist(-2);

        // push
        auton::turn_to(175); // go to
        auton::advance_dist(TILE*3);
        auton::turn_to(-90);
        intake.move(-MTR_MAX); // outtake
        auton::advance_dist(TILE); // go to
        wing.set_value(true); // wing
        auton::wait(0.5);
        auton::advance_dist(TILE);
        auton::turn_to(180);
        auton::turn_to(135);
        wing.set_value(false);
        auton::turn_to(0, 0, 0.5, 1);
        auton::advance_time(-WHEEL_RPM, 0.3);
        auton::advance_dist(TILE*0.3, 0.7, 0);
        auton::turn_to(-90);
        auton::advance_dist(TILE*0.8);
        auton::turn_to(0, 0, 0.5, 1);
        auton::advance_time(-WHEEL_RPM, 0.3);
        intake.move(0);

        // elevation
        /*auton::turn_to(90); // go to
        auton::advance_dist(TILE*2);
        auton::turn_to(0);
        cata::release();
        auton::advance_dist(TILE*1.5);*/
    }
}