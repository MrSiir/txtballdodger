#pragma once

#include "../node.hpp"
#include "../../world.hpp"

struct ActionMove_t : Node_t
{
    explicit ActionMove_t(DIR_t d) noexcept
        : direction{d} { }

    void run(World_t& w) noexcept {
        w.move(direction);
    }

private:
    DIR_t direction;
};