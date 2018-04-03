
#include <gtest/gtest.h>
#include <util/random.h>

class RandomTests
        : public testing::Test {
public:
    int lower = 0, upper = 1000;
    hal::Random int_rnd;
};

TEST_F(RandomTests, Randomness) {
    int val_1 = int_rnd.range(lower, upper);
    int val_2 = int_rnd.range(lower, upper);

    while(val_1 != val_2) {
        ASSERT_TRUE(val_1 != val_2);
        val_2 = int_rnd.range(lower, upper);
    }

    ASSERT_EQ(val_1, val_2);
}

TEST_F(RandomTests, LowerBounds) {
    int val = int_rnd.range(lower, upper);

    while(val != lower) {
        ASSERT_TRUE(val != lower);
        val = int_rnd.range(lower, upper);
    }

    ASSERT_EQ(val, lower);
}

TEST_F(RandomTests, UpperBounds) {
    int val = int_rnd.range(lower, upper);

    while(val != upper) {
        ASSERT_TRUE(val != upper);
        val = int_rnd.range(lower, upper);
    }

    ASSERT_EQ(val, upper);
}

TEST_F(RandomTests, Set) {
    std::set<int> integers;

    for(int i = 0; i < 10000; ++i)
        integers.insert(i);

    ASSERT_TRUE(int_rnd.random_set<int>(integers) != int_rnd.random_set<int>(integers));
}