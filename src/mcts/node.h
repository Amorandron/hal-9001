
#ifndef HAL_9001_NODE_H
#define HAL_9001_NODE_H

#include <set>

#include "../field.h"

namespace hal {
    class Node {
    public:
        Node()
            : state(0,0) {}
        Node(const Move move, Node* parent)
            : move(move), state(0,0), parent(parent) {}
        Node(const Move move, const State& state, bool is_max = true)
            : move(move), state(state), is_max(is_max) {}
        Node(const Move move, const State& state, Node* parent = nullptr, bool is_max = true)
            : move(move), state(state), parent(parent), is_max(is_max) {}
        ~Node();

        // Getters / Setters
        Move get_move();
        State get_state();
        void set_parent(Node* node);
        Node* get_parent();
        void add_child(Node* node);
        void add_child(Node& node);
        std::set<Node*>* get_children();
        int n() const;
        double w() const;
        bool max() const;

        void visit();
        void value(double value);

    protected:
        const Move move = -1;

        State state;

        Node* parent = nullptr;
        std::set<Node*> children;

        int _n = 0;
        double _w = 0;
        bool is_max = true;
    };
}

#endif
