#include <gtest/gtest.h>
#include <interval_math.h>

using namespace interval_math;

/* Cast Test */

TEST(CastTest, AllTests) {
    EXPECT_EQ(ExtendedSet<int>(1) == 1, true);
    EXPECT_EQ(1 == ExtendedSet<int>(1), true);
    EXPECT_EQ(Infinity::POSITIVE == ExtendedSet<int>(1), false);
    EXPECT_EQ(ExtendedSet<int>(1) == Infinity::POSITIVE, false);
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE) == Infinity::NEGATIVE, true);

    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE) == 0, true);
}



/* EqOperatorTest */

TEST(EqualOperatorTest, WithNumbers) {
    EXPECT_EQ(ExtendedSet<int>(1) == ExtendedSet<int>(1), true);
    EXPECT_EQ(ExtendedSet<int>(-1) == ExtendedSet<int>(-1), true);
    EXPECT_EQ(ExtendedSet<int>(1) == ExtendedSet<int>(-1), false);
    EXPECT_EQ(ExtendedSet<int>(-1) == ExtendedSet<int>(1), false);

    EXPECT_EQ(ExtendedSet<int>(10) == ExtendedSet<int>(2), false);
    EXPECT_EQ(ExtendedSet<int>(0) == ExtendedSet<int>(0), true);
}

TEST(EqualOperatorTest, WithInf) {
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE) == ExtendedSet<int>(Infinity::POSITIVE), true);
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE) == ExtendedSet<int>(Infinity::NEGATIVE), true);
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE) == ExtendedSet<int>(Infinity::NEGATIVE), false);
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE) == ExtendedSet<int>(Infinity::POSITIVE), false);
}

TEST(EqualOperatorTest, WithInfAndNumbers) {
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE) == ExtendedSet<int>(1), false);
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE) == ExtendedSet<int>(-1), false);
    EXPECT_EQ(ExtendedSet<int>(-1) == ExtendedSet<int>(Infinity::POSITIVE), false);
    EXPECT_EQ(ExtendedSet<int>(1) == ExtendedSet<int>(Infinity::NEGATIVE), false);
}

TEST(EqualOperatorTest, WithSpecialStates) {
    EXPECT_EQ(ExtendedSet<int>(BadState::NaN) == ExtendedSet<int>(BadState::NaN), false);
    EXPECT_EQ(ExtendedSet<int>(BadState::NaN) == ExtendedSet<int>(1), false);
    EXPECT_EQ(ExtendedSet<int>(1) == ExtendedSet<int>(BadState::NaN), false);
    EXPECT_EQ(ExtendedSet<int>(BadState::NaN) == ExtendedSet<int>(Infinity::NEGATIVE), false);

    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE) == ExtendedSet<int>(Zero::NEGATIVE), false);
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE) == ExtendedSet<int>(Zero::POSITIVE), true);
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE) == ExtendedSet<int>(Zero::NEGATIVE), true);
}



/* NotEqOperatorTest */

TEST(NotEqualOperatorTest, WithNumbers) {
    EXPECT_EQ(ExtendedSet<int>(1) != ExtendedSet<int>(1), false);
    EXPECT_EQ(ExtendedSet<int>(-1) != ExtendedSet<int>(-1), false);
    EXPECT_EQ(ExtendedSet<int>(1) != ExtendedSet<int>(-1), true);
    EXPECT_EQ(ExtendedSet<int>(-1) != ExtendedSet<int>(1), true);

    EXPECT_EQ(ExtendedSet<int>(10) != ExtendedSet<int>(2), true);
    EXPECT_EQ(ExtendedSet<int>(0) != ExtendedSet<int>(0), false);
}

TEST(NotEqualOperatorTest, WithInf) {
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE) != ExtendedSet<int>(Infinity::POSITIVE), false);
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE) != ExtendedSet<int>(Infinity::NEGATIVE), false);
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE) != ExtendedSet<int>(Infinity::NEGATIVE), true);
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE) != ExtendedSet<int>(Infinity::POSITIVE), true);
}

