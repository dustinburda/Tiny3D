//
// Created by Dustin Burda on 11/24/23.
//

#include <gtest/gtest.h>
#include "../Matrix.h"
#include "../Transformations.h"
#include "../util.h"

//
// Created by Dustin Burda on 9/14/23.
//

#include <gtest/gtest.h>
#include "../Matrix.h"

TEST(Matrix, MatrixConstuctTest) {
    std::array<double, 16> nums1{1, 2, 3, 4,
                                 5.5, 6.5, 7.5, 8.5,
                                 9, 10, 11, 12,
                                 13.5, 14.5, 15.5, 16.5};

    std::array<std::array<double, 4>, 4> nums2 = {std::array<double, 4>{1,2,3,4},
                                                  std::array<double, 4>{5.5, 6.5, 7.5, 8.5},
                                                  std::array<double, 4>{9,10,11,12},
                                                  std::array<double, 4>{13.5, 14.5, 15.5, 16.5}};

    std::array<std::array<double, 4>, 4> nums3 = {std::array<double, 4>{1.1,2.1,3.1,4.1},
                                                  std::array<double, 4>{5.4, 6.4, 7.4, 8.4},
                                                  std::array<double, 4>{9.1, 10.1 ,11.1 ,12.1},
                                                  std::array<double, 4>{13.4, 14.4, 15.4, 16.4}};

    Matrix<4,4, double> m1{nums1};
    Matrix<4,4, double> m2{nums2};
    Matrix<4,4, double> m3{nums3};

    EXPECT_EQ(m1, m2);
    EXPECT_NE(m1, m3);
    EXPECT_NE(m2, m3);

}

TEST(Matrix, OpTest) {
    std::array<double, 16> nums1{1, 2, 3, 4,
                                 5.5, 6.5, 7.5, 8.5,
                                 9, 10, 11, 12,
                                 13.5, 14.5, 15.5, 16.5};


    std::array<double, 16> evens{2, 4, 6, 8,
                                 10, 12, 14, 16,
                                 18, 20, 22, 24,
                                 26, 28, 30, 32};

    std::array<double, 16> consec {1, 2, 3 ,4,
                                   5, 6, 7, 8,
                                   9, 10, 11, 12,
                                   13, 14, 15, 16};

    Matrix<4,4, double> m1{nums1};
    Matrix<4,4, double> mEven {evens};
    Matrix<4,4, double> mConsec {consec};


     EXPECT_EQ(-m1, m1 * (-1.0));
    EXPECT_EQ(-mEven, mEven * (-1.0));
    EXPECT_EQ(-mConsec, mConsec * (-1.0));

    Matrix m1alt = (-m1);
    m1alt *= (-1);
    EXPECT_EQ(m1, m1alt);




    mEven /= 2;
    EXPECT_EQ(mEven, mConsec);
    mEven *= 2;
    EXPECT_EQ(mEven, mConsec * 2);

    EXPECT_EQ(mConsec + mEven, mConsec * 3);
    EXPECT_EQ(mConsec + mEven + mConsec * 5, mConsec * 8);
     EXPECT_EQ(mEven - mConsec, mConsec);

    std::array<double, 16> nums4{0, 0, 0, 0,
                                 0.5, 0.5, 0.5, 0.5,
                                 0, 0, 0, 0,
                                 0.5, 0.5, 0.5, 0.5};

    Matrix<4,4, double> m4{nums4};
    EXPECT_EQ(m1 - mConsec, m4);
    EXPECT_EQ((2 * m1 - mEven), 2*m4);

    auto mConsecCopy = mConsec;
    mConsecCopy *= 2;
    mConsecCopy -= mConsec;
    EXPECT_EQ(mConsecCopy, mConsec);

    mConsecCopy *= (-2);
    mConsecCopy += 3 *mConsec;
    EXPECT_EQ(mConsecCopy, mConsec);

    mConsecCopy -= mConsecCopy;
    Matrix<4,4, double> zero(0);
    EXPECT_EQ(mConsecCopy, zero);

    mConsecCopy = mConsecCopy + mConsec;
    mConsecCopy = mConsecCopy - mConsec;
    EXPECT_EQ(mConsecCopy, zero);
    EXPECT_EQ(m1 - mEven/2, m4);

}

TEST(Matrix, MatrixMultiplyTest) {

    std::array<double, 16> numMul1 {1, 2, 3, 4,
                                    5, 6, 7, 8,
                                    9, 8, 7, 6,
                                    5, 4, 3, 2};

    std::array<double, 16> numMult2 {-2, 1, 2, 3,
                                     3, 2, 1, -1,
                                     4, 3, 6, 5,
                                     1, 2, 7, 8};

    std::array<double, 16> numMultResult {20, 22, 50, 48,
                                          44, 54, 114, 108,
                                          40, 58, 110, 102,
                                          16, 26, 46, 42};

    Matrix<4,4, double> mult1{numMul1};
    Matrix<4,4, double> mult2{numMult2};

    Matrix<4,4, double> mmResult{numMultResult}; //Matrix-Matrix Result
    EXPECT_EQ(mult1 * mult2, mmResult);

    Vec<4, double> t1 {{1.0, 2.0, 3.0, 1.0}};
    std::array<double, 16> nums1 {1, 2, 3, 4,
                                  2, 4, 4, 2,
                                  8, 6, 4, 1,
                                  0, 0, 0, 1};

    Matrix<4,4, double> m1{nums1};
    Vec<4, double> mtResult{{18, 24, 33, 1}}; //Tuple-Matrix Result
    EXPECT_EQ(m1 * t1, mtResult);

    auto id = Id<4, double>();
    EXPECT_EQ( id * m1, m1);
    EXPECT_EQ(m1 * id, m1);

    EXPECT_EQ(mult1 * id, mult1);
    EXPECT_EQ(id * mult1, mult1);

    EXPECT_EQ(mult2 * id, mult2);
    EXPECT_EQ(id * mult2, mult2);

    Vec<4, double> t2{{1, 2, 3, 4}};
    EXPECT_EQ(id * t2, t2);
}

