#pragma once

#include "../node.hpp"
#include "../../world.hpp"

struct NodeMove_t : Node_t
{
    explicit NodeMove_t(Node_t& l, Node_t& r) noexcept
        : left{l}, right{r} { }

    void run(World_t& w) noexcept {

        // std::srand(time(0));
        // w.randBetween(0, 100) >= 50

        if (rand() % 100 > 50) {
            if (w.see(DIR_t::left) == ' ') {
                left.run(w);
            } else if (w.see(DIR_t::right) == ' ') {
                right.run(w);
            }
        } else {
            if (w.see(DIR_t::right) == ' ') {
                right.run(w);
            } else if (w.see(DIR_t::left) == ' ') {
                left.run(w);
            }
        }
    }

private:
    Node_t& left;
    Node_t& right;
};