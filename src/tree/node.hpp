#pragma once

struct World_t;

struct Node_t
{
    virtual void run(World_t&) noexcept = 0;
    virtual ~Node_t() noexcept = default;
};