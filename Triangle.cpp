//
// Created by Dustin Burda on 11/19/23.
//

#include "Triangle.h"

void Triangle::raster(Canvas& canvas, const Color& color) const {
    for(int x = bounding_box_.min_x(); x <= bounding_box_.max_x(); x++) {
        for(int y = bounding_box_.min_y(); y <= bounding_box_.max_y(); y++) {
            ScreenPoint p {{ x, y}};

            Vec<3, float> barycentric;
            if( inside( p, barycentric ) ) {
                canvas.write_pixel(color, x, y);
            }
        }
    }
}

void Triangle::raster_triangle_mesh( std::array<Vec<3, float>, 3>& world_coord, Canvas& canvas, const Color& color) const {
    for(int x = bounding_box_.min_x(); x <= bounding_box_.max_x(); x++) {
        for(int y = bounding_box_.min_y(); y <= bounding_box_.max_y(); y++) {
            ScreenPoint p {{ x, y}};

            Vec<3, float> barycentric;
            if( inside( p, barycentric ) ) {
                float zbuff_val = world_coord[0][2]*barycentric[0] + world_coord[1][2]*barycentric[1] + world_coord[2][2]*barycentric[2];
                if(canvas.zbuff_val_at(x,y) < zbuff_val) {
                    canvas.set_zbuff_val(zbuff_val, x, y) ;
                    canvas.write_pixel(color, x, y);
                }
            }

        }
    }
}



void Triangle::raster_wireframe(Canvas& canvas, const Color& color) const {
    for(int i = 0; i < 3; i++) {
        Line l {points_[i], points_[(i+1) % 3]};
        l.raster(canvas, color);
    }
}

bool Triangle::inside(const ScreenPoint& p, Vec<3, float>& barycentric_coord) const {
    barycentric_coord = barycentric(p);

    if(barycentric_coord[0] < 0 || barycentric_coord[1] < 0 || barycentric_coord[2] < 0) {
        return false;
    }

    return true;
}

static constexpr float epsilon = 10e-5;
Vec<3, float> Triangle::barycentric(const ScreenPoint& P) const {
    auto v1 =Vec<3, float> {{static_cast<float>(points_[1][0] -points_[0][0]), static_cast<float>(points_[2][0] - points_[0][0]), static_cast<float>(points_[0][0] - P[0])}};
    auto v2 =Vec<3, float> {{static_cast<float>(points_[1][1] - points_[0][1]), static_cast<float>(points_[2][1]- points_[0][1]), static_cast<float>(points_[0][1] - P[1])}};

    Vec<3, float> b_vec = cross(v1, v2);

    if( std::abs(b_vec[2]) < epsilon) // TODO: Might not be correct condition
        return Vec<3, float> {{-1, -1, -1}};

    return Vec<3, float> {{ 1.0f - (b_vec[0] + b_vec[1]) / b_vec[2], (b_vec[0]) / b_vec[2], (b_vec[1]) / b_vec[2]  }};
}
