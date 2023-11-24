//
// Created by Dustin Burda on 11/23/23.
//

#ifndef RASTERIZATIONENGINE_TRANSFORMATIONS_H
#define RASTERIZATIONENGINE_TRANSFORMATIONS_H

#include "Matrix.h"

static constexpr double pi = 3.141592653589;

namespace Transformations {

    Matrix<4,4, double> Translate(double x, double y, double z);
    Matrix<4,4, double> RotateX(double r);
    Matrix<4,4, double> RotateY(double r);
    Matrix<4,4, double> RotateZ(double r);
    Matrix<4,4, double> Scale(double x, double y, double z);
    Matrix<4,4, double> Shear(double x_y, double x_z, double y_x, double y_z, double z_x, double z_y);

}


#endif //RASTERIZATIONENGINE_TRANSFORMATIONS_H
