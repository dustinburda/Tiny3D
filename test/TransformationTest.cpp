//
// Created by Dustin Burda on 11/24/23.
//

#include <gtest/gtest.h>
#include "../Transformations.h"
#include "../Vector.h"


// TODO: add homogenize, dehomogenize operations
TEST(Transformation, TranslationTest) {
    Vec<3, double> v1{{-3,4,5}};
    Vec<4, double> v1_hom = v1.homogenize_vector();
    auto t1 = Transformations::Translate(5, -3, 2);

    Vec<4, double> v1_translate_hom {{2, 1, 7, 1}};
    Vec<3, double> v1_translate {{2, 1, 7}};

    EXPECT_EQ(t1 * v1_hom, v1_translate_hom);
    EXPECT_EQ((t1 * v1_hom).dehomogenize_vector(), v1_translate);

    Matrix<4, 4, double> t2 = inverse(t1);
    Vec<4, double> v2_translate {{-8, 7, 3, 1}};
    EXPECT_EQ(t2 * v1_hom, v2_translate);
    EXPECT_EQ((t2 * v1_hom).dehomogenize_vector(), v2_translate.dehomogenize_vector());


    Vec<3, double> n3 {{-3,4,5}};
    Vec<4, double> n3_hom {{-3, 4, 5, 0}};
    EXPECT_EQ(t1*n3_hom, n3_hom);
    EXPECT_EQ((t1 * n3_hom).dehomogenize_normal(), n3_hom.dehomogenize_normal());
}


TEST(Transformation, ScalingTest) {
    auto t1 = Transformations::Scale(2, 3, 4);
    Vec<3, double> v1 {{-4, 6, 8}};
    Vec<4, double> v1_hom {{-4, 6, 8, 1}};
    Vec<3, double> v1_scale{{ -8, 18, 32}};
    Vec<4, double> v1_scale_hom{{ -8, 18, 32, 1 }};

    EXPECT_EQ(t1 * v1_hom,  v1_scale_hom);
    EXPECT_EQ(t1 * v1.homogenize_vector(),  v1_scale_hom);
    EXPECT_EQ((t1 * v1.homogenize_vector()).dehomogenize_vector(), v1_scale);
    EXPECT_EQ((t1 * v1_hom).dehomogenize_vector(), v1_scale);
    EXPECT_EQ((t1 * v1.homogenize_vector()).dehomogenize_vector(), v1_scale_hom.dehomogenize_vector());
    EXPECT_EQ((t1 * v1_hom).dehomogenize_vector(), v1_scale_hom.dehomogenize_vector());

    Vec<3, double> n1{{-4, 6, 8}};
    Vec<3, double> n1_scale {{ -8, 18, 32}};
    Vec<4, double> n1_hom{{-4, 6, 8, 0}};
    Vec<4, double> n1_scale_hom {{ -8, 18, 32, 0 }};
    EXPECT_EQ(t1 * n1_hom, n1_scale_hom);
    EXPECT_EQ(t1 * n1.homogenize_normal(), n1_scale_hom);
    EXPECT_EQ((t1 * n1_hom).dehomogenize_normal(), n1_scale);
    EXPECT_EQ((t1 * n1.homogenize_normal()).dehomogenize_normal(), n1_scale);
    EXPECT_EQ((t1 * n1_hom).dehomogenize_normal(), n1_scale_hom.dehomogenize_normal());
    EXPECT_EQ((t1 * n1.homogenize_normal()).dehomogenize_normal(), n1_scale_hom.dehomogenize_normal());

    Matrix<4,4, double> t2 = inverse(t1);
    Vec<3, double> n1_inv_scale {{-2, 2, 2}};
    Vec<4, double> n1_inv_scale_hom {{-2, 2, 2, 0}};
    EXPECT_EQ(t2 * n1_hom, n1_inv_scale_hom);
    EXPECT_EQ((t2 * n1_hom).dehomogenize_normal(), n1_inv_scale_hom.dehomogenize_normal());
    EXPECT_EQ((t2 * n1.homogenize_normal()).dehomogenize_normal(), n1_inv_scale_hom.dehomogenize_normal());
    EXPECT_EQ((t2 * n1.homogenize_normal()).dehomogenize_normal(), n1_inv_scale);

    auto reflectx = Transformations::Scale(-1, 1, 1);
    Vec<3, double> v2 {{2, 3, 4}};
    Vec<3, double> v2_reflect {{-2, 3, 4}};
    Vec<4, double> v2_hom {{2, 3, 4, 1}};
    Vec<4, double> v2_reflect_hom {{-2, 3, 4, 1}};
    EXPECT_EQ((reflectx * v2.homogenize_vector()).dehomogenize_vector(), v2_reflect);
    EXPECT_EQ(reflectx * v2.homogenize_vector(), v2_reflect_hom);
}

