#pragma once

#include "../node.hpp"
#include "../../world.hpp"

struct NodeIamSafe_t : Node_t
{
    explicit NodeIamSafe_t(Node_t& y, Node_t& n) noexcept
        : yes{y}, no{n} { }

    void run(World_t& w) noexcept {
        if (w.distanceToBallUp() > 0)
            yes.run(w);
        else
            no.run(w);
    }

private:
    Node_t& yes;
    Node_t& no;
};