
#include <gtest/gtest.h>
#include <field.h>

class FieldTests
    : public testing::Test {
public:
    FieldTests()
        : field(7, 6) {}

    hal::Field field;
};

TEST_F(FieldTests, WinnerTest) {
    hal::Field almost_winner_field = field.do_move(0).do_move(1).do_move(0).do_move(1).do_move(0).do_move(1);

    ASSERT_EQ(almost_winner_field.get_winner(), hal::Disc::None);

    hal::Field winner_field = almost_winner_field.do_move(0);
    ASSERT_EQ(winner_field.get_winner(), hal::Disc::X);
}