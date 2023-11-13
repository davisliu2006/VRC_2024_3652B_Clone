#pragma once

#include "../globals.hpp"

// catapult
struct cata {
    static constexpr double GEARING = double(84)/36 * 84/36;
    static constexpr double LOAD_ANGL = 90;
    static constexpr double ADJ_ANGL = LOAD_ANGL*GEARING;

    private:
    static bool state;
    
    public:
    static bool get_state() {return state;}
    static void init() {
        state = false;
    }
    static void set_state(bool val) {
        if (state == val) {return;}
        else if (val) { // open

        } else { // close

        }
    }
};

// claw
struct claw {

};

// drivetrain
namespace drv {
    
}