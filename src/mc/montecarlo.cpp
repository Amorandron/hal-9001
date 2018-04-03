
#include "montecarlo.h"

hal::MonteCarlo::MonteCarlo(const hal::State& state, const hal::Disc& your_botdisc)
    : state(state), your_botdisc(your_botdisc) {

    for(Move move : state.get_moves())
        scoreboard[move] = 0;
}

void hal::MonteCarlo::trial(Move initial) {
    State mc_state = state.do_move(initial);
    Disc winner = mc_state.get_winner();

    while(winner == Disc::None) {
        winner = mc_state.get_winner();

        if(winner == your_botdisc) {
            scoreboard[initial] -= 1;
            return;
        }
        else if(winner == switch_player(your_botdisc)) {
            scoreboard[initial] += 1;
            return;
        }

        std::vector<Move> moves = mc_state.get_moves();

        if(moves.empty()) {
            scoreboard[initial] += 0.5;
            return;
        }

        Random rd;
        mc_state = mc_state.do_move(moves[rd.range<size_t>(0, moves.size() - 1)]);
    }
}

Move hal::MonteCarlo::move(int& tpm) {
    Timer timer;
    Random rd;

    int iterations = 0;

    std::vector<Move> moves = state.get_moves();

    timer.start();
    while(timer.elapsed_int() < tpm) {
        iterations++;
        trial(moves[rd.range<int>(0, moves.size() - 1)]);
    }

    Move best_move = std::numeric_limits<Move>::min();
    double best_score = std::numeric_limits<double >::min();

    for(auto move : scoreboard) {
        if(move.second > best_score) {
            best_move = move.first;
            best_score = move.second;
        }
    }

    std::cerr << "Iteratins: " << iterations << std::endl;
    return best_move;
}