TEST(NotEqualOperatorTest, WithInfAndNumbers) {
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE) != ExtendedSet<int>(1), true);
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE) != ExtendedSet<int>(-1), true);
    EXPECT_EQ(ExtendedSet<int>(-1) != ExtendedSet<int>(Infinity::POSITIVE), true);
    EXPECT_EQ(ExtendedSet<int>(1) != ExtendedSet<int>(Infinity::NEGATIVE), true);
}

TEST(NotEqualOperatorTest, WithSpecialStates) {
    EXPECT_EQ(ExtendedSet<int>(BadState::NaN) != ExtendedSet<int>(BadState::NaN), true);
    EXPECT_EQ(ExtendedSet<int>(BadState::NaN) != ExtendedSet<int>(1), true);
    EXPECT_EQ(ExtendedSet<int>(1) != ExtendedSet<int>(BadState::NaN), true);
    EXPECT_EQ(ExtendedSet<int>(BadState::NaN) != ExtendedSet<int>(Infinity::NEGATIVE), true);

    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE) != ExtendedSet<int>(Zero::NEGATIVE), true);
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE) != ExtendedSet<int>(Zero::POSITIVE), false);
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE) != ExtendedSet<int>(Zero::NEGATIVE), false);
}



/* GreaterThanOperatorTest */

TEST(GreaterThanOperatorTest, WithNumbers) {
    EXPECT_EQ(ExtendedSet<int>(2) > ExtendedSet<int>(1), true);
    EXPECT_EQ(ExtendedSet<int>(1) > ExtendedSet<int>(2), false);
    EXPECT_EQ(ExtendedSet<int>(-1) > ExtendedSet<int>(-2), true);
    EXPECT_EQ(ExtendedSet<int>(-2) > ExtendedSet<int>(-1), false);
    EXPECT_EQ(ExtendedSet<int>(-1) > ExtendedSet<int>(-2), true);
    EXPECT_EQ(ExtendedSet<int>(1) > ExtendedSet<int>(-1), true);
    EXPECT_EQ(ExtendedSet<int>(-1) > ExtendedSet<int>(1), false);
}

TEST(GreaterThanOperatorTest, Combined) {
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE) > ExtendedSet<int>(1), true);
    EXPECT_EQ(ExtendedSet<int>(1) > ExtendedSet<int>(0), true);
    EXPECT_EQ(ExtendedSet<int>(0) > ExtendedSet<int>(Zero::NEGATIVE), true);
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE) > ExtendedSet<int>(-1), true);
    EXPECT_EQ(ExtendedSet<int>(-1) > ExtendedSet<int>(Infinity::NEGATIVE), true);
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE) > ExtendedSet<int>(Infinity::NEGATIVE), true);

    EXPECT_EQ(ExtendedSet<int>(ExtendedSet<int>(1) > Infinity::POSITIVE), false);
    EXPECT_EQ(ExtendedSet<int>(0) > ExtendedSet<int>(1), false);
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE) > ExtendedSet<int>(0), false);
    EXPECT_EQ(ExtendedSet<int>(-1) > ExtendedSet<int>(Zero::NEGATIVE), false);
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE) > ExtendedSet<int>(-1), false);
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE) > ExtendedSet<int>(Infinity::POSITIVE), false);
}



/* SumOperationTest */

