
#include <gtest/gtest.h>
#include <rulebased/rulebased.h>

class RulebasedTests
    : public testing::Test {
public:
    RulebasedTests()
        : small_field(3, 2), field(7, 6), big_field(15, 12) {}

    hal::Field small_field;
    hal::Field field;
    hal::Field big_field;
};

TEST_F(RulebasedTests, FirstMove) {
    hal::RuleBased rb_s(small_field, 1);
    ASSERT_EQ(rb_s.move(), 1);

    hal::RuleBased rb_m(field, 1);
    ASSERT_EQ(rb_m.move(), 3);

    hal::RuleBased rb_b(big_field, 1);
    ASSERT_EQ(rb_b.move(), 7);
}

TEST_F(RulebasedTests, WinningBlocking) {
    hal::Field vertical_no = field.do_move(0).do_move(2).do_move(0).do_move(4);
    hal::RuleBased rb_vert_no(vertical_no, -1);
    ASSERT_EQ(rb_vert_no.move(), -1);

    hal::Field vertical = vertical_no.do_move(0).do_move(6);
    hal::RuleBased rb_vert(vertical, -1);
    ASSERT_EQ(rb_vert.move(), 0);

    hal::Field horizontal_no = field.do_move(0).do_move(6).do_move(1).do_move(6);
    hal::RuleBased rb_hor_no(horizontal_no, -1);
    ASSERT_EQ(rb_hor_no.move(), -1);

    hal::Field horizontal = horizontal_no.do_move(2).do_move(5);
    hal::RuleBased rb_hor(horizontal, -1);
    ASSERT_EQ(rb_hor.move(), 3);

    hal::Field horizontal_seperated = {{
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','O','O' }},
        {{  'X','X','-','X','X','O','O' }}
    }};
    hal::RuleBased rb_hor_sep(horizontal_seperated, -1);
    ASSERT_EQ(rb_hor_sep.move(), 2);

    hal::Field diagonal_1 = {{
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','X','-' }},
        {{  '-','-','-','-','-','O','-' }},
        {{  '-','-','-','X','O','X','-' }},
        {{  '-','-','X','O','O','X','O' }}
    }};
    hal::RuleBased rb_dia_1(diagonal_1, -1);
    ASSERT_EQ(rb_dia_1.move(), 4);

    hal::Field diagonal_2 = {{
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','X','X','-','-','-' }},
        {{  '-','-','O','O','X','-','-' }},
        {{  '-','O','X','O','O','X','-' }}
    }};
    hal::RuleBased rb_dia_2(diagonal_2, -1);
    ASSERT_EQ(rb_dia_2.move(), 2);
}

TEST_F(RulebasedTests, MultipleChoice) {
    hal::Field multiple = {{
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  'X','O','-','-','-','-','-' }},
        {{  'X','O','-','-','-','-','-' }},
        {{  'X','O','-','-','-','-','-' }}
    }};
    hal::RuleBased rb_multiple(multiple, -1);
    ASSERT_EQ(rb_multiple.move(), 0);

    hal::Field multiple_w = {{
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  '-','-','-','-','-','-','-' }},
        {{  'X','X','O','O','-','-','-' }},
        {{  'X','X','O','O','-','-','-' }},
        {{  'X','X','O','O','-','-','-' }}
    }};
    hal::RuleBased rb_multiple_w(multiple_w, -1);
    Move move = rb_multiple_w.move();
    ASSERT_TRUE(move == 0 || move == 1);
}