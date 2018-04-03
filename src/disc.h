
#ifndef HAL_9001_DISC_H
#define HAL_9001_DISC_H

#include <iostream>

typedef int Move;

namespace hal {
    enum class Disc {
        None = '-',
        X = 'X',
        O = 'O'
    };

    Disc switch_player(const Disc& disc);
}

#endif
