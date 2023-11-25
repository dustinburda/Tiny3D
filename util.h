//
// Created by Dustin Burda on 11/21/23.
//

#ifndef RASTERIZATIONENGINE_UTIL_H
#define RASTERIZATIONENGINE_UTIL_H

#include "Vector.h"

using ScreenPoint = Vec<2, int>;
using WorldCoord = Vec<3, float>;
using Light = Vec<3, float>;

static constexpr double epsilon = 10e-5;

template<typename T>
static bool equal(T num1, T num2) {
    return std::abs(num1 - num2) < epsilon;
}



#endif //RASTERIZATIONENGINE_UTIL_H
