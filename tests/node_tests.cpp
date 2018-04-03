
#include <gtest/gtest.h>
#include <mcts/node.h>

class NodeTests
    : public testing::Test {
public:
    hal::Node root_node;
    int hierarchy_depth = 10;

    void recursive_child(hal::Node* node, int depth) {
        if(depth <= 0)
            return;

        hal::Node* new_node = new hal::Node;
        node->add_child(new_node);
        recursive_child(new_node, depth - 1);
    }
};

TEST_F(NodeTests, ChildTests) {
    ASSERT_EQ(root_node.get_state().width(), 0);
    ASSERT_EQ(root_node.get_state().height(), 0);

    hal::Node* child_test = new hal::Node;
    root_node.add_child(child_test);
    ASSERT_EQ(root_node.get_children()->size(), 1);

    child_test->value(0.5);
    ASSERT_EQ((*root_node.get_children()->begin())->w(), 0.5);

    child_test->get_parent()->value(0.8);
    ASSERT_EQ(root_node.w(), 0.8);

    delete child_test;
}

TEST_F(NodeTests, HierarchyTests) {
    recursive_child(&root_node, hierarchy_depth);

    hal::Node* current = &root_node;
    int count = 0;
    while(!current->get_children()->empty()) {
        count++;
        current = *current->get_children()->begin();
    }

    ASSERT_EQ(count, hierarchy_depth);
}