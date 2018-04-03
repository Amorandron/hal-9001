
#include <gtest/gtest.h>
#include <util/halstring.h>

class HalStringTests
    : public testing::Test {
public:
    std::vector<hal::string> expected_vector {"a", "b", "c"};
    std::string expected_string = "test";
};

TEST_F(HalStringTests, Split) {
    hal::string test_none  = "a b c";
    ASSERT_EQ(test_none.split(), expected_vector);

    hal::string test_comma = "a,b,c";
    ASSERT_EQ(test_comma.split(','), expected_vector);

    hal::string test_escape = "a\nb\nc";
    ASSERT_EQ(test_escape.split('\n'), expected_vector);
}

TEST_F(HalStringTests, Reverse) {
    hal::string test_basic = "test";
    test_basic.reverse();
    ASSERT_EQ(test_basic, "tset");

    hal::string test_empty = "";
    test_basic.reverse();
    ASSERT_EQ(test_empty, "");
}

TEST_F(HalStringTests, Trim) {
    hal::string test_front = "      test";
    test_front.trim();
    ASSERT_EQ(test_front, expected_string);

    hal::string test_back = "test      ";
    test_back.trim();
    ASSERT_EQ(test_back, expected_string);

    hal::string test_tab = "\t\t\ttest\t\t\t";
    test_tab.trim();
    ASSERT_EQ(test_tab, expected_string);

    hal::string test_new_line = "\n\n\ntest\n\n\n";
    test_new_line.trim();
    ASSERT_EQ(test_new_line, expected_string);

    hal::string test_all = "\n \ttest\t \n";
    test_all.trim();
    ASSERT_EQ(test_all, expected_string);
}

TEST_F(HalStringTests, Comparison) {
    hal::string test_equal = "test";
    ASSERT_TRUE(test_equal == "test");
    ASSERT_TRUE(test_equal != "tost");

    hal::string test_equal_empty;
    ASSERT_TRUE(test_equal_empty == "");
}

TEST_F(HalStringTests, Concatination) {
    hal::string test_hal_part_1 = "te";
    hal::string test_hal_part_2 = "st";
    ASSERT_EQ(test_hal_part_1 + test_hal_part_2, expected_string);

    hal::string test_both_part_1 = "te";
    std::string test_both_part_2 = "st";
    ASSERT_EQ(test_both_part_1 + test_both_part_2, expected_string);

    hal::string test_empty_part_1 = "";
    hal::string test_empty_part_2 = "";
    ASSERT_EQ(test_empty_part_1 + test_empty_part_2, "");
}