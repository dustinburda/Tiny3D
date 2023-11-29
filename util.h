//
// Created by Dustin Burda on 11/21/23.
//

#ifndef RASTERIZATIONENGINE_UTIL_H
#define RASTERIZATIONENGINE_UTIL_H

#include "Vector.h"

static constexpr double epsilon = 10e-4;
static constexpr int height = 1000;
static constexpr int width = 1000;

template<typename T>
static bool equal(T num1, T num2) {
    return std::abs(num1 - num2) < epsilon;
}



#endif //RASTERIZATIONENGINE_UTIL_H