TEST(SumOperatorTest, AllTests) {
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    + ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    + ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        + ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        + ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     + ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::NEGATIVE));;
    EXPECT_TRUE((ExtendedSet<int>(Infinity::POSITIVE) + ExtendedSet<int>(Infinity::NEGATIVE)).NaN());

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    + ExtendedSet<int>(-1),                 ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    + ExtendedSet<int>(-1),                 ExtendedSet<int>(-2));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        + ExtendedSet<int>(-1),                 ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        + ExtendedSet<int>(-1),                 ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(1)                     + ExtendedSet<int>(-1),                 ExtendedSet<int>(0));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    + ExtendedSet<int>(-1),                 ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    + ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    + ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        + ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        + ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     + ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    + ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    + ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    + ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        + ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        + ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     + ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    + ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    + ExtendedSet<int>(1),                  ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    + ExtendedSet<int>(1),                  ExtendedSet<int>(0));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        + ExtendedSet<int>(1),                  ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        + ExtendedSet<int>(1),                  ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(1)                     + ExtendedSet<int>(1),                  ExtendedSet<int>(2));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    + ExtendedSet<int>(1),                  ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_TRUE((ExtendedSet<int>(Infinity::NEGATIVE) + ExtendedSet<int>(Infinity::POSITIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(-1)                    + ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        + ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        + ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     + ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    + ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::POSITIVE));
}



/* UnaryDiffOperationTest */

