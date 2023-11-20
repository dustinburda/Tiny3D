//
// Created by Dustin Burda on 11/19/23.
//

#ifndef RASTERIZATIONENGINE_TRIANGLE_H
#define RASTERIZATIONENGINE_TRIANGLE_H

#include <array>
#include "Vector.h"
#include "Box.h"
#include "Canvas.h"

using ScreenPoint = Vec<2>;




class Triangle {
public:
    explicit Triangle(const Vec<2>& v1, const Vec<2>& v2, const Vec<2>& v3) : points_{v1, v2, v3} {

        // Instantiate Box Here
    }

    void raster(Canvas& canvas, Color& color) const {
        // TODO: fill triangle
    }

    void wire_frame(Canvas& canvas, Color& color) const {
        // TODO: draw lines
    }

    Vec<3> normal() const {
    // TODO: implement normal
    }

    Box& BBox() { return bounding_box_; }


private:

    bool inside(ScreenPoint& p) {
        // TODO: inside triangle?
    }

    Vec<3> barycentric(ScreenPoint& P) {
        // returns barycentric coordinates of point P
    }


    std::array<ScreenPoint, 3> points_;
    Box bounding_box_;
};


#endif //RASTERIZATIONENGINE_TRIANGLE_H
