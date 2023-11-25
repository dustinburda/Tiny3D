//
// Created by Dustin Burda on 11/24/23.
//

#include <gtest/gtest.h>
#include "../Transformations.h"
#include "../Vector.h"


// TODO: add homogenize, dehomogenize operations
TEST(Transformation, TranslationTest) {
    auto t1 = Transformations::Translate(5, -3, 2);
    Vec<4, double> v1 {{-3, 4, 5, 1}};
    Vec<4, double> v1_translate {{2, 1, 7, 1}};
    EXPECT_EQ(t1 * v1, v1_translate);

    Matrix<4, 4, double> t2 = inverse(t1);
    Vec<4, double> v2_translate {{-8, 7, 3, 1}};
    EXPECT_EQ(t2 * v1, v2_translate);

    Vec<4, double> n3 {{-3, 4, 5, 0}};
    EXPECT_EQ(t1 * n3, n3);
}


TEST(Transformation, ScalingTest) {
    auto t1 = Transformations::Scale(2, 3, 4);
    Vec<4, double> v1 {{-4, 6, 8, 1}};
    Vec<4, double> v1_scale{{ -8, 18, 32, 1 }};
    EXPECT_EQ(t1 * v1,  v1_scale);

    Vec<4, double> n1{{-4, 6, 8, 0}};
    Vec<4, double> n1_scale {{ -8, 18, 32, 0 }};
    EXPECT_EQ(t1 * n1, n1_scale);

    Matrix<4,4, double> t2 = inverse(t1);
    Vec<4, double> n1_inv_scale {{-2, 2, 2, 0}};
    EXPECT_EQ(t2 * n1, n1_inv_scale);

    auto reflectx = Transformations::Scale(-1, 1, 1);
    Vec<4, double> v2 {{2, 3, 4, 1}};
    Vec<4, double> v2_reflect {{-2, 3, 4, 1}};
    EXPECT_EQ(reflectx * v2, v2_reflect);
}

//TEST(Transformation, RotateTest) {
//    Vec<4, double> p1{{0, 1, 0, 1}};
//    auto half_quarterX = Transformations::RotateX(pi/4);
//    auto full_quarterX = Transformations::RotateX(pi/2);
//
//
//    EXPECT_EQ(half_quarterX * p1, {{ 0, std::sqrt(2) / 2, std::sqrt(2) / 2, 1 } });
//    EXPECT_EQ(full_quarterX * p1, {{ 0, 0, 1, 1 } });
//
//    Matrix R_Xinv;
//    half_quarterX.Inverse(R_Xinv);
//    EXPECT_EQ(R_Xinv * p1,  Tuple::Point(0, std::sqrt(2) / 2, -std::sqrt(2) / 2));
//
//
//    Point p2 = Tuple::Point(0, 0, 1);
//    auto half_quarterY = Transformations::RotateY(pi/4);
//    auto full_quarterY = Transformations::RotateY(pi/2);
//    EXPECT_EQ(half_quarterY * p2, Tuple::Point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
//    EXPECT_EQ(full_quarterY * p2, Tuple::Point(1, 0, 0));
//
//    Matrix R_Yinv;
//    half_quarterY.Inverse(R_Yinv);
//    EXPECT_EQ(R_Yinv * p2,  Tuple::Point(-std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
//
//    auto half_quarterZ = Transformations::RotateZ(pi/4);
//    auto full_quarterZ = Transformations::RotateZ(pi/2);
//    EXPECT_EQ(half_quarterZ * p1, Tuple::Point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0));
//    EXPECT_EQ(full_quarterZ * p1, Tuple::Point(-1, 0, 0));
//
//    Matrix R_Zinv;
//    half_quarterZ.Inverse(R_Zinv);
//    EXPECT_EQ(R_Zinv * p1, Tuple::Point(std::sqrt(2) / 2, std::sqrt(2) / 2, 0));
//}

//TEST(Transformation, ShearTest) {
//    Point p1 = Tuple::Point(2, 3, 4);
//    auto s1 = Transformations::Shear(1, 0, 0, 0, 0, 0);
//    EXPECT_EQ(s1 * p1, Tuple::Point(5, 3, 4));
//
//    auto s2 = Transformations::Shear(0, 1, 0, 0, 0, 0);
//    EXPECT_EQ(s2 * p1, Tuple::Point(6, 3, 4));
//
//    auto s3 = Transformations::Shear(0, 0, 1, 0, 0, 0);
//    EXPECT_EQ(s3 * p1, Tuple::Point(2, 5, 4));
//
//    auto s4 = Transformations::Shear(0, 0, 0, 1, 0, 0);
//    EXPECT_EQ(s4 * p1, Tuple::Point(2, 7, 4));
//
//    auto s5 = Transformations::Shear(0, 0, 0, 0, 1, 0);
//    EXPECT_EQ(s5 * p1, Tuple::Point(2, 3, 6));
//
//    auto s6 = Transformations::Shear(0, 0, 0, 0, 0, 1);
//    EXPECT_EQ(s6 * p1, Tuple::Point(2, 3, 7));
//}

TEST(Transformation, IntegrationTest) {
    Vec<4, double> v1{{1, 0, 1, 1}};
    auto A = Transformations::RotateX(pi/2);
    auto B = Transformations::Scale(5, 5, 5);
    auto C = Transformations::Translate(10, 5, 7);

    Vec<4, double> rotate_x_expect{{ 1, -1, 0, 1 }};
    EXPECT_EQ(A * v1, rotate_x_expect);

    auto v2 = A * v1;
    Vec<4, double> scale_expect {{5, -5, 0, 1}};
    EXPECT_EQ(B * v2, scale_expect);

    auto v3 = B * v2;
    Vec<4, double> translate_expect {{15, 0, 7, 1}};
    EXPECT_EQ(C * v3, translate_expect);

    Vec<4, double> final_result {{15, 0, 7, 1}};
    EXPECT_EQ(C * B * A * v1, final_result);
}