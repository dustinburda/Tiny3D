//
// Created by Dustin Burda on 11/19/23.
//

#ifndef RASTERIZATIONENGINE_TRIANGLE_H
#define RASTERIZATIONENGINE_TRIANGLE_H

#include <array>

using Vec = std::array<float, 3>;




class Triangle {
    explicit Triangle(Vec v1, Vec v2, Vec v3) : points_{v1, v2, v3} {}



private:
    std::array<Vec, 3> points_;
};


#endif //RASTERIZATIONENGINE_TRIANGLE_H
