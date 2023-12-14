#pragma once

#include "../globals.hpp"
#include "../lib/autonomous.hpp"

// ROUTES
#include "close.hpp"
#include "far.hpp"

// SKILLS
#include "skills.hpp"

// TEST
namespace route {
    inline void test_4() {
        auton::advance_dist(TILE);
        // auton::turn_to(90, 0.5);
        auton::advance_dist(-TILE);
    }
}