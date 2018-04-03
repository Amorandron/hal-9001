
#ifndef HAL_9001_ALGORITHM_H
#define HAL_9001_ALGORITHM_H

#include "disc.h"

// Algorithm Interface
namespace hal {
    class Algorithm {
    public:
        virtual Move move() {
            return -1;
        }
        virtual Move move(int& tpm) {
            return -1;
        }
        virtual Move move(int& tpm, std::vector<Move>& blocked_moves) {
            return -1;
        }
    };
}

#endif
