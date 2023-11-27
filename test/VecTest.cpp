//
// Created by Dustin Burda on 11/20/23.
//

#include <gtest/gtest.h>

#include "../Vector.h"

TEST(VecTest, OperatorTest) {
    // Vector Constructor
    Vec<3, float> v1{{1, 2, 3}};
    Vec<3, float> v2{{0, -3, 2}};

    //Single Num Constructor
    Vec<100, float> v100(1);
    for(int i = 0; i < 100; i++) {
        EXPECT_EQ(v100[i], 1);
    }

    // Subscript
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);

    // Negate
    Vec<4, float> v3 {{1,2,3,4}};
    auto neg = Vec<4, float>{{-1, -2, -3, -4}};
    EXPECT_EQ(-v3, neg);

    // Plus Equal
    v1 += v2;
    auto expect_plus_equal = Vec<3, float>{{1, -1, 5}};
    EXPECT_EQ(v1, expect_plus_equal);

    // Minus Equal
    v1 -= v2;
    auto expect_minus_equal = Vec<3, float>{{1, 2, 3}};
    EXPECT_EQ(v1, expect_minus_equal);


    // Scalar Multiplication
    v1 *= 2;
    auto expect_double = Vec<3, float> {{2,4,6}};
    EXPECT_EQ(v1, expect_double);

    // Scalar Division
    v1 /= 2;
    auto expect_half = Vec<3, float>{{1,2,3}};
    EXPECT_EQ(v1, expect_half);

    float magnitude = v1.magnitude();
    float expect_magnitude = std::sqrt(14);
    EXPECT_EQ(magnitude, expect_magnitude);

    Vec<3, float> normal_vec = v1.normal();
    auto expect_normal_vec = v1 / magnitude;
    EXPECT_EQ(normal_vec, expect_normal_vec);

    v1.normalize();
    EXPECT_EQ(v1, normal_vec);

}

TEST(VecTest, StaticOperatorsTest) {
    Vec<3, float> v1{{1, 2, 3}};
    Vec<3, float> v2{{0, -3, 2}};

    // Addition
    auto add = v1 + v2;
    auto expect_add = Vec<3, float>{{1, -1, 5}};
    EXPECT_EQ(add, expect_add);

    // Subtraction
    auto sub = v1 - v2;
    auto expect_sub = Vec<3, float>{{1, 5, 1}};
    EXPECT_EQ(sub, expect_sub);

    // Scalar multiplication
    auto double_vec1 = v1 * 2;
    auto double_vec2 = 2 * v1;
    EXPECT_EQ(double_vec1, double_vec2);
    auto expect_vec = Vec<3, float> {{2, 4, 6}};
    EXPECT_EQ(expect_vec, double_vec1);

    auto orig_vec = double_vec1 / 2;
    EXPECT_EQ(orig_vec, v1);

    // homogenous coordinates
    Vec<4, float> homogenized = v1.homogenize_vector();
    auto homogenized_expect = Vec<4, float>{{1,2,3,1}};
    EXPECT_EQ(homogenized, homogenized_expect);

    Vec<3, float> dehomogenized = homogenized.dehomogenize_vector();
    EXPECT_EQ(dehomogenized, v1);

    homogenized *= 2;
    Vec<3, float> dehomogenized_double = homogenized.dehomogenize_vector();
    EXPECT_EQ(dehomogenized, v1);

    // Dot product
    EXPECT_EQ(dot(v1, v2), 0);
    EXPECT_EQ(dot(3*v1, 4*v2), 0);

    Vec<3, float> v3{{1, -2, 3}};
    Vec<3, float> v4{{2, 4, -5}};
    EXPECT_EQ(dot(v3, v4), -21);

    // Cross Product
    auto cross_vec1_2 = cross(v1, v2);
    auto cross_vec2_1 = cross(v2, v1);
    EXPECT_EQ(cross_vec1_2, - cross_vec2_1);
    Vec<3, float> expected_cross1_2 {{13, -2, -3}};
    EXPECT_EQ(cross_vec1_2, expected_cross1_2);

    Vec<3, float> expected_cross3_4{{-2, 11, 8}};
    EXPECT_EQ(expected_cross3_4, cross(v3, v4));
}

TEST(VecTest, Normalize) {
    Vec<3, float> v1 {{1, 1, 1}};
    auto normal = v1.normalize();
    EXPECT_TRUE( std::abs(1.0 - normal.magnitude()) < 0.001);
}