TEST(Transformation, RotateTest) {
    Vec<4, double> v1{{0, 1, 0, 1}};
    auto half_quarterX = Transformations::RotateX(pi/4);
    auto full_quarterX = Transformations::RotateX(pi/2);

    Vec<4, double> half_quarterX_expect {{ 0, std::sqrt(2) / 2, std::sqrt(2) / 2, 1 }};
    Vec<4, double> full_quarterX_expect {{ 0, 0, 1, 1 }};
    EXPECT_EQ(half_quarterX * v1, half_quarterX_expect);
    EXPECT_EQ(full_quarterX * v1, full_quarterX_expect);

    Matrix<4,4, double> R_Xinv = inverse(half_quarterX);
    Vec<4, double> inv_half_quarterX_expect{{ 0, std::sqrt(2) / 2, -std::sqrt(2) / 2, 1 }};
    EXPECT_EQ(R_Xinv * v1,  inv_half_quarterX_expect);


    Vec<4, double> v2 {{0, 0, 1, 1}};
    auto half_quarterY = Transformations::RotateY(pi/4);
    auto full_quarterY = Transformations::RotateY(pi/2);

    Vec<4, double> half_quarterY_expect {{std::sqrt(2) / 2, 0, std::sqrt(2) / 2, 1}};
    Vec<4, double> full_quarterY_expect {{1, 0, 0, 1}};
    EXPECT_EQ(half_quarterY * v2, half_quarterY_expect);
    EXPECT_EQ(full_quarterY * v2, full_quarterY_expect);

    Matrix<4,4, double> R_Yinv = inverse(half_quarterY);
    Vec<4, double> inv_half_quarterY_expect{{-std::sqrt(2) / 2, 0, std::sqrt(2) / 2, 1}};
    EXPECT_EQ(R_Yinv * v2,  inv_half_quarterY_expect);

    auto half_quarterZ = Transformations::RotateZ(pi/4);
    auto full_quarterZ = Transformations::RotateZ(pi/2);
    Vec<4, double> expect_half_quarterZ{{-std::sqrt(2) / 2, std::sqrt(2) / 2, 0, 1}};
    Vec<4, double> expect_full_quarterZ{{-1, 0, 0, 1}};
    EXPECT_EQ(half_quarterZ * v1, expect_half_quarterZ);
    EXPECT_EQ(full_quarterZ * v1, expect_full_quarterZ);

    Matrix<4,4, double> R_Zinv = inverse(half_quarterZ);
    Vec<4, double> inv_half_quarterZ_expect{{std::sqrt(2) / 2, std::sqrt(2) / 2, 0, 1}};
    EXPECT_EQ(R_Zinv * v1, inv_half_quarterZ_expect);
}

TEST(Transformation, ShearTest) {
    Vec<4, double> v1{{2, 3, 4, 1}} ;
    auto s1 = Transformations::Shear(1, 0, 0, 0, 0, 0);
    Vec<4, double> expect_s1{{ 5, 3, 4, 1 }};
    EXPECT_EQ(s1 * v1, expect_s1);

    auto s2 = Transformations::Shear(0, 1, 0, 0, 0, 0);
    Vec<4, double> expect_s2{{ 6, 3, 4, 1 }};
    EXPECT_EQ(s2 * v1, expect_s2);

    auto s3 = Transformations::Shear(0, 0, 1, 0, 0, 0);
    Vec<4, double> expect_s3{{ 2, 5, 4, 1 }};
    EXPECT_EQ(s3 * v1,  expect_s3);

    auto s4 = Transformations::Shear(0, 0, 0, 1, 0, 0);
    Vec<4, double> expect_s4{{ 2, 7, 4, 1 }};
    EXPECT_EQ(s4 * v1, expect_s4);

    auto s5 = Transformations::Shear(0, 0, 0, 0, 1, 0);
    Vec<4, double> expect_s5{{ 2, 3, 6, 1 }};
    EXPECT_EQ(s5 * v1, expect_s5);

    auto s6 = Transformations::Shear(0, 0, 0, 0, 0, 1);
    Vec<4, double> expect_s6{{ 2, 3, 7, 1 }};
    EXPECT_EQ(s6 * v1, expect_s6);
}

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