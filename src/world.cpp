#include <thread>
#include "tree/tree.hpp"
#include "world.hpp"

World_t::World_t(DecisionTree_t& dt, time_ms_t fd) noexcept
    : m_dt(dt), m_frame_delay(fd)
{
    std::srand(time(0));
}

void
World_t::updateAI() noexcept {
    m_dt.run(*this);
}

char
World_t::see(DIR_t const d) const noexcept {
    uint8_t constexpr  left { static_cast<uint8_t>(DIR_t::left) };
    uint8_t constexpr right { static_cast<uint8_t>(DIR_t::right) };
    uint8_t constexpr    up { static_cast<uint8_t>(DIR_t::up) };
    uint8_t constexpr  down { static_cast<uint8_t>(DIR_t::down) };
    uint8_t bitdir          { static_cast<uint8_t>(d) };
    int8_t dx { 0 }, dy { 0 };

    if      (bitdir &  left) dx = -1;
    else if (bitdir & right) dx =  1;
    if      (bitdir &    up) dy = -1;
    else if (bitdir &  down) dy =  1;

    return m_map[m_y + dy][m_x + dx];
}

void
World_t::move(DIR_t const d) noexcept {
    int8_t dx { 0 }, dy { 0 };
    switch(d) {
        case DIR_t::left:  { dx=-1; break; }
        case DIR_t::right: { dx= 1; break; }
        default:;
    }
    switch(m_map[m_y+dy][m_x+dx]) {
        case 'o':
        case 'O':
        case '0': {
            m_map[m_y][m_x] = ' ';
            break;
        }
        case ' ': {
            m_map[m_y][m_x] = ' ';
            m_x+=dx; m_y+=dy;
            m_map[m_y][m_x] = '^';
            break;
        }
    }
}

std::size_t
World_t::distanceToBallUp() const noexcept {
    std::size_t distance { 0 };

    for(std::size_t yp1{m_y}; yp1 > 0; --yp1) {
        auto y { yp1 - 1 };
        switch(m_map[y][m_x]) {
            case ' ': { distance += 3;  break;           }
            case '0': { distance += 2;  return distance; }
            case 'O': { distance += 1;  return distance; }
            case 'o': {                 return distance; }
        }
    }

    return distance;
}

void
World_t::update() noexcept {
    if ( !m_alive ) return;

    // Update world
    ++m_cycles;
    m_alive = false;
    createNewBalls();
    for(std::size_t y{0}; y < nRows; ++y) {
        for(std::size_t x{0}; x < nCols; ++x) {
            switch(m_map[y][x]) {
                case '@': { m_map[y][x] = '0';          break; }
                case '0': { m_map[y][x] = 'O';          break; }
                case 'O': { m_map[y][x] = 'o';          break; }
                case 'o': { moveBallDown(x, y);         break; }
                case '^': { m_alive=true; m_x=x; m_y=y; break; }
            }
        }
    }
    // Update AI
    if (m_alive) updateAI();
}

constexpr void
World_t::print() const noexcept {
    for(auto const& row : m_map) {
        for(auto const& item : row)
            std::printf("%c", item);
        std::puts("");
    }
    std::printf("$%05lu$\n", m_cycles);
}

void
World_t::run() noexcept {
    using namespace std::chrono_literals;

    clearScreen();
    while(m_alive) {
        print();
        std::this_thread::sleep_for(m_frame_delay);
        clearScreen();
        update();
    }
    print();
    std::printf("Game Over\n");
}

constexpr void
World_t::moveBallDown(std::size_t const x, std::size_t const y) noexcept {
    if (y == nRows-1) { m_map[y][x]='#'; return; }
    m_map[y  ][x] = ' ';
    m_map[y+1][x] = '@';
}

std::size_t
World_t::randBetween(std::size_t const min, std::size_t const max) const noexcept {
    return min + (std::rand() % (max-min+1));
}

constexpr void
World_t::createNewBalls() noexcept {
    if ( --time2NextBall == 0 ) {
        time2NextBall = randBetween(minTNewBall, maxTNewBall);
        std::size_t x { randBetween(1, nCols-2) };
        m_map[0][x] = '0';
    }
}

void
World_t::clearScreen() const noexcept {
    std::puts("\033[H\033[J");
}
