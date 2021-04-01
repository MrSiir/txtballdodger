#pragma once
#include <cstdint>

enum class DIR_t : uint8_t {
            left = 0b10000000
    ,      right = 0b01000000
    ,         up = 0b00100000
    ,       down = 0b00010000
    ,    left_up = 0b10100000
    ,  left_down = 0b10010000
    ,   right_up = 0b01100000
    , right_down = 0b01010000
};
