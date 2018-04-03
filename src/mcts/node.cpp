
#include "node.h"

hal::Node::~Node() {
    if(parent != nullptr && parent->children.empty())
        parent->get_children()->erase(this);

    for (Node* child : children)
        delete child;
}

Move hal::Node::get_move() {
    return move;
}

void hal::Node::add_child(Node* node) {
    node->set_parent(this);
    children.insert(node);
}

void hal::Node::add_child(hal::Node& node) {
    node.set_parent(this);
    children.insert(&node);
}

std::set<hal::Node*>* hal::Node::get_children() {
    return &children;
}

void hal::Node::set_parent(Node* node) {
    parent = node;
}

hal::Node* hal::Node::get_parent() {
    return parent;
}

hal::State hal::Node::get_state() {
    return state;
}

int hal::Node::n() const {
    return _n;
}

double hal::Node::w() const {
    return _w;
}

bool hal::Node::max() const {
    return is_max;
}

void hal::Node::visit() {
    _n++;
}

void hal::Node::value(double value) {
    _w += value;
}
