//
// Created by Dustin Burda on 11/17/23.
//

#ifndef RASTERIZATIONENGINE_LINE_H
#define RASTERIZATIONENGINE_LINE_H

#include "Canvas.h"


// TODO: replace Point with Vec<2>

using Point = std::array<int, 2>;

class Line {
public:
    explicit Line(const Point& p1, const Point& p2) : p1_{p1}, p2_{p2} {}

    // Bresenham
    void raster(Canvas& canvas, const Color& color);

private:
    Point p1_;
    Point p2_;
};


#endif //RASTERIZATIONENGINE_LINE_H
