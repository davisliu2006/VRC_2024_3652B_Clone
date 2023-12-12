#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    // TEST

    inline void test_4() {
        auton::advance_dist(TILE);
        // auton::turn_to(90, 0.5);
        auton::advance_dist(-TILE);
    }

    // ROUTES

    inline void close_1() {
        // score triball
        auton::advance_dist(TILE*2.5); // go to
        auton::turn_to(90);
        intake.move(-MTR_MAX); // outtake
        auton::wait(0.5);
        intake.move(0);

        // load from match loading zone
        auton::turn_to(180); // go to
        auton::advance_dist(TILE*2.5);
        auton::turn_to(90);
        intake.move(MTR_MAX); // intake
        auton::wait(0.5);
        auton::advance_dist(TILE*0.3);
        auton::turn_to(135);
        auton::wait(1);
        auton::turn_to(90);
        auton::advance_dist(-TILE*0.3);
        intake.move(0);

        // touch elevation bar
        auton::turn_to(-90);
        auton::advance_dist(TILE);
    }

    inline void far_1() {
        // score triball
        auton::advance_dist(TILE*2); // go to
        auton::turn_to(-90);
        intake.move(-MTR_MAX); // outtake
        auton::wait(0.5);
        intake.move(0);

        // load from match loading zone
        auton::turn_to(180); // go to
        auton::advance_dist(TILE*2);
        auton::turn_to(-90);
        intake.move(MTR_MAX); // intake
        auton::advance_dist(TILE*0.5);
        auton::wait(0.5);
        auton::advance_dist(-TILE*0.5);
        intake.move(0);
        auton::turn_to(180);

        // touch elevation bar
        auton::turn_to(90);
        auton::advance_dist(TILE);
    }

    inline void test_1() {
        // TODO : define launch function
        double AB = 35.433;
        double BC = 52.820;
        double CD = 59.055;
        double PICKUP = 6.9;
        // Init auton.
        // Start at node $A$ at a heading of $60$ degrees.
        // Throw starting triball.
        // ! launch();
        // Turn $60$ degrees left.
        auton::turn_angl(-60);
        // Go forward the distance of $AB$
        auton::advance_dist(AB);
        // Turn $30$ degrees left.
        auton::turn_angl(-30);
        // Pick up triball.
        auton::advance_dist(PICKUP);
        auton::advance_dist(-PICKUP);
        // Turn $90$ degrees right.
        auton::turn_angl(90);
        // Throw the triball.
        // ! launch();
        // Turn $90$ degrees right.
        auton::turn_angl(90);
        //  Go forward the distance of $BC$
        auton::advance_dist(BC);
        //  Pick up triball.
        auton::advance_dist(PICKUP);
        auton::advance_dist(-PICKUP);
        //  Turn $300$ degrees right.
        auton::turn_angl(-60);
        //  Go forward the distance of $CD$
        auton::advance_dist(CD);
        //  Touch the bar.
        //  End auton.
    }

    // SKILLS

    inline void skills() {
        auton::turn_to(0);
        if (cata::START_STATE) {cata::release();}
        for (int i = 1; i <= 39; i++) {
            auton::wait(0.5);
            cata::load();
            auton::wait(0.5);
            cata::release();
        }
        auton::advance_dist(1);
    }
}