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

    void raster(Canvas& canvas, Color& color) const {
        // TODO: fill triangle
    }

    // TODO: rename raster_wireframe
    void wire_frame(Canvas& canvas, Color& color) const {
        for(int i = 0; i < 3; i++) {
            Line l {points_[i], points_[(i+1) % 3]};
            l.raster(canvas, color);
        }
    }

    Vec<3, int> normal() const {
    // TODO: implement normal
    }

    Box& BBox() { return bounding_box_; }


private:

    bool inside(ScreenPoint& p) {
        // TODO: inside triangle?
    }

    Vec<3, int> barycentric(ScreenPoint& P) {
        // returns barycentric coordinates of point P
    }


    std::array<ScreenPoint, 3> points_;
    Box bounding_box_;
};


#endif //RASTERIZATIONENGINE_TRIANGLE_H
