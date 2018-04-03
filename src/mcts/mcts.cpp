
#include "mcts.h"

hal::MonteCarloTreeSearch::~MonteCarloTreeSearch() {
    delete root;
}

double hal::MonteCarloTreeSearch::uct(const hal::Node* n) const {
    if(n->n() == 0)
        return std::numeric_limits<double>::max();
    return (n->w() / n->n()) + c * (sqrt(log(root->n() + 1) / n->n()));
}

hal::Node* hal::MonteCarloTreeSearch::best_uct_node(hal::Node* node) const {
    if (node == nullptr)
        return nullptr;

    if (node->get_children()->empty())
        return node;

    std::set<Node*>* children = node->get_children();

    Node* max_node = nullptr;
    double max_score = std::numeric_limits<double>::min();

    for(Node* child : *children) {
        double score = uct(child);

        if(score > max_score) {
            max_node = child;
            max_score = score;
        }
    }

    return max_node;
}

hal::Node* hal::MonteCarloTreeSearch::selection() {
    Node* current = root;

    while (!current->get_children()->empty())
        current = best_uct_node(current);

    return current;
}

void hal::MonteCarloTreeSearch::expansion(hal::Node* node) {
    if(node == nullptr)
        node = root;

    State state = node->get_state();
    std::vector<Move> moves = state.get_moves();

    for(Move move : moves) {
        State new_state = state.do_move(move);
        Node* new_node = new Node(move, new_state, node, !node->max());
        node->add_child(new_node);
    }
}

double hal::MonteCarloTreeSearch::simulation(hal::Node* node) {
    State state = node->get_state();
    Disc winner = state.get_winner();

    while(winner == Disc::None) {
        winner = state.get_winner();

        if(winner == your_botdisc)
            return 0;
        else if(winner == switch_player(your_botdisc))
            return 1;

        std::vector<Move> possible_moves = state.get_moves();

        if(possible_moves.empty())
            return 0;

        Random rd;
        Move random_move = possible_moves[rd.range<size_t>(0, possible_moves.size() - 1)];
        state = state.do_move(random_move);
    }
    return 0;
}

void hal::MonteCarloTreeSearch::back_propagation(hal::Node* node, double& score) {
    node->visit();
    node->value(score);

    if(node->get_parent() != nullptr)
        back_propagation(node->get_parent(), score);
}

Move hal::MonteCarloTreeSearch::move(int& timeout, std::vector<Move>& blocked_moves) {
    Timer timer;
    Random rd;

    timer.start();
    while(timer.elapsed_int() < timeout) {
        Node* focus = selection();
        if(focus->get_state().get_winner() == Disc::None)
            expansion(focus);

        Node* simulation_node = focus;
        if(!focus->get_children()->empty())
            simulation_node = rd.random_set<Node*>(*simulation_node->get_children());

        double score = simulation(simulation_node);
        back_propagation(simulation_node, score);
    }

    for(Node* child : *root->get_children()) {
        std::cerr << "Move: " << child->get_move() << " (Visits: " << child->n() << ", score: " << child->w() << ")" << std::endl;
    }

    std::vector<Node*> non_blocked;

    for(Node* child : *root->get_children()) {
        bool appears = false;

        for(Move blocked_move : blocked_moves)
            if(blocked_move == child->get_move())
                appears = true;

        if(!appears)
            non_blocked.push_back(child);
    }

    Move best_move = std::numeric_limits<Move>::min();
    double best_score = -1;

    std::vector<Node*> equals;

    for(Node* child : non_blocked) {
        if(child->w() > best_score) {
            equals.empty();
            best_score = child->w();
            best_move = child->get_move();
        }
        else if(child->w() == best_score)
            equals.push_back(child);
    }

    if(!equals.empty())
        best_move = equals[rd.range<size_t>(0, equals.size() - 1)]->get_move();

    std::cerr << "Best move: " << best_move << std::endl;
    return best_move;
}