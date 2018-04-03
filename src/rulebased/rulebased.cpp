
#include "rulebased.h"

bool hal::RuleBased::middle_tile() const {
    int y = state.height() - 1;

    return round == 1 && state[y][state.middle_column()] == Disc::None;
}

Move hal::RuleBased::blocks_wins() const {
    std::vector<WinCheck> win_checks;

    for(std::tuple<int, int> tile : get_top_tiles()) {
        int y = std::get<0>(tile);
        int x = std::get<1>(tile);

        WinCheck check = bw_tile(y, x);

        if(check.done)
            win_checks.push_back(check);
    }

    if(win_checks.size() == 1)
        return win_checks[0].move;
    else {
        std::vector<Move> wins;
        std::vector<Move> blocks;

        for(WinCheck wc : win_checks) {
            if(wc.block_win == Bw::WIN)
                wins.push_back(wc.move);
            else if(wc.block_win == Bw::BLOCK)
                blocks.push_back(wc.move);
        }

        Random rd;
        if(!wins.empty()) {
            std::cerr << "Win!" << std::endl;
            return wins[rd.range<size_t>(0, wins.size() - 1)];
        }
        else if(!blocks.empty()) {
            std::cerr << "Blocked!" << std::endl;
            return blocks[rd.range<size_t>(0, blocks.size() - 1)];
        }
    }

    return -1;
}

bool hal::RuleBased::bw_tile_horizontal(const int& y, const int& x, const Disc& disc) const {
    int count = 0;

    for(int i = x - 1; i >= 0; --i) {
        if(state[y][i] == disc)
            count++;
        else
            break;
    }

    for(int i = x + 1; i < state.width(); ++i) {
        if(state[y][i] == disc)
            count++;
        else
            break;
    }

    return count >= 3;
}

bool hal::RuleBased::bw_tile_vertical(const int& y, const int& x, const Disc& disc) const {
    int count = 0;

    for (int i = y + 1; i < state.height(); ++i) {
        if (state[i][x] == disc)
            count++;
        else
            break;
    }

    return count >= 3;
}

bool hal::RuleBased::bw_tile_diagonal_bl_tr(const int& y, const int& x, const Disc& disc) const {
    int count = 0;

    for(int r = y + 1, c = x - 1; r < state.height() &&  c >= 0; ++r, --c) {
        if(state[r][c] == disc)
            count++;
        else
            break;
    }

    for(int r = y - 1, c = x + 1; r >= 0 && c < state.width(); ++c, --r) {
        if(state[r][c] == disc)
            count++;
        else
            break;
    }

    return count >= 3;
}

bool hal::RuleBased::bw_tile_diagnoal_tl_br(const int& y, const int& x, const Disc& disc) const {
    int count = 0;

    for(int r = y - 1, c = x - 1; r >= 0 && c >= 0; --r, --c) {
        if(state[r][c] == disc)
            count++;
        else
            break;
    }

    for(int r = y + 1, c = x + 1; r < state.height() && c < state.width(); ++c, ++r) {
        if(state[r][c] == disc)
            count++;
        else
            break;
    }

    return count >= 3;
}

hal::WinCheck hal::RuleBased::bw_tile(const int& y, const int& x) const {
    bool result = false;
    std::vector<Disc> discs {Disc::X, Disc::O};

    for(Disc& disc : discs) {
        result = bw_tile_horizontal(y, x, disc) || result;
        result = bw_tile_vertical(y, x, disc) || result;
        result = bw_tile_diagonal_bl_tr(y, x, disc) || result;
        result = bw_tile_diagnoal_tl_br(y, x, disc) || result;

        if(result) {
            if(disc == state.get_current_player())
                return {result, Bw::WIN, x};
            else
                return {result, Bw::BLOCK, x};
        }
    }

    return {result, Bw::NONE, x};
}

std::vector<std::tuple<int, int>> hal::RuleBased::get_top_tiles() const {
    std::vector<std::tuple<int, int>> positions;
    std::vector<Move> moves = state.get_moves();

    for(int y = 0; y < state.height(); ++y) {
        for (int x : moves) {

            if(state[y][x] == Disc::None) {

                if(y == state.height() - 1)
                    positions.emplace_back(std::tuple<int, int>(y, x));
                else  {
                    bool empty_found = false;

                    for(int i = y + 1; i < state.height(); ++i)
                        if(state[i][x] == Disc::None)
                            empty_found = true;

                    if(!empty_found)
                        positions.emplace_back(std::tuple<int, int>(y, x));
                }
            }
        }
    }

    return positions;
}

void hal::RuleBased::set_blocked_moves() {
    std::vector<Move> moves = state.get_moves();
    std::vector<Move> new_moves;

    Disc me = state.get_current_player();
    Disc other = switch_player(me);

    for(Move move : moves) {
        State copy = state;

        if(copy.do_move(move).do_move(move).get_winner() == other) {
            std::cerr << "Blocked move: " << move << std::endl;
            new_moves.push_back(move);
        }
    }

    if(new_moves.size() != blocked_moves.size())
        blocked_moves = new_moves;
}

std::vector<Move> hal::RuleBased::get_blocked_moves() {
    return blocked_moves;
}

Move hal::RuleBased::move() {
    if(state.get_winner() != Disc::None)
        return false;

    if(state.get_moves().size() == 1)
        return state.get_moves()[0];

    if(middle_tile())
        return state.middle_column();

    if(state.get_moves().size() > 1)
        set_blocked_moves();

    return blocks_wins();
}


