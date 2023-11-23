#pragma once

#include "../globals.hpp"

// catapult
namespace cata {
    const double SLIP_GEARING = double(84)/36; // mechanical advantage
    const double SCND_GEARING = 1; // mechanical advantage, secondary gearing
    const double ARM_LOAD = 90;
    const double ARM_TURN = 360;
    const double SLIP_LOAD = ARM_LOAD*SLIP_GEARING;
    const double SLIP_TURN = ARM_TURN;
    const double SLIP_UNLOAD = (SLIP_TURN-SLIP_LOAD)/2;
    const double MTR_LOAD = SLIP_LOAD*SCND_GEARING;
    const double MTR_TURN = SLIP_TURN*SCND_GEARING;
    const double MTR_UNLOAD = SLIP_UNLOAD*SCND_GEARING;
    const bool START_STATE = false;
    
    inline void init() {
        if (START_STATE == false) {
            catamotor.tare_position();
            catamotor.move_absolute(SLIP_LOAD, CATA_RPM);
        } else {
            //
        }
    }

    inline double mtr_angle() {return catamotor.get_position();}
    inline double slip_angle() {return mtr_angle()/SCND_GEARING;}
    // get state, loaded = true, unloaded = false
    inline bool get_state() {
        double rot = catamotor.get_position();
        double load_diff = angl_180(slip_angle()-SLIP_LOAD);
        double unload_diff = angl_180(slip_angle()-SLIP_LOAD-SLIP_UNLOAD);
        return abs(load_diff) <= abs(unload_diff);
    }
    // set state, loaded = true, unloaded = false
    static void set_state(bool val) {
        long nturns;
        if (val && !get_state()) { // load
            nturns = round((mtr_angle()-MTR_LOAD-MTR_UNLOAD)/MTR_TURN);
            catamotor.move_absolute((nturns+1)*MTR_TURN + MTR_LOAD, CATA_RPM);
        } else if (!val && get_state()) { // unload
            nturns = round((mtr_angle()-MTR_LOAD)/MTR_TURN);
            catamotor.move_absolute(nturns*MTR_TURN + MTR_LOAD + MTR_UNLOAD, CATA_RPM);
        }
    }
};

// claw
struct claw {

};

// drivetrain
namespace drv {
    
}