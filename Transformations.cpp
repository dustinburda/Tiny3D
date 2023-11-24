//
// Created by Dustin Burda on 11/23/23.
//

#include "Transformations.h"

Matrix<4,4, double> Transformations::Translate(double x, double y, double z) {
    std::array<double, 16> nums{1, 0, 0, x,
                                0, 1, 0, y,
                                0, 0, 1, z,
                                0, 0, 0, 1};
    Matrix<4,4, double> translation{nums};
    return translation;
}

Matrix<4,4, double> Transformations::RotateX(double r) {
    std::array<double, 16> nums{1,      0,           0,       0,
                                0,  std::cos(r), -std::sin(r), 0,
                                0,  std::sin(r), std::cos(r), 0,
                                0,      0,           0,       1};
    Matrix<4,4, double> rotate_x{nums};
    return rotate_x;
}

Matrix<4,4, double> Transformations::RotateY(double r) {
    std::array<double, 16> nums{std::cos(r),      0,           std::sin(r),       0,
                                0,           1,               0,             0,
                                -std::sin(r),     0,           std::cos(r),       0,
                                0,           0,               0,             1};
    Matrix<4,4, double> rotate_y{nums};
    return rotate_y;
}

Matrix<4,4, double> Transformations::RotateZ(double r) {
    std::array<double, 16> nums{std::cos(r), -std::sin(r), 0, 0,
                                std::sin(r),  std::cos(r), 0, 0,
                                0,             0,     1, 0,
                                0,             0,     0, 1};
    Matrix<4,4, double> rotate_x{nums};
    return rotate_x;
}

Matrix<4,4, double> Transformations::Scale(double x, double y, double z) {
    std::array<double, 16> nums{x, 0, 0, 0,
                                0, y, 0, 0,
                                0, 0, z, 0,
                                0, 0, 0, 1};
    Matrix<4,4, double> scale{nums};
    return scale;

}

Matrix<4,4, double> Transformations::Shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y) {
    std::array<double, 16> nums{1, x_y, x_z, 0,
                                y_x, 1, y_z, 0,
                                z_x, z_y, 1, 0,
                                0,   0,   0, 1};

    Matrix<4,4, double> shear{nums};
    return shear;
}