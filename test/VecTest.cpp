//
// Created by Dustin Burda on 11/20/23.
//

#include <gtest/gtest.h>

#include "../Vector.h"

TEST(VecTest, OperatorTest) {
    // Vector Constructor
    Vec<3> v1{{1, 2, 3}};
    Vec<3> v2{{0, -3, 2}};

    // Subscript
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);

    // Plus Equal
    v1 += v2;
    auto expect_plus_equal = Vec<3>{{1, -1, 5}};
    EXPECT_EQ(v1, expect_plus_equal);

    // Minus Equal
    v1 -= v2;
    auto expect_minus_equal = Vec<3>{{1, 2, 3}};
    EXPECT_EQ(v1, expect_minus_equal);

    // Negate
    Vec<4> v3 {{1,2,3,4}};
    auto neg = Vec<4>{{-1, -2, -3, -4}};
    EXPECT_EQ(-v3, neg);

    //Single Num Constructor
    Vec<100> v100(1);
    for(int i = 0; i < 100; i++) {
        EXPECT_EQ(v100[i], 1);
    }

    // Scalar Multiplication


}

TEST(VecTest, StaticOperatorsTest) {
    Vec<3> v1{{1, 2, 3}};
    Vec<3> v2{{0, -3, 2}};

    // Addition
    auto add = v1 + v2;
    auto expect_add = Vec<3>{{1, -1, 5}};
    EXPECT_EQ(add, expect_add);

    auto sub = v1 - v2;
    auto expect_sub = Vec<3>{{1, 5, 1}};
    EXPECT_EQ(sub, expect_sub);

}
