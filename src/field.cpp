
#include "field.h"

hal::Field::Field(int w, int h)
    : w(w), h(h) {

    std::cerr << "Creating field" << std::endl;

    for(int y = 0; y < h; ++y) {
        std::vector<Disc> current;
        for(int x = 0; x < w; ++x)
            current.push_back(Disc::None);
        field.push_back(current);
    }
}

hal::Field::Field(const std::vector<std::vector<char>>& grid)
    : w(grid[0].size()), h(grid.size()) {

    for(int y = 0; y < h; ++y) {
        std::vector<Disc> current;
        for(int x = 0; x < w; ++x) {
            if(grid[y][x] == 'X')
                current.push_back(Disc::X);
            else if(grid[y][x] == 'O')
                current.push_back(Disc::O);
            else
                current.push_back(Disc::None);
        }
        field.push_back(current);
    }
}

hal::Field::Field(const hal::Field& f)
    : w(f.w), h(f.h), field(f.field) {}

hal::Disc hal::Field::get_current_player() const {
    int countX = 0;
    int countO = 0;
    for(int r=0; r<h; r++) {
        for(int c=0; c<w; c++) {
            if(field[r][c] == Disc::X)
                countX++;
            else if(field[r][c] == Disc::O)
                countO++;
        }
    }
    return(countX > countO ? Disc::O : Disc::X);
}

hal::Field hal::Field::do_move(const Move& move) const {
    Field result = *this;

    for(int r=0; r<h; r++) {
        if(r == 5 || result[r + 1][move] != Disc::None) {
            result[r][move] = get_current_player();
            return result;
        }
    }
    return result; // Invalid move
}

hal::Disc hal::Field::get_winner() const {
    for(int r=0; r<h; r++) {
        for(int c=0; c<w; c++) {
            if(field[r][c] != Disc::None) {
                if(c<4) {
                    if(field[r][c] == field[r][c+1] && field[r][c] == field[r][c+2] && field[r][c] == field[r][c+3])
                        return field[r][c];
                    if(r<3) {
                        if (field[r][c] == field[r+1][c+1] && field[r][c] == field[r+2][c+2] && field[r][c] == field[r+3][c+3])
                            return field[r][c];
                    }
                }
                if (r<3) {
                    if(field[r][c] == field[r+1][c] && field[r][c] == field[r+2][c] && field[r][c] == field[r+3][c])
                        return field[r][c];
                    if(c>2) {
                        if(field[r][c] == field[r+1][c-1] && field[r][c] == field[r+2][c-2] && field[r][c] == field[r+3][c-3])
                            return field[r][c];
                    }
                }
            }
        }
    }

    return Disc::None;
}

std::vector<Move> hal::Field::get_moves() const {
    std::vector<Move> moves;
    if(get_winner() == Disc::None)
        for(int i=0; i<7; i++)
            if(field[0][i] == Disc::None)
                moves.push_back(i);
    return moves;
}

int hal::Field::width() const {
    return w;
}

int hal::Field::height() const {
    return h;
}

int hal::Field::middle_column() const {
    return static_cast<int>(floor(width() / 2));
}

bool hal::Field::operator==(const hal::Field& other) {
    return field == other.field && w == other.w && h == other.h;
}

bool hal::Field::operator!=(const hal::Field& other) {
    return !(*this == other);
}

// Get row
std::vector<hal::Disc>& hal::Field::operator[](const int& index) const {
    if(index > h)
        throw std::out_of_range("Index out of range");

    return field[index];
}

std::ostream& operator<<(std::ostream& os, hal::Field& field) {
    // Header
    os << " ||";
    for(int x = 0; x < field.width(); ++x)
        os << x << '|';
    os << '\n';
    os << "=++";
    for(int x = 0; x < field.width(); ++x)
        os << "==";
    os << '\n';

    for(int y = 0; y < field.height(); ++y) {
        os << y << "||";

        for(int x = 0; x < field.width(); ++x)
            os << static_cast<char>(field[y][x]) << '|';
        os << '\n';

        os << "-++";
        for(int x = 0; x < field.width(); ++x)
            os << "-+";
        os << '\n';
    }

    return os;
}