TEST(Matrix, TransposeTest) {
    std::array<double, 16> num {0, 9, 3, 0,
                                9, 8, 0, 8,
                                1, 8, 5, 3,
                                0, 0, 5, 8};

    std::array<double, 16> numT {0, 9, 1, 0,
                                 9, 8, 8, 0,
                                 3, 0, 5, 5,
                                 0, 8, 3, 8};

    Matrix<4,4, double> m{num};

    Matrix<4,4, double> mt = m.transpose();

    Matrix<4,4, double> mT_test{numT};
    EXPECT_EQ(mt, mT_test);

    Matrix<4,4, double> mtt = mt.transpose();
    EXPECT_EQ(m, mtt);
    EXPECT_EQ(m, mT_test.transpose());

    Matrix<4,4, double> ID = Id<4, double>();
    Matrix<4,4, double> ID_T = ID.transpose();
    EXPECT_EQ(ID, ID_T);
}

TEST(Matrix, DeterminantTest) {
    std::array<double, 16> nums1 {-2, -8, 3, 5,
                                  -3, 1, 7, 3,
                                  1, 2, -9, 6,
                                  -6, 7, 7, -9};

    Matrix<4,4, double> m1{nums1};

    auto identity4 = Id<4, float>();

    EXPECT_EQ(m1.determinant(), -4071);
    EXPECT_TRUE(m1.invertible());


    EXPECT_EQ(identity4.determinant(), 1);
    EXPECT_TRUE(identity4.invertible());

    std::array<double, 16> nums2 {6, 4, 4, 4,
                                  5, 5, 7, 6,
                                  4, -9, 3, -7,
                                  9, 1, 7, -6};

    Matrix<4,4, double> m2{nums2};
    EXPECT_TRUE(equal(m2.determinant(), -2120.0));
    EXPECT_TRUE(m2.invertible());

    std::array<double, 16> nums3 {-4, 2, -2, -3,
                                  9, 6, 2, 6,
                                  0, -5, 1, 5,
                                  0, 0, 0, 0};

    Matrix<4,4, double> m3{nums3};
    EXPECT_TRUE(equal(m3.determinant(), 0.0));
    EXPECT_FALSE(m3.invertible());
}

TEST(Matrix, InversionTest) {
    std::array<double, 16> nums1 {-5, 2, 6, -8,
                                  1, -5, 1, 8,
                                  7, 7, -6, -7,
                                  1, -3, 7, 4};

    Matrix<4,4, double> m1{nums1};
    auto m1det = m1.determinant();
    EXPECT_TRUE(equal(m1det, 532.0));

    Matrix<4,4, double> m1Inv = inverse(m1);

    std::array<double, 16> inv {0.21805, 0.45113, 0.24060, -0.04511,
                                -0.80827, -1.45677, -0.44361, 0.52068,
                                -0.07895, -0.22368, -0.05263, 0.19737,
                                -0.52256, -0.81391, -0.30075, 0.30639};

    Matrix<4,4, double> expect_inverse{inv};
    EXPECT_EQ(expect_inverse, m1Inv);
    auto identity4 = Id<4, double>();
    EXPECT_EQ(m1 * m1Inv, identity4);
    EXPECT_EQ(m1Inv * m1, identity4);


    std::array<double, 16> nums2 {8, -5, 9, 2,
                                  7, 5, 6, 1,
                                  -6, 0, 9, 6,
                                  -3, 0, -9, -4};

    Matrix<4,4, double> m2{nums2};

    Matrix<4,4, double> m2Inv = inverse(m2);

    std::array<double, 16> inv2 {-0.15385, -0.15385, -0.28205, -0.53846,
                                 -0.07692, 0.12308, 0.02564, 0.03077,
                                 0.35897, 0.35897, 0.43590, 0.92308,
                                 -0.69231, -0.69231, -0.76923, -1.92308};

    Matrix<4,4, double> inverse2{inv2};

    EXPECT_EQ(m2Inv, inverse2);
    EXPECT_EQ(m2 * m2Inv, identity4);
    EXPECT_EQ(m2Inv * m2, identity4);




    std::array<double, 16> nums3 {9, 3, 0, 9,
                                  -5, -2, -6, -3,
                                  -4, 9, 6, 4,
                                  -7, 6, 6, 2};
    Matrix<4,4, double> m3{nums3};

    Matrix<4,4, double> m3Inv = inverse(m3);

    // TODO: hardcode better matrix
    std::array<double, 16> inv3 {-0.0407407,  -0.0777778,  0.144444, -0.2222222,
                                 -0.0777778,  0.0333333,  0.366667, -0.333333,
                                 -0.0290123,  -0.146296,  -0.109259,  0.12963,
                                 0.177778,  0.0666667,  -0.266667,  0.333333};
    Matrix<4,4, double> inverse3{inv3};
    EXPECT_EQ(m3Inv, inverse3);
    EXPECT_EQ(m3 * m3Inv, identity4);
    EXPECT_EQ(m3Inv * m3, identity4);


};

