
#ifndef HAL_9001_MONTECARLO_H
#define HAL_9001_MONTECARLO_H

#include <map>

#include "../util/random.h"
#include "../util/timer.h"
#include "../algorithm.h"
#include "../field.h"

namespace hal {
    typedef std::map<Move, double> Scoreboard;

    class MonteCarlo
        : public Algorithm {
    public:
        MonteCarlo(const State& state, const Disc& your_botdisc);

        Move move(int& tpm) override;

    private:
        const State state;
        const Disc your_botdisc;

        Scoreboard scoreboard;

        void trial(Move intial);
    };
}

#endif
