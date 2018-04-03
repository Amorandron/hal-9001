
#include "disc.h"

hal::Disc hal::switch_player(const Disc& disc) {
    if(disc == Disc::X)
        return Disc::O;
    else if(disc == Disc::O)
        return Disc::X;
    return Disc::None;
}