TEST(UnaryDiffOperationTest, AllTests) {
    EXPECT_EQ(-ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(-ExtendedSet<int>(-1)                , ExtendedSet<int>(1));
    EXPECT_EQ(-ExtendedSet<int>(Zero::NEGATIVE)    , ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(-ExtendedSet<int>(Zero::POSITIVE)    , ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(-ExtendedSet<int>(1)                 , ExtendedSet<int>(-1));
    EXPECT_EQ(-ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::NEGATIVE));
}



/* DiffOperationTest */

TEST(DiffOperationTest, AllTests) {
    EXPECT_TRUE((ExtendedSet<int>(Infinity::NEGATIVE) - ExtendedSet<int>(Infinity::NEGATIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(-1)                    - ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        - ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        - ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     - ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    - ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    - ExtendedSet<int>(-1),                 ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    - ExtendedSet<int>(-1),                 ExtendedSet<int>(0));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        - ExtendedSet<int>(-1),                 ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        - ExtendedSet<int>(-1),                 ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(1)                     - ExtendedSet<int>(-1),                 ExtendedSet<int>(2));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    - ExtendedSet<int>(-1),                 ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    - ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    - ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        - ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        - ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     - ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    - ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    - ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    - ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        - ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        - ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     - ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    - ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    - ExtendedSet<int>(1),                  ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    - ExtendedSet<int>(1),                  ExtendedSet<int>(-2));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        - ExtendedSet<int>(1),                  ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        - ExtendedSet<int>(1),                  ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(1)                     - ExtendedSet<int>(1),                  ExtendedSet<int>(0));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    - ExtendedSet<int>(1),                  ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    - ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    - ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        - ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        - ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     - ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_TRUE((ExtendedSet<int>(Infinity::POSITIVE) - ExtendedSet<int>(Infinity::POSITIVE)).NaN());
}



/* MultOperationTest */

TEST(MultOperationTest, AllTests) {
    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    * ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    * ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_TRUE((ExtendedSet<int>(Zero::NEGATIVE)     * ExtendedSet<int>(Infinity::NEGATIVE)).NaN());
    EXPECT_TRUE((ExtendedSet<int>(Zero::POSITIVE)     * ExtendedSet<int>(Infinity::NEGATIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(1)                     * ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    * ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Infinity::NEGATIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    * ExtendedSet<int>(-1),                 ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    * ExtendedSet<int>(-1),                 ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        * ExtendedSet<int>(-1),                 ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        * ExtendedSet<int>(-1),                 ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     * ExtendedSet<int>(-1),                 ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    * ExtendedSet<int>(-1),                 ExtendedSet<int>(Infinity::NEGATIVE));

    EXPECT_TRUE((ExtendedSet<int>(Infinity::NEGATIVE) * ExtendedSet<int>(Zero::NEGATIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(-1)                    * ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        * ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        * ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     * ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_TRUE((ExtendedSet<int>(Infinity::POSITIVE) * ExtendedSet<int>(Zero::NEGATIVE)).NaN());

    EXPECT_TRUE((ExtendedSet<int>(Infinity::NEGATIVE) * ExtendedSet<int>(Zero::POSITIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(-1)                    * ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        * ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        * ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     * ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_TRUE((ExtendedSet<int>(Infinity::POSITIVE) * ExtendedSet<int>(Zero::POSITIVE)).NaN());

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    * ExtendedSet<int>(1),                  ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    * ExtendedSet<int>(1),                  ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        * ExtendedSet<int>(1),                  ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        * ExtendedSet<int>(1),                  ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     * ExtendedSet<int>(1),                  ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    * ExtendedSet<int>(1),                  ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    * ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    * ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_TRUE((ExtendedSet<int>(Zero::NEGATIVE)     * ExtendedSet<int>(Infinity::POSITIVE)).NaN());
    EXPECT_TRUE((ExtendedSet<int>(Zero::POSITIVE)     * ExtendedSet<int>(Infinity::POSITIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(1)                     * ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    * ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Infinity::POSITIVE));
}



/* DivOperationTest */

TEST(DivOperationTest, AllTests) {
    EXPECT_TRUE((ExtendedSet<int>(Infinity::NEGATIVE) / ExtendedSet<int>(Infinity::NEGATIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(-1)                    / ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        / ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        / ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     / ExtendedSet<int>(Infinity::NEGATIVE), ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_TRUE((ExtendedSet<int>(Infinity::POSITIVE) / ExtendedSet<int>(Infinity::NEGATIVE)).NaN());

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    / ExtendedSet<int>(-1),                 ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    / ExtendedSet<int>(-1),                 ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        / ExtendedSet<int>(-1),                 ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        / ExtendedSet<int>(-1),                 ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     / ExtendedSet<int>(-1),                 ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    / ExtendedSet<int>(-1),                 ExtendedSet<int>(Infinity::NEGATIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    / ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Infinity::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    / ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_TRUE((ExtendedSet<int>(Zero::NEGATIVE)     / ExtendedSet<int>(Zero::NEGATIVE)).NaN());
    EXPECT_TRUE((ExtendedSet<int>(Zero::POSITIVE)     / ExtendedSet<int>(Zero::NEGATIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(1)                     / ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    / ExtendedSet<int>(Zero::NEGATIVE),     ExtendedSet<int>(Infinity::NEGATIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    / ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    / ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_TRUE((ExtendedSet<int>(Zero::NEGATIVE)     / ExtendedSet<int>(Zero::POSITIVE)).NaN());
    EXPECT_TRUE((ExtendedSet<int>(Zero::POSITIVE)     / ExtendedSet<int>(Zero::POSITIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(1)                     / ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    / ExtendedSet<int>(Zero::POSITIVE),     ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_EQ(ExtendedSet<int>(Infinity::NEGATIVE)    / ExtendedSet<int>(1),                  ExtendedSet<int>(Infinity::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(-1)                    / ExtendedSet<int>(1),                  ExtendedSet<int>(-1));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        / ExtendedSet<int>(1),                  ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        / ExtendedSet<int>(1),                  ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     / ExtendedSet<int>(1),                  ExtendedSet<int>(1));
    EXPECT_EQ(ExtendedSet<int>(Infinity::POSITIVE)    / ExtendedSet<int>(1),                  ExtendedSet<int>(Infinity::POSITIVE));

    EXPECT_TRUE((ExtendedSet<int>(Infinity::NEGATIVE) / ExtendedSet<int>(Infinity::POSITIVE)).NaN());
    EXPECT_EQ(ExtendedSet<int>(-1)                    / ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::NEGATIVE)        / ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Zero::NEGATIVE));
    EXPECT_EQ(ExtendedSet<int>(Zero::POSITIVE)        / ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_EQ(ExtendedSet<int>(1)                     / ExtendedSet<int>(Infinity::POSITIVE), ExtendedSet<int>(Zero::POSITIVE));
    EXPECT_TRUE((ExtendedSet<int>(Infinity::POSITIVE) / ExtendedSet<int>(Infinity::POSITIVE)).NaN());
}