#include <gtest/gtest.h>
#include <interval_math.h>

using namespace interval_math;

/* Interval tests */
TEST(IntervalTests, MergeIntervalsTests) {
    MultiInterval<double> interval_1, interval_2;

    interval_1 = MultiInterval<double>{Interval<double>(1, 3), Interval<double>(2, 6), Interval<double>(8, 9)};
    interval_2 = MultiInterval<double>{Interval<double>(1, 6), Interval<double>(8, 9)};
    EXPECT_EQ(interval_1, interval_2);
    std::cerr << "Merge test 1:\n";
    std::cerr << "Interval 1: " << interval_1 << "\nInterval 2: " << interval_2 << "\n";
    std::cerr << "------------\n\n";

    interval_1 = MultiInterval<double>{Interval<double>(Infinity::NEGATIVE, 3), Interval<double>(2, 9), Interval<double>(8, Infinity::POSITIVE)};
    interval_2 = MultiInterval<double>{Interval<double>(Infinity::NEGATIVE, Infinity::POSITIVE)};
    EXPECT_EQ(interval_1, interval_2);
    std::cerr << "Merge test 2:\n";
    std::cerr << "Interval 1: " << interval_1 << "\nInterval 2: " << interval_2 << "\n";
    std::cerr << "------------\n\n";
}

TEST(IntervalTests, IntervalOperations) {
    MultiInterval<double> interval_1, interval_2;

    EXPECT_EQ(Interval<double>(1, 2) + Interval<double>(3, 4), Interval<double>(4, 6));
    EXPECT_EQ(Interval<double>(1, 2) - Interval<double>(3, 4), Interval<double>(-3, -1));
    EXPECT_EQ(Interval<double>(1, 2) * Interval<double>(3, 4), Interval<double>(3, 8));

    EXPECT_EQ(Interval<double>(1, 2) / Interval<double>(3, 4), Interval<double>(1.0 / 4.0, 2.0 / 3.0));
    EXPECT_EQ(Interval<double>(1, 2) / Interval<double>(3, 0), Interval<double>(Infinity::NEGATIVE, 2.0 / 3.0));
    EXPECT_EQ(Interval<double>(1, 2) / Interval<double>(0, 4), Interval<double>(1.0 / 4.0, Infinity::POSITIVE));

    interval_1 = Interval<double>(1, 2) / Interval<double>(-3, 4);
    interval_2 = MultiInterval<double>{Interval<double>(Infinity::NEGATIVE, -1.0 / 3.0), Interval<double>(1.0 / 4.0, Infinity::POSITIVE)};
    EXPECT_EQ(interval_1, interval_2);
}