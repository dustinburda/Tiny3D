//
// Created by Dustin Burda on 11/17/23.
//

#ifndef RASTERIZATIONENGINE_LINE_H
#define RASTERIZATIONENGINE_LINE_H

#include "Canvas.h"

using Point = std::array<int, 2>;

class Line {
public:
    explicit Line(const Point& p1, const Point& p2) : p1_{p1}, p2_{p2} {}

    // Bresenham
    void raster(Canvas& canvas, const Color& color) {
        bool swapped { false };
        if(std::abs(p1_[1] - p2_[1]) > std::abs(p1_[0] - p2_[0])) {
            std::swap(p1_[0], p1_[1]); //swap x0, y0
            std::swap(p2_[0], p2_[1]); // swap x1, y1
            swapped = true;
        }


        if(p1_[0] > p2_[0])
            std:swap(p1_, p2_);

        for(int x = p1_[0]; x <= p2_[0]; x++) {
            float t = (x - p1_[0]) / static_cast<float>(p2_[0] - p1_[0]);
            int y = p1_[1] * (1.0 -t) + p2_[1] * t;

            swapped ? canvas.write_pixel(color, y, x)
                    : canvas.write_pixel(color, x, y);
        }
    }

private:
    Point p1_;
    Point p2_;
};


#endif //RASTERIZATIONENGINE_LINE_H
