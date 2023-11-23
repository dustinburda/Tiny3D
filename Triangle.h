//
// Created by Dustin Burda on 11/19/23.
//

#ifndef RASTERIZATIONENGINE_TRIANGLE_H
#define RASTERIZATIONENGINE_TRIANGLE_H

#include <array>
#include "util.h"
#include "Box.h"
#include "Canvas.h"
#include "Line.h"


class Triangle {
public:
    explicit Triangle(const ScreenPoint& v1, const ScreenPoint& v2, const ScreenPoint& v3) : points_{v1, v2, v3}, bounding_box_{{v1, v2, v3}} {}

    void raster(Canvas& canvas, const Color& color) const;
    void raster_wireframe(Canvas& canvas, const Color& color) const;

    Box& BBox() { return bounding_box_; }


private:

    static constexpr float epsilon = 10e-5;

    bool inside(const ScreenPoint& p) const;
    Vec<3, float> barycentric(const ScreenPoint& P) const;

    std::array<ScreenPoint, 3> points_;
    Box bounding_box_;
};


#endif //RASTERIZATIONENGINE_TRIANGLE_H
