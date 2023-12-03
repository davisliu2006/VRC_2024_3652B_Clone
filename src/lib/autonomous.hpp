#pragma once

#include "../globals.hpp"
#include "sensing.hpp"
#include "subsystems.hpp"

namespace auton {
    // DEFINITIONS

    const double ADVNC_MINDIFF = 1; // changes advance_dist tolerence (minimum distance diff (inches))
    const double ADVNC_MAXDIFF = 3; // changes advance_dist scaling upper bound distance (inches)
    const double TURN_MINDIFF = 5; // changes turn tolerence (minimum angle diff)
    const double TURN_MAXDIFF = 100; // changes turn scaling upper bound angle

    // SIMPLE MOVEMENT

    // simple move
    inline void advance(int vel) {
        flmotor.move_velocity(vel);
        frmotor.move_velocity(vel);
        rlmotor.move_velocity(vel);
        rrmotor.move_velocity(vel);
    }
    inline void move(double lvel, double rvel) {
        flmotor.move_velocity(lvel);
        frmotor.move_velocity(rvel);
        rlmotor.move_velocity(lvel);
        rrmotor.move_velocity(rvel);
    }

    // simple turn
    inline void turn(int rotvel) {
        flmotor.move_velocity(rotvel);
        frmotor.move_velocity(-rotvel);
        rlmotor.move_velocity(rotvel);
        rrmotor.move_velocity(-rotvel);
    }

    // stop
    inline void stop() {
        flmotor.move_velocity(0);
        frmotor.move_velocity(0);
        rlmotor.move_velocity(0);
        rrmotor.move_velocity(0);
    }

    // wait with background processing
    inline void wait(double dt) {
        sens::update();
        while (dt > 0) {
            sens::update();
            dt -= sens::dt;
        }
    }
    inline void wait_until(function<bool()> func) {
        sens::update();
        while (!func()) {
            sens::update();
        }
    }

    // MEASURED MOVEMENT

    // move distance
    inline void advance_time(double vel, double dt) {
        advance(vel);
        wait(dt);
        stop();
    }
    inline void advance_straight(double vel, double dt, double corr = 1) {
        sens::update();
        double rot = sens::rot;
        while (dt > 0) {
            sens::update();
            double rotdiff = angl_180(rot-sens::rot)/TURN_MAXDIFF;
            flmotor.move_velocity(vel+rotdiff*corr);
            frmotor.move_velocity(vel-rotdiff*corr);
            rlmotor.move_velocity(vel+rotdiff*corr);
            rrmotor.move_velocity(vel-rotdiff*corr);
            dt -= sens::dt;
        }
        stop();
    }
    inline void advance_dist(double dist, double mult = 1) {
        double pos0 = drv::get_avg_ldist();
        double pos1 = pos0;
        double dpos = pos1-pos0;
        while (abs(dist-dpos) > ADVNC_MINDIFF) {
            pos1 = drv::get_avg_ldist();
            dpos = pos1-pos0;
            double distdiff = min(1.0, dpos/ADVNC_MAXDIFF);
            advance(distdiff*WHEEL_RPM*mult);
        }
        stop();
    }

    // turn angle
    inline void turn_to(double heading, double mult = 1) {
        sens::update();
        heading = angl_360(heading);
        while (abs(sens::rot-heading) > TURN_MINDIFF) {
            sens::update();
            double rotdiff = angl_180(heading-sens::rot)/TURN_MAXDIFF;
            rotdiff = min(1.0, rotdiff);
            turn(rotdiff*WHEEL_RPM*mult);
        }
        stop();
    }
    inline void turn_angl(double angle) {
        sens::update();
        turn_to(angl_360(sens::rot+angle));
    }

    // INITIALIZE
    inline bool did_init = false;
    inline bool need_sens_reset = false;
    /*
    Runs at the beginning of autonomous before any route.
    For any initializations that cannot occur during initialize(),
    such as calibrating moving parts.
    */
    inline void init() {
        did_init = true;
        // sensing
        if (need_sens_reset && pros::competition::is_autonomous()) {
            sens::reset();
        }
        need_sens_reset = false;
        // catapult
        catamotor.move(MTR_MAX*0.1);
        wait(0.3);
        catamotor.tare_position();
        catamotor.move_absolute(cata::SLIP_LOAD, CATA_RPM);
        // intake
    }
}