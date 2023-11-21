//
// Created by Dustin Burda on 11/17/23.
//

#ifndef RASTERIZATIONENGINE_LINE_H
#define RASTERIZATIONENGINE_LINE_H

#include "Canvas.h"
#include "util.h"

class Line {
public:
    explicit Line(const ScreenPoint& p1, const ScreenPoint& p2) : p1_{p1}, p2_{p2} {}

    // Bresenham
    void raster(Canvas& canvas, const Color& color);

private:
    ScreenPoint p1_;
    ScreenPoint p2_;
};


#endif //RASTERIZATIONENGINE_LINE_H
