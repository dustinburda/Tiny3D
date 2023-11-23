//
// Created by Dustin Burda on 11/19/23.
//

#ifndef RASTERIZATIONENGINE_BOUNDINGBOX_H
#define RASTERIZATIONENGINE_BOUNDINGBOX_H

#include "Vector.h"
#include "Canvas.h"
#include "util.h"

/*
 * 2D Bounding Box for efficient rasterization
 *
 *
 * */
class Box {
public:
    Box() : min_{{std::numeric_limits<int>::max(),std::numeric_limits<int>::max()}}, max_{{ 0, 0 }} {}

    Box(const std::vector<ScreenPoint>& points);

    int min_x() const { return min_[0]; }
    int min_y() const { return min_[1]; }
    int max_x() const { return max_[0]; }
    int max_y() const { return max_[1]; }

private:
    Vec<2, int> min_;
    Vec<2, int> max_;
};

#endif //RASTERIZATIONENGINE_BOUNDINGBOX_H
