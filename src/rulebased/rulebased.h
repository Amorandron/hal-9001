
#ifndef HAL_9001_RULEBASED_H
#define HAL_9001_RULEBASED_H

#include <tuple>
#include <vector>

#include "../util/random.h"
#include "../algorithm.h"
#include "../field.h"

namespace hal {
    enum class Bw {
        BLOCK = 0,
        WIN = 1,
        NONE = 2
    };

    struct WinCheck {
        bool done;
        Bw block_win;
        Move move;
    };

    class RuleBased
        : public Algorithm {
    public:
        RuleBased(const State& state, const int& round)
            : state(state), round(round) {}

        Move move() override;
        std::vector<Move> get_blocked_moves();

    private:
        const State state;
        const int round;
        std::vector<Move> blocked_moves;

        bool middle_tile() const;
        std::vector<std::tuple<int, int>> get_top_tiles() const;

        void set_blocked_moves();

        bool bw_tile_horizontal(const int& y, const int& x, const Disc& disc) const;
        bool bw_tile_vertical(const int& y, const int& x, const Disc& disc) const;
        bool bw_tile_diagonal_bl_tr(const int& y, const int& x, const Disc& disc) const;
        bool bw_tile_diagnoal_tl_br(const int& y, const int& x, const Disc& disc) const;
        WinCheck bw_tile(const int& y, const int& x) const;
        Move blocks_wins() const;
    };
}

#endif
