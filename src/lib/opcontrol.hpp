#pragma once

#include "../globals.hpp"
#include "sensing.hpp"
#include "subsystems.hpp"
#include "../display/main.hpp"

// maps joystick position to drive speed
inline double joymap(int x){
    double temp = double(x)/MTR_MAX;
    return temp*sqrt(abs(temp));
}

// start opcontrol
inline void opcontrol_start() {
    // drivetrain
    bool drv_rev = 1; // reverse drivetrain: set to -1

    while (true) {
        // sensing
        sens::update();

        // display
        dashboard::update();

        // drivetrain
        double x = joymap(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X))*drv_rev;
        double y = joymap(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y))*drv_rev;
        double rot = joymap(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
        flmotor.move_velocity((y+rot)*WHEEL_RPM);
        frmotor.move_velocity((y-rot)*WHEEL_RPM);
        rlmotor.move_velocity((y+rot)*WHEEL_RPM);
        rrmotor.move_velocity((y-rot)*WHEEL_RPM);

        // intake
        #if INTAKE_TYPE == TYPE_PNEU
        #elif INTAKE_TYPE == TYPE_MTR
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
            intake.move(MTR_MAX);
        } else if (pros::E_CONTROLLER_DIGITAL_L1) {
            intake.move(-MTR_MAX);
        } else {
            intake.move(0);
        }
        #endif

        // catapult
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
            cata::load();
        } else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
            cata::release();
        }
    }
}