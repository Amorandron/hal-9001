
#ifndef HAL_9001_BOARD_H
#define HAL_9001_BOARD_H

#include <cmath>
#include <stdexcept>
#include <vector>

#include "disc.h"

namespace hal {
    class Field {
    public:
        Field(int w, int h);
        Field(const std::vector<std::vector<char>>& grid);
        Field(const Field& field);

        Disc get_current_player() const;
        Field do_move(const Move& move) const;
        Disc get_winner() const;
        std::vector<Move> get_moves() const;

        int width() const;
        int height() const;
        int middle_column() const;

        bool operator==(const Field& other);
        bool operator!=(const Field& other);
        std::vector<hal::Disc>& operator[](const int& index) const;

    private:
        int w, h;
        mutable std::vector<std::vector<hal::Disc>> field;
    };

    typedef Field State;
}

std::ostream& operator<<(std::ostream& os, hal::Field& field);

#endif
