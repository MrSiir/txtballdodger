#pragma once

#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <chrono>
#include <array>
#include "dir.hpp"

struct DecisionTree_t;

struct World_t {
    // Constants
    static constexpr std::size_t minTNewBall {  4 };
    static constexpr std::size_t maxTNewBall { 12 };
    static constexpr std::size_t nRows { 10 };
    static constexpr std::size_t nCols {  7 };
    using Row_t = std::array<char,  nCols>;
    using Map_t = std::array<Row_t, nRows>;
    using time_ms_t = std::chrono::duration<uint32_t, std::milli>;

    explicit World_t(DecisionTree_t& dt, time_ms_t fd) noexcept;

              char        see             (DIR_t const d)       const noexcept;
              void        move            (DIR_t const d)             noexcept;
              std::size_t distanceToBallUp()                    const noexcept;
    constexpr void        print           ()                    const noexcept;
              void        run             ()                          noexcept;

private:
    DecisionTree_t& m_dt;
    std::size_t m_cycles { 0 };
    std::size_t time2NextBall { 1 };
    std::size_t m_x { 0 }, m_y { 0 };
    time_ms_t   m_frame_delay { 40 };
    bool        m_alive { true };

              void          update        ()                                                   noexcept;
              void          clearScreen   ()                                             const noexcept;
              void          updateAI      ()                                                   noexcept;
    constexpr void          moveBallDown  (std::size_t const x, std::size_t const y)           noexcept;
              std::size_t   randBetween   (std::size_t const min, std::size_t const max) const noexcept;
    constexpr void          createNewBalls()                                                   noexcept;

    Map_t m_map {{
         {{ '#',' ',' ',' ',' ',' ','#' }}
        ,{{ '#',' ',' ',' ',' ',' ','#' }}
        ,{{ '#',' ',' ',' ',' ',' ','#' }}
        ,{{ '#',' ',' ',' ',' ',' ','#' }}
        ,{{ '#',' ',' ',' ',' ',' ','#' }}
        ,{{ '#',' ',' ',' ',' ',' ','#' }}
        ,{{ '#',' ',' ',' ',' ',' ','#' }}
        ,{{ '#',' ',' ',' ',' ',' ','#' }}
        ,{{ '|',' ',' ','^',' ',' ','|' }}
        ,{{ '#','#','#','#','#','#','#' }}
    }};
};
