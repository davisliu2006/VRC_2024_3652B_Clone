#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

namespace route {
    inline void test_route() {
        while (true) {
            auton::wait(1);
            cata::release();
            auton::wait(1);
            cata::load();
        }
        auton::wait(1);
        auton::advance(TILE);
    }
}