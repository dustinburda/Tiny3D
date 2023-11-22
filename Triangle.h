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

    void raster(Canvas& canvas, const Color& color) const {
        for(int x = bounding_box_.min_x(); x <= bounding_box_.max_x(); x++) {
            for(int y = bounding_box_.min_y(); y <= bounding_box_.max_y(); y++) {
                ScreenPoint p {{ x, y}};

                if( inside( p ) ) {
                    canvas.write_pixel(color, x, y);
                }

            }
        }
    }

    void raster_wireframe(Canvas& canvas, const Color& color) const {
        for(int i = 0; i < 3; i++) {
            Line l {points_[i], points_[(i+1) % 3]};
            l.raster(canvas, color);
        }
    }

    Box& BBox() { return bounding_box_; }


private:

    bool inside(const ScreenPoint& p) const {
        auto barycentric_coord = barycentric(p);

        if(barycentric_coord[0] < 0 || barycentric_coord[1] < 0 || barycentric_coord[2] < 0) {
            return false;
        }

        return true;
    }

    static constexpr float epsilon = 10e-5;
    Vec<3, float> barycentric(const ScreenPoint& P) const {
        auto v1 =Vec<3, float> {{static_cast<float>(points_[1][0] -points_[0][0]), static_cast<float>(points_[2][0] - points_[0][0]), static_cast<float>(points_[0][0] - P[0])}};
        auto v2 =Vec<3, float> {{static_cast<float>(points_[1][1] - points_[0][1]), static_cast<float>(points_[2][1]- points_[0][1]), static_cast<float>(points_[0][1] - P[1])}};

        Vec<3, float> b_vec = cross(v1, v2);

        if( std::abs(b_vec[2]) < epsilon) // TODO: Might not be correct condition
            return Vec<3, float> {{-1, -1, -1}};

        return Vec<3, float> {{ 1.0f - (b_vec[0] + b_vec[1]) / b_vec[2], (b_vec[0]) / b_vec[2], (b_vec[1]) / b_vec[2]  }};
    }


    std::array<ScreenPoint, 3> points_;
    Box bounding_box_;
};


#endif //RASTERIZATIONENGINE_TRIANGLE_H
