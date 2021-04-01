#pragma once

#include "../node.hpp"
#include "../../world.hpp"

struct ActionIdle_t : Node_t
{
    void run(World_t& w) noexcept {
        // Noop
    }
};