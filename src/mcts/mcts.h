
#ifndef HAL_9001_MTSC_H
#define HAL_9001_MTSC_H

#include <chrono>
#include <limits>
#include <random>

#include "node.h"
#include "../util/random.h"
#include "../util/timer.h"
#include "../algorithm.h"

const double c = sqrt(2);

namespace hal {
    class MonteCarloTreeSearch
        : public Algorithm {
    public:
        MonteCarloTreeSearch(const State& state, const Disc& your_botdisc)
            : root(new Node(-1, state, true)), your_botdisc(your_botdisc) {}
        MonteCarloTreeSearch(Node* root, const Disc& your_botdisc)
            : root(root), your_botdisc(your_botdisc) {}
        ~MonteCarloTreeSearch();

        Move move(int& tpm, std::vector<Move>& blocked_moves) override;

    private:
        Node* root;
        const Disc your_botdisc;

        double uct(const Node* node) const;
        Node* best_uct_node(Node* node) const;

        Node* selection();
        void expansion(Node* node);
        double simulation(Node* node);
        void back_propagation(Node* node, double& score);
    };
}

#endif
